🔥 Smart Fire Alarm System with Telegram Alerts & Dashboard
This repository contains the code and documentation for a smart fire alarm system built using an ESP32 microcontroller. The system detects flames, triggers local audio-visual alarms (buzzer and LED), and sends real-time alerts to your Telegram account. Additionally, it can be integrated with an IoT dashboard (like Arduino Cloud) for remote monitoring.

✨ Features
Flame Detection: Utilizes an analog flame sensor to detect the presence of fire.

Local Alarms: Activates a buzzer and an LED for immediate, on-site notification.

Telegram Alerts: Sends instant notifications to a designated Telegram chat when fire is detected and an "all clear" message when the threat is resolved.

Remote Monitoring (Dashboard Ready): Designed to be easily integrated with IoT platforms (e.g., Arduino Cloud) for real-time sensor data visualization and system status monitoring from anywhere.

ESP32 Powered: Leverages the ESP32's Wi-Fi capabilities for internet connectivity.

🛠️ Components Used
To build this system, you'll need the following hardware:

ESP32 Development Board (e.g., ESP32-WROOM-32)

Flame Sensor (e.g., KY-026 or similar analog flame sensor)

Buzzer (active buzzer)

LED (any color)

Jumper Wires

Breadboard (optional, for prototyping)

USB Cable (for programming the ESP32)

💻 Software Setup
Arduino IDE
Install Arduino IDE: If you don't have it, download and install the Arduino IDE.

Install ESP32 Board Support:

Go to File > Preferences.

In "Additional Board Manager URLs", add: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

Go to Tools > Board > Boards Manager....

Search for "esp32" and install the "esp32 by Espressif Systems" package.

Install Libraries:

Go to Sketch > Include Library > Manage Libraries....

Search for and install:

Universal-Arduino-Telegram-Bot by Brian Lough

ArduinoJson by Benoit Blanchon

Telegram Bot Configuration
Create a Telegram Bot:

Open Telegram and search for @BotFather.

Start a chat with @BotFather and send /newbot.

Follow the instructions to give your bot a name and a username.

@BotFather will provide you with an HTTP API Token. Copy this token; you'll need it for the code.

Get Your Telegram Chat ID:

Open Telegram and search for @myidbot.

Start a chat with @myidbot and send /getid.

It will reply with your unique Chat ID. Copy this ID.

🔌 Circuit Diagram / Connections
Connect the components to your ESP32 as follows:

Flame Sensor:

VCC to 3.3V on ESP32

GND to GND on ESP32

AO (Analog Output) to GPIO 34 on ESP32

Buzzer:

Positive (+)  to GPIO 26 on ESP32

Negative (-)  to GND on ESP32

LED:

Anode (+)  to GPIO 27 on ESP32 (through a current-limiting resistor, e.g., 220 Ohm, though not explicitly in code)

Cathode (-)  to GND on ESP32

📄 Code Explanation
The fire_alarm_system.ino file (or similar name) contains the Arduino sketch for the ESP32.

Includes: Necessary libraries for Wi-Fi, secure client, Telegram bot, and JSON parsing.

Pin Definitions: Defines the GPIO pins for the flame sensor, buzzer, and LED.

Threshold Value: flameThreshold is a crucial value. You'll need to calibrate this for your specific sensor and environment. Read the flameValue from the Serial Monitor when there's no flame and when there's a flame, then choose a value in between.

Wi-Fi Credentials: Replace YOUR_WIFI_SSID and YOUR_WIFI_PASSWORD with your actual Wi-Fi network details.

Telegram Credentials: Replace YOUR_TELEGRAM_BOT_TOKEN and YOUR_TELEGRAM_CHAT_ID with the values you obtained from Telegram.

setup() Function:

Initializes Serial communication for debugging.

Sets up the buzzer and LED pins as outputs.

Connects the ESP32 to your Wi-Fi network.

Sends an initial "System Online" message to Telegram.

loop() Function:

Continuously reads the analog value from the flame sensor.

Compares the flameValue to the flameThreshold.

If a flame is detected (flameValue > flameThreshold):

Activates the buzzer and LED.

Sends a "FIRE DETECTED!" alert to Telegram (only once per detection event).

If no flame is detected:

Deactivates the buzzer and LED.

Sends an "All clear" message to Telegram (only once after a fire event).

Includes a delay(500) to prevent the loop from running too fast.

🚀 Usage
Upload the Code:

Open the .ino file in Arduino IDE.

Select your ESP32 board (Tools > Board > ESP32 Arduino > ESP32 Dev Module).

Select the correct COM Port (Tools > Port).

Click the "Upload" button.

Monitor:

Open the Serial Monitor (Tools > Serial Monitor) to see sensor readings and debug messages.

Observe the LED and buzzer for local alerts.

Check your Telegram chat for real-time notifications.

Calibration:

With no flame, note the Flame Sensor Value in the Serial Monitor.

Introduce a small, controlled flame (e.g., from a lighter) near the sensor and note the Flame Sensor Value.

Adjust the flameThreshold in your code to a value between these two readings. Re-upload the code after changes.
