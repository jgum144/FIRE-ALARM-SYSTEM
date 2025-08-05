#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// --- Pin Definitions ---
const int flamePin = 34;    // Analog pin for the flame sensor
const int buzzerPin = 26;   // Digital pin for the buzzer
const int ledPin = 27;      // Digital pin for the LED

// --- Threshold Value ---
const int flameThreshold = 3000;

// --- Wi-Fi Credentials ---
const char* ssid = "GBCC Overseer";
const char* password = "LeadGulu291";

// --- Telegram Bot Credentials ---
#define BOT_TOKEN "8493294451:AAFjI3KvzkbNVrrC5orpCQuopeb4AylA8Ho"
#define CHAT_ID "1921644086" // Your personal chat ID

// --- Telegram Bot Instance ---
WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

bool fireDetected = false; // Flag to track the fire state

void setup() {
  Serial.begin(115200);

  // Set the pin modes for the output components
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // Ensure the alarms are off at startup
  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // For secure communication

  Serial.print("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  
  // Send a startup message to Telegram
  bot.sendMessage(CHAT_ID, "Fire alarm system is online!", "");
}

void loop() {
  // Read the analog value from the flame sensor
  int flameValue = analogRead(flamePin);
  Serial.print("Flame Sensor Value: ");
  Serial.println(flameValue);

  if (flameValue > flameThreshold) {
    // Fire detected 
    if (!fireDetected) { // Check if it's a new detection
      Serial.println("!!! FIRE DETECTED !!!");
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(ledPin, HIGH);
      
      // Send alert to Telegram
      String message = "🚨 **FIRE DETECTED!** 🚨\n\n";
      message += "Sensor Value: " + String(flameValue);
      bot.sendMessage(CHAT_ID, message, "Markdown");
      fireDetected = true; // Set flag to true
    }
  } else {
    // No flame
    if (fireDetected) { // Check if it was previously detected
      Serial.println("Fire all clear.");
      digitalWrite(buzzerPin, LOW);
      digitalWrite(ledPin, LOW);
      
      // Send "all clear" message to Telegram
      bot.sendMessage(CHAT_ID, "✅ **All clear.** The fire has been resolved.", "Markdown");
      fireDetected = false; // Reset flag
    }
  }

  // A small delay to prevent the loop from running too fast
  delay(500);
}