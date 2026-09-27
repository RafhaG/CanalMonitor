# CanalMonitor

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include "Base64.h"

const char* WIFI_SSID = "YOUR_WIFI";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

const char* GITHUB_TOKEN = "YOUR_GITHUB_TOKEN";

const char* GITHUB_USER = "YOUR_USERNAME";
const char* GITHUB_REPO = "CanalMonitor";

void uploadToGitHub(String jsonData, String filePath) {

  WiFiClientSecure client;
  client.setInsecure();  // Prototype only

  HTTPClient http;

  String url =
    "https://api.github.com/repos/" +
    String(GITHUB_USER) +
    "/" +
    String(GITHUB_REPO) +
    "/contents/" +
    filePath;

  http.begin(client, url);

  http.addHeader("Authorization", "Bearer " + String(GITHUB_TOKEN));
  http.addHeader("Accept", "application/vnd.github+json");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("User-Agent", "ESP32-Sensor");

  String encoded = base64::encode(jsonData);

  String payload =
    "{"
    "\"message\":\"Update sensor data\","
    "\"content\":\"" + encoded + "\""
    "}";

  int responseCode = http.PUT(payload);

  Serial.print("GitHub response: ");
  Serial.println(responseCode);

  Serial.println(http.getString());

  http.end();
}
