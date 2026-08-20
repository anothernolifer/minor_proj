#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include "fan_speed_model.h"
#include "light_intensity_model.h"

// =====================================================
// WiFi / MQTT CONFIG
// =====================================================

const char* ssid = "Roboticsclub-Dharan";
const char* password = "Dharan@Roboticsclub";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;   // ESP32 PubSubClient uses raw MQTT/TCP, not 8000

const char* sensor_topic = "esp32/sensordata";
const char* control_topic = "esp32/control";

WiFiClient espClient;
PubSubClient client(espClient);

// =====================================================
// PINS
// =====================================================

const int IR1_PIN = 23;
const int IR2_PIN = 22;
const int DHT_PIN = 4;

// ADC1 pins - safe to use while WiFi is active
const int LDR1_PIN = 34;   // inside room
const int LDR2_PIN = 36;   // outside room (labeled "VP" on most devkits)
const int CO2_PIN = 35;

// L298N - Fan (channel A)
const int FAN_ENA = 25;   // PWM speed
const int FAN_IN1 = 26;   // direction, fixed HIGH
const int FAN_IN2 = 27;   // direction, fixed LOW

// L298N - Light (channel B)
const int LIGHT_ENB = 33; // PWM speed
const int LIGHT_IN3 = 32; // direction, fixed HIGH
const int LIGHT_IN4 = 14; // direction, fixed LOW

#define DHT_TYPE DHT11

// =====================================================
// TIMING
// =====================================================

const unsigned long TIMEOUT = 2000;
const unsigned long DHT_INTERVAL = 2000;
const unsigned long AI_UPDATE_INTERVAL = 6000;

// =====================================================
// SENSOR / AI OBJECTS
// =====================================================

DHT dht(DHT_PIN, DHT_TYPE);

Eloquent::ML::Port::DecisionTreeFan fanModel;
Eloquent::ML::Port::DecisionTreeLight lightModel;

// =====================================================
// IR VARIABLES
// =====================================================

volatile int count = 0;

volatile bool ir1Flag = false;
volatile bool ir2Flag = false;

volatile unsigned long lastIr1 = 0;
volatile unsigned long lastIr2 = 0;

bool ir1Triggered = false;
bool ir2Triggered = false;

unsigned long ir1Time = 0;
unsigned long ir2Time = 0;

// =====================================================
// SENSOR VARIABLES
// =====================================================

float temperature = 0;
float humidity = 0;

unsigned long lastDhtRead = 0;
unsigned long lastAiUpdate = 0;

int ldrInside = 0;
int ldrOutside = 0;
int ldrDiff = 0;    // outside - inside; positive = outside brighter, needs light

int co2Level = 400;

// AI output: 0-4
int predictedFanSpeed = 0;
int predictedLightIntensity = 0;

// =====================================================
// MANUAL / AUTO CONTROL
// =====================================================

bool fanManual = false;
bool lightManual = false;

int manualFanSpeed = 0;
int manualLightIntensity = 0;

// =====================================================
// IR INTERRUPTS
// =====================================================

void IRAM_ATTR ir1ISR() {
  if (millis() - lastIr1 > 50) {
    ir1Flag = true;
    lastIr1 = millis();
  }
}

void IRAM_ATTR ir2ISR() {
  if (millis() - lastIr2 > 50) {
    ir2Flag = true;
    lastIr2 = millis();
  }
}

// =====================================================
// CO2 READING
// =====================================================

int readCO2() {
  int raw = analogRead(CO2_PIN);
  // Simplified mapping for class project. NOT calibrated CO2 ppm.
  return map(raw, 0, 4095, 200, 2500);
}

// =====================================================
// AI INFERENCE
// =====================================================

void runInference() {
  // Fan model: count, co2_level, temperature, humidity
  float fanFeatures[4] = {
    (float)count,
    (float)co2Level,
    temperature,
    humidity
  };

  // Light model: count, co2_level, ldr_diff
  float lightFeatures[3] = {
    (float)count,
    (float)co2Level,
    (float)ldrDiff
  };

  predictedFanSpeed = fanModel.predict(fanFeatures);
  predictedLightIntensity = lightModel.predict(lightFeatures);
}

// =====================================================
// ACTUATOR OUTPUT (L298N)
// =====================================================

void applyActuators() {
  int fanPercent = fanManual ? manualFanSpeed : (predictedFanSpeed * 25);
  int lightPercent = lightManual ? manualLightIntensity : (predictedLightIntensity * 25);

  fanPercent = constrain(fanPercent, 0, 100);
  lightPercent = constrain(lightPercent, 0, 100);

  ledcWrite(FAN_ENA, map(fanPercent, 0, 100, 0, 255));
  ledcWrite(LIGHT_ENB, map(lightPercent, 0, 100, 0, 255));
}

