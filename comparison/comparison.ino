#include <Arduino.h>
#include "esp_heap_caps.h"
#include "esp_system.h"
#include "esp_timer.h"


// ============================================================
// CONFIGURATION
// ============================================================

// 0 = Fan Speed
// 1 = Light Intensity
#define TARGET 0


// 0 = BASELINE (no ML model)
// 1 = Decision Tree
// 2 = Naive Bayes
#define MODEL_TYPE 1


// Number of predictions used for timing
#define NUM_RUNS 100000

// Warm-up predictions
#define WARMUP_RUNS 1000


// ============================================================
// BASELINE VALUES
// ============================================================
//
// STEP 1:
// Run the code with MODEL_TYPE = 0.
//
// Record:
//   Running firmware size
//   Free heap after boot
//
// STEP 2:
// Replace these example values with your baseline results.

#define BASELINE_FIRMWARE_SIZE  200000
#define BASELINE_FREE_HEAP      280000


// ============================================================
// MODEL INCLUDES
// ============================================================

#if MODEL_TYPE == 1

    // --------------------------------------------------------
    // DECISION TREE
    // --------------------------------------------------------

    #if TARGET == 0

        #include "fan_speed_model.h"

        Eloquent::ML::Port::DecisionTreeFan model;

    #elif TARGET == 1

        #include "light_intensity_model.h"

        Eloquent::ML::Port::DecisionTreeLight model;

    #endif


#elif MODEL_TYPE == 2

    // --------------------------------------------------------
    // NAIVE BAYES
    // --------------------------------------------------------

    #if TARGET == 0

        #include "naive_bayes_fan.h"

        Eloquent::ML::Port::GaussianNBFan model;

    #elif TARGET == 1

        #include "naive_bayes_light.h"

        Eloquent::ML::Port::GaussianNBLight model;

    #endif

#endif


// ============================================================
// PREVENT COMPILER OPTIMIZATION
// ============================================================

volatile int predictionResult = 0;


// ============================================================
// INPUT DATA
// ============================================================
//
// Feature order:
//
// Fan Speed:
// count, co2_level, temp, humidity
//
// Light Intensity:
// count, co2_level, ldr_diff
//
// IMPORTANT:
// Use the same feature order used during model training.


#if TARGET == 0

    float input[] = {
        15.0,
        800.0,
        32.0,
        60.0
    };


#elif TARGET == 1

    float input[] = {
        15.0,
        800.0,
        500.0
    };

#endif


// ============================================================
// GET TARGET NAME
// ============================================================

const char* getTargetName() {

#if TARGET == 0
    return "Fan Speed";

#elif TARGET == 1
    return "Light Intensity";

#endif

}


// ============================================================
// GET MODEL NAME
// ============================================================

const char* getModelName() {

#if MODEL_TYPE == 0
    return "Baseline";

#elif MODEL_TYPE == 1
    return "Decision Tree";

#elif MODEL_TYPE == 2
    return "Naive Bayes";

#endif

}


// ============================================================
// PRINT CONFIGURATION
// ============================================================

void printConfiguration() {

    Serial.println();
    Serial.println("==================================================");
    Serial.println("          ESP32 MACHINE LEARNING BENCHMARK");
    Serial.println("==================================================");

    Serial.print("Target: ");
    Serial.println(getTargetName());

    Serial.print("Model: ");
    Serial.println(getModelName());

    Serial.print("CPU Frequency: ");
    Serial.print(getCpuFrequencyMhz());
    Serial.println(" MHz");

    Serial.println("==================================================");

}


// ============================================================
// PRINT MEMORY INFORMATION
// ============================================================

void printMemoryInfo(const char *stage) {

    Serial.println();

    Serial.println("---------------- MEMORY INFO ----------------");

    Serial.print("Stage: ");
    Serial.println(stage);

    Serial.print("Free heap: ");
    Serial.print(ESP.getFreeHeap());
    Serial.println(" bytes");

    Serial.print("Minimum free heap: ");
    Serial.print(ESP.getMinFreeHeap());
    Serial.println(" bytes");

    Serial.print("Maximum allocatable block: ");
    Serial.print(ESP.getMaxAllocHeap());
    Serial.println(" bytes");

    Serial.print("Total heap: ");
    Serial.print(ESP.getHeapSize());
    Serial.println(" bytes");

    Serial.println("---------------------------------------------");

}


