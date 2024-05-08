#include <SoftwareSerial.h>

SoftwareSerial mySerial(1, 0); // Rx Tx

void setup() {
  Serial.begin(9600);
  delay(100);
}

void loop() {
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CMGS=\"+919699688519\"\r");
  delay(1000);
  Serial.println("Hello");
  delay(100);
  Serial.println((char)26);
  delay(1000);
}
