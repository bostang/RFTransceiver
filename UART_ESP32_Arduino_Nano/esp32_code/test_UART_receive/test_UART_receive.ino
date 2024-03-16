// esp32 sebagai penerima
void setup() {
  Serial.begin(9600); // Set the baud rate to match Arduino Nano
}

void loop() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();
    // Serial.print("Received from Arduino Nano: ");
    Serial.print(receivedChar);
  }
  // delay(1000);
  // Serial.println("Hello from ESP32!");
}
