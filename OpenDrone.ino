/**
 * OpenDrone
 * 
 * App-basierte Drohnen-Steuerung mit dem NodeMCU
 * 
 * Schul-Projekt 2019
 * 
 * Programm v0.0.1
 * 
 * (C) 2019 Jarne Jost
 */

/* Bibliotheken */

#include <Arduino.h>

#include <I2Cdev.h>
#include <MPU6050.h>

/* gesetzte Einstellungen */

#define SCL_PIN 14
#define SDA_PIN 12

/* globale Variablen */

MPU6050 mpu6050;

int16_t gx, gy, gz;

/* Kommunikation mit Gyro-Sensor */



/* Hauptfunktionen */

void setup() {
    Wire.begin(SDA_PIN, SCL_PIN);

    mpu6050.initialize();

    Serial.begin(9600);

    Serial.println(mpu6050.testConnection() ? "Verbindung zum MPU OK!" : "Verbindung zum MPU FEHLGESCHLAGEN!");
}

void loop() {
    //mpu6050.getRotation(&gx, &gy, &gz);
    mpu6050.getAcceleration(&gx, &gy, &gz); // TODO: Rotation und Acceleration wurden in der Library vertauscht !!!

    Serial.print(gx);
    Serial.print(" | ");
    Serial.print(gy);
    Serial.print(" | ");
    Serial.print(gz);
    Serial.println();

    delay(1000);
}
