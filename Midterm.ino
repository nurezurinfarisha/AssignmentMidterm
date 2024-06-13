#include <ESP8266WiFi.h>
#include <DHT.h>

#define DHTPIN D4      // Pin connected to the DHT sensor
#define DHTTYPE DHT11  // DHT 11

#define TRIGPIN D5     // Pin connected to the US016 Trigger
#define ECHOPIN D6     // Pin connected to the US016 Echo

const char* ssid = "Ezu";
const char* password = "ezu2142002";

const char* server = "http://localhost/midterm.php"; // Your backend server endpoint

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200); // Initialize serial communication
  dht.begin(); // Initialize the DHT sensor

  pinMode(TRIGPIN, OUTPUT); // Set TRIGPIN as an OUTPUT
  pinMode(ECHOPIN, INPUT);  // Set ECHOPIN as an INPUT

  // Connect to WiFi
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Reading DHT11 sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Reading US016 sensor
  long duration, distance;
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration / 2) / 29.1;

  // Printing values to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Send data to the server
  sendData(temperature, humidity, distance);

  delay(60000); // Delay 1 minute between readings
}

void sendData(float temperature, float humidity, long distance) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    // Change server to the IP address of your computer on the local network
    if (client.connect("172.20.10.3", 80)) { // Replace with your computer's local IP address
      String postData = "temperature=" + String(temperature) + "&humidity=" + String(humidity) + "&distance=" + String(distance);
      
      // Adjust the Host and POST lines
      client.println("POST /midterm.php HTTP/1.1"); // Relative path to the script
      client.println("Host: 172.20.10.3"); // Replace with your computer's local IP address
      client.println("Content-Type: application/x-www-form-urlencoded");
      client.println("Connection: close");
      client.println("Content-Length: " + String(postData.length()));
      client.println();
      client.println(postData);

      // Print the server response for debugging
      while (client.connected() || client.available()) {
        if (client.available()) {
          String line = client.readStringUntil('\n');
          Serial.println(line); // Print the response from the server
        }
      }

      client.stop(); // Close the connection
    } else {
      Serial.println("Failed to connect to server");
    }
  } else {
    Serial.println("WiFi not connected");
  }
}