// ============================================================
// PRINT FIRMWARE SIZE
// ============================================================

void printFirmwareSize() {

    size_t sketchSize = ESP.getSketchSize();

    Serial.println();

    Serial.println("---------------- FIRMWARE SIZE ----------------");

    Serial.print("Running firmware size: ");
    Serial.print(sketchSize);
    Serial.println(" bytes");

    Serial.print("Running firmware size: ");
    Serial.print(sketchSize / 1024.0, 3);
    Serial.println(" KB");

    Serial.print("Free sketch space: ");
    Serial.print(ESP.getFreeSketchSpace());
    Serial.println(" bytes");

    Serial.println("------------------------------------------------");

}


// ============================================================
// PRINT FINAL RESULT TABLE
// ============================================================

void printResultTable(
    double inferenceTimeMs,
    float modelSizeKB,
    int64_t ramImpact
) {

    Serial.println();
    Serial.println();
    Serial.println("==========================================================================================");

    Serial.println(
        "| Target          | Model         | Inference Time (ms) | Model Size (KB) | RAM Impact (bytes) |"
    );

    Serial.println("==========================================================================================");

    Serial.print("| ");


    // --------------------------------------------------------
    // TARGET
    // --------------------------------------------------------

#if TARGET == 0

    Serial.print("Fan Speed       ");

#elif TARGET == 1

    Serial.print("Light Intensity ");

#endif


    Serial.print("| ");


    // --------------------------------------------------------
    // MODEL
    // --------------------------------------------------------

#if MODEL_TYPE == 1

    Serial.print("Decision Tree ");

#elif MODEL_TYPE == 2

    Serial.print("Naive Bayes   ");

#endif


    Serial.print("| ");


    // --------------------------------------------------------
    // INFERENCE TIME
    // --------------------------------------------------------

    Serial.print(inferenceTimeMs, 6);


    // Add spaces
    Serial.print("            | ");


    // --------------------------------------------------------
    // MODEL SIZE
    // --------------------------------------------------------

    Serial.print(modelSizeKB, 3);


    Serial.print("           | ");


    // --------------------------------------------------------
    // RAM IMPACT
    // --------------------------------------------------------

    Serial.print(ramImpact);


    Serial.println("                |");

    Serial.println("==========================================================================================");

}


// ============================================================
// BASELINE BENCHMARK
// ============================================================

void runBaselineBenchmark() {

    Serial.println();
    Serial.println("==================================================");
    Serial.println("               BASELINE MEASUREMENT");
    Serial.println("==================================================");

    size_t firmwareSize = ESP.getSketchSize();
    size_t freeHeap = ESP.getFreeHeap();

    Serial.print("BASELINE_FIRMWARE_SIZE = ");
    Serial.println(firmwareSize);

    Serial.print("BASELINE_FREE_HEAP = ");
    Serial.println(freeHeap);

    Serial.println();
    Serial.println("Copy these values into:");
    Serial.println();

    Serial.print("#define BASELINE_FIRMWARE_SIZE ");
    Serial.println(firmwareSize);

    Serial.print("#define BASELINE_FREE_HEAP     ");
    Serial.println(freeHeap);

    Serial.println();
    Serial.println("==================================================");

}


// ============================================================
// MODEL BENCHMARK
// ============================================================

