#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

// WiFi credentials
const char* ssid = "your_wifi_ssid";   // Replace with your Wi-Fi SSID
const char* password = "your_wifi_password";  // Replace with your Wi-Fi password

// DHT sensor setup
#define DHTPIN D4     // Pin where the DHT11 is connected (GPIO 2, D4)
#define DHTTYPE DHT11 // DHT 11 sensor type
DHT dht(DHTPIN, DHTTYPE);

// Server setup
String serverUrl = "http://localhost:8000/api/temperature/";  // URL of your Django API

// Function to send temperature data to the server
void sendTemperatureData(float temperature) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String fullUrl = serverUrl + String(temperature);  // Complete API endpoint

    http.begin(fullUrl);  // Specify destination for HTTP request
    int httpCode = http.GET();  // Send the GET request

    // Check response from the server
    if (httpCode > 0) {
      String response = http.getString();  // Get the response from the server
      Serial.println(httpCode);            // Print HTTP return code
      Serial.println(response);            // Print server response
    } else {
      Serial.println("Error in sending request");
    }
    http.end();  // Close connection
  } else {
    Serial.println("WiFi not connected");
  }
}

void setup() {
  // Initialize serial monitor
  Serial.begin(115200);

  // Initialize DHT sensor
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
}

void loop() {
  // Read temperature in Celsius from DHT11
  float temperature = dht.readTemperature();
  
  // Check if any reads failed
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Send temperature data to server
  sendTemperatureData(temperature);

  // Wait for a while before sending the next reading (e.g., 10 seconds)
  delay(10000);
}
