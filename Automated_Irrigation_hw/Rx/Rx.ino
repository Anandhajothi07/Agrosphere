 #include <SPI.h>
 #include <nRF24L01.h>
 #include <RF24.h>
 #define CE_PIN 9
 #define CSN_PIN 10
 
 const uint64_t pipe = 0xE8E8F0F0E1LL;
 
RF24 radio(CE_PIN, CSN_PIN);
float data[4]; // depending on the number of sensors used
 
unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;
 
float data1; 
float data2;

void setup()
 {
 Serial.begin(9600);
 delay(1000);
 Serial.println("Nrf24L01 Receiver Starting");
 radio.begin();
 radio.openReadingPipe(1,pipe);
 radio.startListening();
 }
 
void loop()
 {
 if ( radio.available() )
 {
 bool done = false;
 while (!done)
 {
 radio.read(data, sizeof(data));
 lastReceiveTime = millis(); // At this moment we have received the data
 
if (data[0] == 231) // header
{
  data1 = data[1];
  Serial.print("Data: ");
  Serial.println(data1);
}
  
delay(100);
 
 }
 }
 else
 {
currentTime = millis();
if ( currentTime - lastReceiveTime > 1000 ) { // If current time is more then 1 second since we have recived the last data, that means we have lost connection
 Serial.println("No data received for more than 1 second.");
 
 }
 }
 }
 