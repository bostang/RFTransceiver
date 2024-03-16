// arduino uno sebagai pengirim

int i = 0;
void setup() {
  Serial.begin(9600); // Set the baud rate to match ESP32
}

void loop()
{
  Serial.println(i);
  i++;
  delay(1000);
}
