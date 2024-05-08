#define Sober 120 // Define max value that we consider sober
#define Drunk 400 // Define min value that we consider drunk
#define MQ3pin 0

float sensorValue; //variable to store sensor value

void setup() {
  Serial.begin(9600); // sets the serial port to 9600
  Serial.println("MQ3 warming up!");
  delay(20000); // allow the MQ3 to warm up
}

void loop() {
  sensorValue = analogRead(MQ3pin); // read analog input pin 0
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  
  // Determine the status
  if (sensorValue < Sober) {
    Serial.println(" | Status: Stone Cold Sober");
  } else if (sensorValue >= Sober && sensorValue < Drunk) {
    Serial.println(" | Status: Drinking but within legal limits");
  } else {
    Serial.println(" | Status: DRUNK");
  }
  delay(2000); // wait 2s for next reading
}
