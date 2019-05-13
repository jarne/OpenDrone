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

/* gesetzte Einstellungen */

#define MOTOR_FL 12
#define MOTOR_FR 14
#define MOTOR_RL 0
#define MOTOR_RR 2

/* globale Variablen */



/* Hauptfunktionen */

void setup() {
    pinMode(MOTOR_FL, OUTPUT);
    pinMode(MOTOR_FR, OUTPUT);
    pinMode(MOTOR_RL, OUTPUT); 
    pinMode(MOTOR_RR, OUTPUT);
}

void loop() {
    digitalWrite(MOTOR_FL, HIGH);
    digitalWrite(MOTOR_FR, HIGH);
    digitalWrite(MOTOR_RL, HIGH);
    digitalWrite(MOTOR_RR, HIGH);

    delay(1000);
}
