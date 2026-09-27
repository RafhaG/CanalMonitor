#include <Arduino.h>
#include <WiFi.h>


const int H2S_PIN = 34; // GPIO 34 (ADC1_CH6)
// --- Calibration Values ---
// Voltage in clean air (Baseline Zero Voltage, usually around 0.4V)
const float ZERO_VOLTAGE = 0.142; 

// Sensitivity slope (Volts per PPM)
// Default for 0-100 ppm range with 0.4V to 2.0V output: (2.0V - 0.4V) / 100 ppm = 0.016 V/ppm
const float VOLTS_PER_PPM = 0.016; 

void setup() {
  Serial.begin(115200);
  analogReadResolution(12); // 0 to 4095
  WiFi.begin(ssid,password);
  Serial.print("connecting to wifi")
  while (WiFi.status() != WL_CONNECTED){
    delay(500)

  }

  Serial.println("=====================================");
  Serial.println("   H2S Gas Sensor Monitor Started    ");
  Serial.println("=====================================");
}

float readH2SVoltage() {
  long totalMV = 0;
  int samples = 20;

  for (int i = 0; i < samples; i++) {
    totalMV += analogReadMilliVolts(H2S_PIN);
    delay(10);
  }

  // Convert average millivolts to Volts
  return (totalMV / (float)samples) / 1000.0;
}

void loop() {
  float voltage = readH2SVoltage();

  // Calculate concentration: PPM = (Measured_V - Zero_V) / Slope
  float ppm = (voltage - ZERO_VOLTAGE) / VOLTS_PER_PPM;
  
  // Prevent negative readings in clean air due to minor noise
  if (ppm < 0) ppm = 0;

  // Print results
  Serial.print("Signal Voltage: ");
  Serial.print(voltage, 3);
  Serial.print(" V  |  H2S Concentration: ");
  Serial.print(ppm, 1);
  Serial.println(" PPM");

  delay(1000);
}