// =====================================================
// SERIAL STATUS
// =====================================================

void printStatus() {
  Serial.print("count : ");
  Serial.print(count);

  Serial.print(" , co2 : ");
  Serial.print(co2Level);

  Serial.print(" , temp : ");
  Serial.print(temperature, 1);

  Serial.print(" , humidity : ");
  Serial.print(humidity, 1);

  Serial.print(" , ldrIn : ");
  Serial.print(ldrInside);

  Serial.print(" , ldrOut : ");
  Serial.print(ldrOutside);

  Serial.print(" , ldrDiff : ");
  Serial.print(ldrDiff);

  Serial.print(" , fan_speed(lvl) : ");
  Serial.print(predictedFanSpeed);

  Serial.print(" , light_intensity(lvl) : ");
  Serial.print(predictedLightIntensity);

  Serial.print(" , fanManual : ");
  Serial.print(fanManual);

  Serial.print(" , lightManual : ");
  Serial.println(lightManual);
}

// =====================================================
// PUBLISH SENSOR DATA
// =====================================================

void publishSensorData() {
  if (!client.connected()) {
    Serial.println("MQTT not connected. Cannot publish.");
    return;
  }

  StaticJsonDocument<256> doc;

  doc["count"] = count;
  doc["temp"] = temperature;
  doc["humidity"] = humidity;
  doc["ldr"] = ldrDiff;      // Flutter's SensorReading still expects "ldr" key
  doc["co2"] = co2Level;

  int fanOutput = fanManual ? manualFanSpeed : predictedFanSpeed * 25;
  int lightOutput = lightManual ? manualLightIntensity : predictedLightIntensity * 25;

  doc["fan_speed"] = fanOutput;
  doc["light_intensity"] = lightOutput;

  doc["fan_manual"] = fanManual;
  doc["light_manual"] = lightManual;

  char buffer[256];
  size_t n = serializeJson(doc, buffer);

  bool success = client.publish(sensor_topic, buffer, n);

  if (success) {
    Serial.print("MQTT -> ");
    Serial.println(buffer);
  } else {
    Serial.println("MQTT publish failed!");
  }
}

// =====================================================
// MQTT CALLBACK
// =====================================================

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  StaticJsonDocument<128> doc;
  DeserializationError err = deserializeJson(doc, payload, length);

  if (err) {
    Serial.print("JSON parse failed: ");
    Serial.println(err.c_str());
    return;
  }

  bool stateChanged = false;

  if (doc.containsKey("fan")) {
    manualFanSpeed = constrain(doc["fan"].as<int>(), 0, 100);
    stateChanged = true;
  }

  if (doc.containsKey("light")) {
    manualLightIntensity = constrain(doc["light"].as<int>(), 0, 100);
    stateChanged = true;
  }

  if (doc.containsKey("fan_mode")) {
    fanManual = (String((const char*)doc["fan_mode"]) == "manual");
    stateChanged = true;
  }

  if (doc.containsKey("light_mode")) {
    lightManual = (String((const char*)doc["light_mode"]) == "manual");
    stateChanged = true;
  }

  Serial.print("MQTT <- ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if (stateChanged) {
    applyActuators();
    publishSensorData();
  }
}

// =====================================================
// MQTT RECONNECT
// =====================================================

void reconnectMqtt() {
  while (!client.connected()) {
    Serial.println();
    Serial.print("Connecting to MQTT...");

    String clientId = "ESP32SmartRoom-" + String((uint32_t)ESP.getEfuseMac(), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("connected");

      if (client.subscribe(control_topic)) {
        Serial.print("Subscribed to: ");
        Serial.println(control_topic);
      } else {
        Serial.println("MQTT subscribe failed!");
      }
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 2s");
      delay(2000);
    }
  }
}

// =====================================================
// WIFI CONNECTION
// =====================================================

void connectWiFi() {
  Serial.println();
  Serial.println("=== WiFi Connection ===");

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(500);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  unsigned long wifiStart = millis();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

    if (millis() - wifiStart > 15000) {
      Serial.println();
      Serial.print("WiFi connect FAILED, status code: ");
      Serial.println(WiFi.status());
      Serial.println("Retrying...");
      WiFi.disconnect();
      delay(1000);
      WiFi.begin(ssid, password);
      wifiStart = millis();
    }
  }

  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Signal strength: ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}

