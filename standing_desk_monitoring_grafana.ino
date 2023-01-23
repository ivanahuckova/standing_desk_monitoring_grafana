#include <Arduino.h>
#include <PromLokiTransport.h>
#include <PrometheusArduino.h>
#include <DHT.h>
#include <HCSR04.h>

#include "certificates.h"
#include "config.h"


// Ultrasonic Sensor
UltraSonicDistanceSensor distanceSensor(ULTRASONIC_PIN_TRIG, ULTRASONIC_PIN_ECHO);  

// Prometheus client and transport
PromLokiTransport transport;
PromClient client(transport);

// Create a write request for 4 series
WriteRequest req(1, 512);

// Define a TimeSeries which can hold up to 5 samples
TimeSeries ts1(5, "height_centimeter", "{monitoring_type=\"standing_desk\",board_type=\"esp32_devkit1\"}");

float heightOfRoom = 246; // Height of room in centimeters
int loopCounter = 0;

// Function to set up Prometheus client
void setupClient() {
  Serial.println("Setting up client...");

  uint8_t serialTimeout;
  while (!Serial && serialTimeout < 50) {
    delay(100);
    serialTimeout++;
  }
  
  // Configure and start the transport layer
  transport.setUseTls(true);
  transport.setCerts(grafanaCert, strlen(grafanaCert));
  transport.setWifiSsid(WIFI_SSID);
  transport.setWifiPass(WIFI_PASSWORD);
  transport.setDebug(Serial);  // Remove this line to disable debug logging of the client.
  if (!transport.begin()) {
      Serial.println(transport.errmsg);
      while (true) {};
  }

  // Configure the client
  client.setUrl(GC_PROM_URL);
  client.setPath(GC_PROM_PATH);
  client.setPort(GC_PORT);
  client.setUser(GC_PROM_USER);
  client.setPass(GC_PROM_PASS);
  client.setDebug(Serial);  // Remove this line to disable debug logging of the client.
  if (!client.begin()) {
      Serial.println(client.errmsg);
      while (true) {};
  }

  // Add our TimeSeries to the WriteRequest
  req.addTimeSeries(ts1);
  req.setDebug(Serial);  // Remove this line to disable debug logging of the write request serialization and compression.
}


// ========== MAIN FUNCTIONS: SETUP & LOOP ========== 
// SETUP: Function called at boot to initialize the system
void setup() {
  Serial.begin(115200);
  setupClient();
}

// LOOP: Function called in a loop to read from sensors and send them do databases
void loop() {
  int64_t time;
  time = transport.getTimeMillis();

  float distance = distanceSensor.measureDistanceCm();
  // The sensor is pointed to ceiling, so we need to subtract the distance from height of room
  // to get correct height of standing desk
  float height = heightOfRoom - distance;

  // Check if any reads failed and exit early (to try again).
  if (isnan(height) ) {
    Serial.println(F("Failed to read from sensor!"));
    return;
  }
  

  if (loopCounter >= 5) {
    //Send
    loopCounter = 0;
    PromClient::SendResult res = client.send(req);
    if (!res == PromClient::SendResult::SUCCESS) {
      Serial.println(client.errmsg);
    }
    // Reset batches after a successful send.
    ts1.resetSamples();
  } else {
    if (!ts1.addSample(time, height)) {
      Serial.println(ts1.errmsg);
    }
    loopCounter++;
  }

  // wait INTERVAL seconds and then do it again
  delay(INTERVAL * 1000);
}

