#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

const int buzzerPin = 8;
const float threshold = 1.5; // Adjust this value according to the sensitivity you need

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Get accelerometer values
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  // Convert raw values to G's (1G = 9.8m/s^2)
  float gX = ax / 16384.0;
  float gY = ay / 16384.0;
  float gZ = az / 16384.0;

  // Calculate total acceleration vector magnitude
  float totalAcceleration = sqrt(gX * gX + gY * gY + gZ * gZ);

  // Check if the total acceleration exceeds the threshold
  if (totalAcceleration > threshold) {
    digitalWrite(buzzerPin, HIGH); // Turn on the buzzer/LED
  } else {
    digitalWrite(buzzerPin, LOW); // Turn off the buzzer/LED
  }

  // Print values to Serial Monitor for debugging
  Serial.print("X: "); Serial.print(gX);
  Serial.print(" Y: "); Serial.print(gY);
  Serial.print(" Z: "); Serial.print(gZ);
  Serial.print(" Total: "); Serial.println(totalAcceleration);

  delay(100);
}