void runModelBenchmark() {

    Serial.println();

    Serial.println("==================================================");
    Serial.println("             MODEL BENCHMARK START");
    Serial.println("==================================================");


    // --------------------------------------------------------
    // MEMORY BEFORE BENCHMARK
    // --------------------------------------------------------

    size_t heapBefore = ESP.getFreeHeap();


    // --------------------------------------------------------
    // WARM-UP
    // --------------------------------------------------------

    Serial.print("Warm-up predictions: ");
    Serial.println(WARMUP_RUNS);

    for (int i = 0; i < WARMUP_RUNS; i++) {

        predictionResult = model.predict(input);

    }


    // --------------------------------------------------------
    // INFERENCE TIME BENCHMARK
    // --------------------------------------------------------

    Serial.print("Benchmark predictions: ");
    Serial.println(NUM_RUNS);


    int64_t startTime = esp_timer_get_time();


    for (int i = 0; i < NUM_RUNS; i++) {

        predictionResult = model.predict(input);

    }


    int64_t endTime = esp_timer_get_time();


    // --------------------------------------------------------
    // CALCULATE INFERENCE TIME
    // --------------------------------------------------------

    int64_t totalTimeUs = endTime - startTime;

    double averageTimeUs =
        (double) totalTimeUs / NUM_RUNS;

    double averageTimeMs =
        averageTimeUs / 1000.0;


    // --------------------------------------------------------
    // MEMORY AFTER BENCHMARK
    // --------------------------------------------------------

    size_t heapAfter = ESP.getFreeHeap();


    // --------------------------------------------------------
    // FIRMWARE SIZE
    // --------------------------------------------------------

    size_t currentFirmwareSize =
        ESP.getSketchSize();


    // Model size compared with baseline

    int64_t modelSizeBytes =
        (int64_t) currentFirmwareSize -
        (int64_t) BASELINE_FIRMWARE_SIZE;


    float modelSizeKB =
        (float) modelSizeBytes / 1024.0;


    // --------------------------------------------------------
    // RAM IMPACT
    // --------------------------------------------------------
    //
    // Compare current free heap with baseline free heap.

    int64_t ramImpact =
        (int64_t) BASELINE_FREE_HEAP -
        (int64_t) heapBefore;


    // --------------------------------------------------------
    // PRINT INDIVIDUAL RESULTS
    // --------------------------------------------------------

    Serial.println();

    Serial.println("-------------- MEASUREMENTS --------------");

    Serial.print("Average inference time: ");
    Serial.print(averageTimeMs, 6);
    Serial.println(" ms");

    Serial.print("Current firmware size: ");
    Serial.print(currentFirmwareSize);
    Serial.println(" bytes");

    Serial.print("Model size contribution: ");
    Serial.print(modelSizeKB, 3);
    Serial.println(" KB");

    Serial.print("Free heap before benchmark: ");
    Serial.print(heapBefore);
    Serial.println(" bytes");

    Serial.print("Free heap after benchmark: ");
    Serial.print(heapAfter);
    Serial.println(" bytes");

    Serial.print("RAM impact: ");
    Serial.print(ramImpact);
    Serial.println(" bytes");

    Serial.println("------------------------------------------");


    // --------------------------------------------------------
    // PRINT FINAL TABLE ROW
    // --------------------------------------------------------

    printResultTable(
        averageTimeMs,
        modelSizeKB,
        ramImpact
    );


    // --------------------------------------------------------
    // CHECK PREDICTION
    // --------------------------------------------------------

    Serial.println();

    Serial.print("Last prediction: ");
    Serial.println(predictionResult);

}


// ============================================================
// SETUP
// ============================================================

void setup() {

    Serial.begin(115200);

    delay(3000);


    // --------------------------------------------------------
    // PRINT CONFIGURATION
    // --------------------------------------------------------

    printConfiguration();


    // --------------------------------------------------------
    // BASELINE BUILD
    // --------------------------------------------------------

#if MODEL_TYPE == 0

    runBaselineBenchmark();

#endif


    // --------------------------------------------------------
    // DECISION TREE / NAIVE BAYES BUILD
    // --------------------------------------------------------

#if MODEL_TYPE == 1 || MODEL_TYPE == 2

    runModelBenchmark();

#endif

}


// ============================================================
// LOOP
// ============================================================

void loop() {

    delay(1000);

}
