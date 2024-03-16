#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

char received_message[64]; // Global variable to store received message

void displayTask(void * parameter) {
  (void)parameter;
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);

  while (true) {
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Update display every 1000 ms

    // Clear previous content
    display.clearDisplay();

    // Display received message
    display.print(received_message);

    // Refresh display
    display.display();
  }
}

void setup() {
  Serial.begin(9600); // Set the baud rate to match Arduino Nano

  // Create a task for OLED display
  xTaskCreatePinnedToCore(
    displayTask,          // Function to execute
    "displayTask",        // Name of the task
    4096,                 // Stack size (bytes)
    NULL,                 // Task input parameter
    1,                    // Priority (1 is highest priority)
    NULL,                 // Task handle
    0                     // Run on core 0
  );
}

void loop() {
  if (Serial.available() > 0) {
    // Read characters from serial port and store in received_message
    Serial.readBytesUntil('\n', received_message, sizeof(received_message));
    Serial.println(received_message);
  }
}
