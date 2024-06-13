# ESP8266 Environmental Monitoring System with Database Storage

## Overview
This project demonstrates how to build an environmental monitoring system using the ESP8266 microcontroller. The system collects data from a DHT11 temperature and humidity sensor and a US016 ultrasonic distance sensor. The collected data is transmitted to a backend server and stored in a MySQL database. The stored data can be viewed on a web interface.

## Features
- Monitors temperature, humidity, and distance.
- Sends data to a MySQL database via a backend server.
- Displays stored sensor data on a web page.
- Uses ESP8266 for wireless connectivity.

## Hardware Requirements
- ESP8266 (NodeMCU)
- DHT11 Temperature and Humidity Sensor
- US016 Ultrasonic Distance Sensor
- Breadboard and jumper wires

## Software Requirements
- Arduino IDE
- MySQL Server
- PHP Server (e.g., XAMPP)
- Web browser to view the data

## Getting Started

### 1. Hardware Setup

#### Components:
- **DHT11 Sensor**:
  - VCC to 3.3V
  - GND to GND
  - Data to D4 (GPIO2)

- **US016 Sensor**:
  - VCC to 3.3V
  - GND to GND
  - Trigger to D5 (GPIO14)
  - Echo to D6 (GPIO12)

### 2. Software Setup

#### Arduino Code

1. **Install Arduino IDE**: [Download and install Arduino IDE](https://www.arduino.cc/en/software).

2. **Install Required Libraries**:
   - Open Arduino IDE.
   - Go to `Sketch > Include Library > Manage Libraries...`.
   - Search for and install the `DHT` library by Adafruit.
   - Ensure the `ESP8266WiFi` library is included (usually pre-installed with ESP8266 core).

3. **Upload the Code**:
   - Open the provided `ESP8266.ino` file in Arduino IDE.
   - Edit the Wi-Fi credentials in the code:
     ```cpp
     const char* ssid = "Your_SSID";
     const char* password = "Your_PASSWORD";
     ```
   - Replace `Your_SSID` and `Your_PASSWORD` with your Wi-Fi network name and password.
   - Replace `server` with your server's IP address and PHP script path:
     ```cpp
     const char* server = "http://192.168.x.x/midterm.php"; // Use your computer's local IP address
     ```
   - Select the appropriate board and port: `Tools > Board > NodeMCU 1.0` (or appropriate ESP8266 board).
   - Upload the code by clicking the `Upload` button.

#### PHP and MySQL Setup

1. **Install XAMPP** (or similar PHP/MySQL server):
   - [Download and install XAMPP](https://www.apachefriends.org/index.html).

2. **Start Apache and MySQL**:
   - Open XAMPP Control Panel.
   - Click `Start` next to Apache and MySQL.

3. **Create MySQL Database**:
   - Open phpMyAdmin by navigating to `http://localhost/phpmyadmin` in your browser.
   - Create a database named `EnvironmentalData`.
   - Create a table named `SensorReadings` with the following structure:
     ```sql
     CREATE TABLE SensorReadings (
         id INT AUTO_INCREMENT PRIMARY KEY,
         temperature FLOAT,
         humidity FLOAT,
         distance FLOAT,
         timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
     );
     ```

4. **Deploy PHP Script**:
   - Place the `midterm.php` script in the `htdocs` directory of your XAMPP installation (e.g., `C:\xampp\htdocs\`).
   - Ensure the PHP script can connect to the MySQL database with the correct credentials.

### 3. Running the Project

1. **Power the ESP8266**: Connect it to your computer via USB or a suitable power source.

2. **Monitor Serial Output**: 
   - Open the Serial Monitor in Arduino IDE (`Tools > Serial Monitor`).
   - Set the baud rate to `115200` to view debug information.

3. **View Data**:
   - Navigate to `http://localhost/midterm.php` in your web browser to see the stored sensor data.

## Troubleshooting

- **No Data in Database**:
  - Ensure the ESP8266 is correctly connected to Wi-Fi.
  - Verify the server IP address and path in the ESP8266 code.
  - Check the PHP script for errors in handling the incoming POST request.

- **Wi-Fi Connection Issues**:
  - Double-check the SSID and password.
  - Ensure the Wi-Fi network is available and the ESP8266 is within range.

- **PHP/MySQL Issues**:
  - Make sure Apache and MySQL are running in XAMPP.
  - Verify the database schema and that the PHP script has correct permissions.


## Acknowledgements
- Adafruit for the DHT library.
- Arduino for providing a robust development platform.
- XAMPP for simplifying local server setup.

