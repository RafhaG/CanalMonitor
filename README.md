# CanalMonitor
![Uploading image_4d113d40.jpg…]()


configTime(7 * 3600, 0, "pool.ntp.org", "time.nist.gov");

String getTimestampFilename() {
  struct tm timeinfo;

  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to get time");
    return "data/unknown.json";
  }

  char filename[50];

  strftime(
    filename,
    sizeof(filename),
    "data/%Y-%m-%d_%H-%M.json",
    &timeinfo
  );

  return String(filename);
}

String jsonData = R"({
  "device": "esp32-01",
  "timestamp": "2026-09-27T15:00:00Z",
  "ph": 6.82,
  "h2s_ppm": 2.14,
  "methane_ppm": 184,
  "temperature_c": 28.4,
  "humidity_percent": 71.2,
  "co2_ppm": 618,
  "dissolved_oxygen_mg_l": 7.31
})";

String filename = getTimestampFilename();

uploadToGitHub(
  jsonData,
  filename
);
