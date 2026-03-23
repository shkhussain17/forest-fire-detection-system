#define RXD2 20
#define TXD2 21

HardwareSerial hc12(1);

int led = 2;

void setup() {
  Serial.begin(115200);

  hc12.begin(9600, SERIAL_8N1, RXD2, TXD2);

  pinMode(led, OUTPUT);

  Serial.println("Receiver Started...");
}

void loop() {

  if (hc12.available()) {

    String data = hc12.readStringUntil('\n');

    Serial.print("Received: ");
    Serial.println(data);

    // Parse data
    float temp;
    int smoke;
    int flame;

    sscanf(data.c_str(), "%f,%d,%d", &temp, &smoke, &flame);

    Serial.print("Temp: ");
    Serial.println(temp);

    Serial.print("Smoke: ");
    Serial.println(smoke);

    Serial.print("Flame: ");
    Serial.println(flame);

    // 🔥 Fire Condition
    if (temp > 40 || smoke > 300 || flame == 0) {
      digitalWrite(led, HIGH);
      Serial.println("🔥 FIRE DETECTED");
    } else {
      digitalWrite(led, LOW);
      Serial.println("✅ SAFE");
    }
  }
}