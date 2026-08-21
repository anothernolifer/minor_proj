#include <Arduino.h>
#include "esp_heap_caps.h"
#include "esp_system.h"
#include "esp_timer.h"


// ============================================================
// CONFIGURATION
// ============================================================

// Select ONE target at a time:
//
// 0 = Fan Speed
// 1 = Light Intensity
#define TARGET 0


// Select ONE model at a time:
//
// 0 = BASELINE (no ML model)
// 1 = Decision Tree
// 2 = Naive Bayes
#define MODEL_TYPE 1


// Number of predictions used for timing
#define NUM_RUNS 100000

// Warm-up predictions
#define WARMUP_RUNS 1000


// ============================================================
// MODEL INCLUDES
// ============================================================

#if MODEL_TYPE == 1

    // ---------------- DECISION TREE ----------------

    #if TARGET == 0

        #include "fan_speed_model.h"

        Eloquent::ML::Port::DecisionTreeFan model;

    #elif TARGET == 1

        #include "light_intensity_model.h"

        Eloquent::ML::Port::DecisionTreeLight model;

    #endif


#elif MODEL_TYPE == 2

    // ---------------- NAIVE BAYES ----------------

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
// Feature order MUST match training exactly:
// Fan speed:       count, co2_level, temp, humidity   (4 features)
// Light intensity: count, co2_level, ldr_diff          (3 features)

#if TARGET == 0

    // FAN SPEED INPUT: count=15, co2_level=800, temp=32.0, humidity=60.0
    float input[] = {
        15.0,
        800.0,
        32.0,
        60.0
    };

#elif TARGET == 1

    // LIGHT INTENSITY INPUT: count=15, co2_level=800, ldr_diff=500
    float input[] = {
        15.0,
        800.0,
        500.0
    };

#endif


// ============================================================
// PRINT HEADER
// ============================================================

void printConfiguration() {

    Serial.println();
    Serial.println("==================================================");
    Serial.println("          ESP32 MACHINE LEARNING BENCHMARK");
    Serial.println("==================================================");

    Serial.print("Target: ");

    #if TARGET == 0
        Serial.println("Fan Speed");
    #elif TARGET == 1
        Serial.println("Light Intensity");
    #endif


    Serial.print("Model: ");

    #if MODEL_TYPE == 0
        Serial.println("Baseline");
    #elif MODEL_TYPE == 1
        Serial.println("Decision Tree");
    #elif MODEL_TYPE == 2
        Serial.println("Naive Bayes");
    #endif

    Serial.print("CPU Frequency: ");
    Serial.print(getCpuFrequencyMhz());
    Serial.println(" MHz");

    Serial.println("==================================================");
    Serial.println();
}


// ============================================================
// MEMORY INFORMATION
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
// FIRMWARE SIZE
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
// BASELINE BENCHMARK
// ============================================================

void runBaselineBenchmark() {

    Serial.println();
    Serial.println("BASELINE BUILD");
    Serial.println("No ML model is included.");

    printMemoryInfo("Baseline");

    Serial.println();
    Serial.println("No inference time is measured for baseline.");
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
    // MEMORY BEFORE WARM-UP
    // --------------------------------------------------------

    size_t heapBefore = ESP.getFreeHeap();
    size_t minHeapBefore = ESP.getMinFreeHeap();


    Serial.print("Free heap before benchmark: ");
    Serial.print(heapBefore);
    Serial.println(" bytes");


    // --------------------------------------------------------
    // WARM-UP
    // --------------------------------------------------------

    Serial.println();
    Serial.print("Running warm-up: ");
    Serial.print(WARMUP_RUNS);
    Serial.println(" predictions");

    for (int i = 0; i < WARMUP_RUNS; i++) {

        predictionResult = model.predict(input);

    }


    // --------------------------------------------------------
    // MEMORY AFTER WARM-UP
    // --------------------------------------------------------

    size_t heapAfterWarmup = ESP.getFreeHeap();


    // --------------------------------------------------------
    // INFERENCE TIME
    // --------------------------------------------------------

    Serial.println();
    Serial.print("Running benchmark: ");
    Serial.print(NUM_RUNS);
    Serial.println(" predictions");


    int64_t startTime = esp_timer_get_time();


    for (int i = 0; i < NUM_RUNS; i++) {

        predictionResult = model.predict(input);

    }


    int64_t endTime = esp_timer_get_time();


    int64_t totalTimeUs = endTime - startTime;


    double averageTimeUs =
        (double) totalTimeUs / NUM_RUNS;


    double averageTimeMs =
        averageTimeUs / 1000.0;


    // --------------------------------------------------------
    // MEMORY AFTER BENCHMARK
    // --------------------------------------------------------

    size_t heapAfter = ESP.getFreeHeap();
    size_t minHeapAfter = ESP.getMinFreeHeap();


    // --------------------------------------------------------
    // RESULTS
    // --------------------------------------------------------

    Serial.println();
    Serial.println("==================================================");
    Serial.println("                 BENCHMARK RESULTS");
    Serial.println("==================================================");


    // --------------------------------------------------------
    // INFERENCE TIME
    // --------------------------------------------------------

    Serial.println();
    Serial.println("[INFERENCE TIME]");

    Serial.print("Total time: ");
    Serial.print((long long) totalTimeUs);
    Serial.println(" us");

    Serial.print("Number of predictions: ");
    Serial.println(NUM_RUNS);

    Serial.print("Average inference time: ");
    Serial.print(averageTimeUs, 6);
    Serial.println(" us");

    Serial.print("Average inference time: ");
    Serial.print(averageTimeMs, 9);
    Serial.println(" ms");


    // --------------------------------------------------------
    // RAM / HEAP
    // --------------------------------------------------------

    Serial.println();
    Serial.println("[RAM / HEAP USAGE]");

    Serial.print("Free heap before: ");
    Serial.print(heapBefore);
    Serial.println(" bytes");

    Serial.print("Free heap after warm-up: ");
    Serial.print(heapAfterWarmup);
    Serial.println(" bytes");

    Serial.print("Free heap after benchmark: ");
    Serial.print(heapAfter);
    Serial.println(" bytes");

    Serial.print("Minimum free heap before: ");
    Serial.print(minHeapBefore);
    Serial.println(" bytes");

    Serial.print("Minimum free heap after: ");
    Serial.print(minHeapAfter);
    Serial.println(" bytes");


    int64_t heapDifference =
        (int64_t) heapBefore -
        (int64_t) heapAfterWarmup;


    Serial.print("Heap change after model execution: ");
    Serial.print(heapDifference);
    Serial.println(" bytes");


    // --------------------------------------------------------
    // LAST PREDICTION
    // --------------------------------------------------------

    Serial.println();
    Serial.println("[CHECK]");

    Serial.print("Last prediction: ");
    Serial.println(predictionResult);


    Serial.println();
    Serial.println("==================================================");
    Serial.println("               BENCHMARK COMPLETE");
    Serial.println("==================================================");
}


// ============================================================
// SETUP
// ============================================================

void setup() {

    Serial.begin(115200);

    delay(3000);

    printConfiguration();

    printFirmwareSize();

    printMemoryInfo("After boot");


    #if MODEL_TYPE == 0

        runBaselineBenchmark();

    #endif


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
