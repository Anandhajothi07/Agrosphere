 #include <SPI.h>
 #include <nRF24L01.h>
 #include <RF24.h>
 #define CE_PIN 9
 #define CSN_PIN 10
 
 
const uint64_t pipelane = 0xE8E8F0F0E1LL;
 
RF24 radio(CE_PIN, CSN_PIN);
float data[4];
int moisture = A0; 
int moist;
float moistper;
 
void setup()
 {
 Serial.begin(9600);
 radio.begin();
 radio.openWritingPipe(pipelane);
 pinMode(moisture,INPUT);
 
 }
 
void loop()
 {
 
 // read the value at analog input 
   moist = analogRead(moisture);
   moistper = ( 100 - ( (moist/1023.00) * 100 ) );
   Serial.println(moistper);

 
data[0] = 231;
data[1] = moistper;
//data[1] = 231;

radio.write( data, sizeof(data) );
Serial.println(data[1]);
delay(3000);
 }