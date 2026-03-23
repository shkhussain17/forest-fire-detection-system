#include <DHT.h>
#include <SoftwareSerial.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

SoftwareSerial hc12(10,11);

int flame = 3;
int smoke = A0;

void setup() {

  Serial.begin(9600);     // PC Serial Monitor
  hc12.begin(9600);       // HC-12 communication

  pinMode(flame, INPUT);

  dht.begin();

  Serial.println("Forest Fire Detection System Started");
}

void loop() {

  float temp = dht.readTemperature();
  int smokeValue = analogRead(smoke);
  int flameValue = digitalRead(flame);

  // Send data to HC-12
  String data = String(temp) + "," + String(smokeValue) + "," + String(flameValue);
  hc12.println(data);

  // Show data on PC Serial Monitor
  Serial.println("----- SENSOR STATUS -----");

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" C");

  Serial.print("Smoke Level: ");
  Serial.println(smokeValue);

  if(flameValue == LOW)
  {
    Serial.println("Flame: FIRE DETECTED");
  }
  else
  {
    Serial.println("Flame: No Fire");
  }

  Serial.println("--------------------------");

  delay(2000);
}