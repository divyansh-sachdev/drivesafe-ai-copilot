/**
 * DriveSafe ESP32 Companion — Haptic & Audio Driver Alert
 * Author: Divyansh Sachdev
 */

#include <Arduino.h>

#define BUZZER_PIN 23
#define MOTOR_PIN  22

void setup() {
    Serial.begin(115200);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(MOTOR_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(MOTOR_PIN, LOW);
    Serial.println("[READY] ESP32 Driver Safety Alert Unit online.");
}

void loop() {
    if (Serial.available()) {
        char cmd = Serial.read();
        if (cmd == 'A') { // Alert Trigger
            for (int i = 0; i < 3; i++) {
                digitalWrite(BUZZER_PIN, HIGH);
                digitalWrite(MOTOR_PIN, HIGH);
                delay(150);
                digitalWrite(BUZZER_PIN, LOW);
                digitalWrite(MOTOR_PIN, LOW);
                delay(100);
            }
        }
    }
}
