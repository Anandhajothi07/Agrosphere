#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <SoftwareSerial.h>

// Pins for NRF24
#define CE_PIN 9
#define CSN_PIN 10

// SoftwareSerial pins
SoftwareSerial nanoSerial(2, 3); // RX (2), TX (3)

// NRF24 setup
const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(CE_PIN, CSN_PIN);

// Variables
float data[4];               // Array to hold incoming data
float soilMoisture = 0;      // Variable to store the received soil moisture data
unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;

void setup() {
  // Initialize serial communication for debugging and NodeMCU communication
  Serial.begin(9600);       // For debugging
  nanoSerial.begin(9600);   // Communication with NodeMCU

  // NRF24 setup
  Serial.println("Nrf24L01 Receiver Starting");
  radio.begin();
  radio.openReadingPipe(1, pipe); // Open reading pipe
  radio.startListening();         // Start listening for incoming data
  Serial.println("Setup complete");
}

void loop() {
  // Check for incoming data from NRF24
  if (radio.available()) {
    while (radio.available()) {
      radio.read(&data, sizeof(data)); // Read the incoming data
      lastReceiveTime = millis();

      // Check if the header matches the expected value
      if (data[0] == 231) {
        soilMoisture = data[1]; // Assign the second element as soil moisture
        Serial.print("Soil Moisture: ");
        Serial.println(soilMoisture);

        // Send the soil moisture data to the NodeMCU via SoftwareSerial
        nanoSerial.println(soilMoisture);
      }
    }
  } else {
    // Handle timeout for no data received
    currentTime = millis();
    if (currentTime - lastReceiveTime > 1000) {
      Serial.println("No data received for more than 1 second.");
    }
  }

  delay(100); // Small delay to prevent rapid looping
}