// =====================================================
// SETUP
// =====================================================

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("================================");
  Serial.println("     SMART ROOM ESP32");
  Serial.println("================================");

  // -------------------------------
  // IR sensors
  // -------------------------------
  pinMode(IR1_PIN, INPUT);
  pinMode(IR2_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(IR1_PIN), ir1ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(IR2_PIN), ir2ISR, FALLING);

  // -------------------------------
  // L298N - direction pins fixed one way (no reverse needed)
  // -------------------------------
  pinMode(FAN_IN1, OUTPUT);
  pinMode(FAN_IN2, OUTPUT);
  digitalWrite(FAN_IN1, HIGH);
  digitalWrite(FAN_IN2, LOW);

  pinMode(LIGHT_IN3, OUTPUT);
  pinMode(LIGHT_IN4, OUTPUT);
  digitalWrite(LIGHT_IN3, HIGH);
  digitalWrite(LIGHT_IN4, LOW);

  ledcAttach(FAN_ENA, 5000, 8);     // 5kHz PWM, 8-bit resolution
  ledcAttach(LIGHT_ENB, 5000, 8);

  // -------------------------------
  // DHT
  // -------------------------------
  dht.begin();
  delay(1000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (!isnan(h) && !isnan(t)) {
    humidity = h;
    temperature = t;
  } else {
    Serial.println("Initial DHT11 read failed - check wiring");
  }

  lastDhtRead = millis();

  // -------------------------------
  // Analog sensors
  // -------------------------------
  ldrInside = analogRead(LDR1_PIN);
  ldrOutside = analogRead(LDR2_PIN);
  ldrDiff = ldrOutside - ldrInside;

  co2Level = readCO2();

  // -------------------------------
  // Initial AI prediction + actuator output
  // -------------------------------
  runInference();
  applyActuators();

  // -------------------------------
  // WiFi
  // -------------------------------
  connectWiFi();

  // -------------------------------
  // MQTT
  // -------------------------------
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqttCallback);

  Serial.println();
  Serial.println("=== System Ready ===");
  printStatus();

  lastAiUpdate = millis();
}

// =====================================================
// LOOP
// =====================================================

void loop() {
  // ---------------- WIFI ----------------
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi dropped, reconnecting...");
    connectWiFi();
  }

  // ---------------- MQTT ----------------
  if (!client.connected()) {
    reconnectMqtt();
  }

  client.loop();

  unsigned long now = millis();

  // ---------------- IR1 EVENT ----------------
  if (ir1Flag) {
    ir1Flag = false;

    if (!ir1Triggered && !ir2Triggered) {
      ir1Triggered = true;
      ir1Time = now;
    } else if (ir2Triggered) {
      if (now - ir2Time <= TIMEOUT) {
        count--;
        if (count < 0) count = 0;
      }
      ir1Triggered = false;
      ir2Triggered = false;
    }
  }

  // ---------------- IR2 EVENT ----------------
  if (ir2Flag) {
    ir2Flag = false;

    if (!ir1Triggered && !ir2Triggered) {
      ir2Triggered = true;
      ir2Time = now;
    } else if (ir1Triggered) {
      if (now - ir1Time <= TIMEOUT) {
        count++;
      }
      ir1Triggered = false;
      ir2Triggered = false;
    }
  }

  // ---------------- IR TIMEOUT ----------------
  if (ir1Triggered && now - ir1Time > TIMEOUT) {
    ir1Triggered = false;
  }
  if (ir2Triggered && now - ir2Time > TIMEOUT) {
    ir2Triggered = false;
  }

  // ---------------- LDR (both sensors) ----------------
  int newLdrInside = analogRead(LDR1_PIN);
  int newLdrOutside = analogRead(LDR2_PIN);

  if (abs(newLdrInside - ldrInside) > 20 || abs(newLdrOutside - ldrOutside) > 20) {
    ldrInside = newLdrInside;
    ldrOutside = newLdrOutside;
    ldrDiff = ldrOutside - ldrInside;
  }

  // ---------------- CO2 ----------------
  int newCo2Level = readCO2();
  if (abs(newCo2Level - co2Level) > 30) {
    co2Level = newCo2Level;
  }

  // ---------------- DHT11 ----------------
  if (now - lastDhtRead >= DHT_INTERVAL) {
    lastDhtRead = now;

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (!isnan(h) && !isnan(t)) {
      humidity = h;
      temperature = t;
    } else {
      Serial.println("DHT11 read failed");
    }
  }

  // ---------------- AI + ACTUATORS + MQTT PUBLISH ----------------
  if (now - lastAiUpdate >= AI_UPDATE_INTERVAL) {
    lastAiUpdate = now;

    runInference();
    applyActuators();
    printStatus();
    publishSensorData();
  }
}