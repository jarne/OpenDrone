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

#include <ESP8266WiFi.h>

#include <DNSServer.h>

#include <WebSocketsServer.h>

/* Netzwerk-Einstellungen */

#define WIFI_NAME "DroneMaschien"

#define IP_ADDRESS IPAddress(192, 168, 187, 1)
#define SUBNET_MASK IPAddress(255, 255, 255, 248)

/* Belegungs-Einstellungen */

#define MOTOR_FL 5
#define MOTOR_FR 4
#define MOTOR_RL 0
#define MOTOR_RR 13

/* Motor-Ausgleichs-Einstellungen */

#define FAC_FL 1
#define FAC_FR 1
#define FAC_RL 1
#define FAC_RR 1

/* globale Variablen */

DNSServer dnsServer;

WebSocketsServer socketServer(187);

int zustand = 0;

int derzGeschw = 0;

/* Motoren-Ansteuerung */

void adjustMotorSpeed(int newSpeed) {
    analogWrite(MOTOR_FL, newSpeed * FAC_FL);
    analogWrite(MOTOR_FR, newSpeed * FAC_FR);
    analogWrite(MOTOR_RL, newSpeed * FAC_RL);
    analogWrite(MOTOR_RR, newSpeed * FAC_RR);
}

/* Socket-Event-Handler */

void handleWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    if(type != WStype_TEXT) {
        return;
    }

    switch((int) payload[0]) {
        case 48: // stoppen
            switch(zustand) {
                case 1:
                    zustand = 3;
                    break;
                case 2:
                    zustand = 3;
                    break;
            }
            break;
        case 49: // starten
            switch(zustand) {
                case 0:
                    zustand = 1;
                    break;
            }
            break;
    }
}

/* Hauptfunktionen */

void setup() {
    WiFi.mode(WIFI_AP);

    WiFi.softAPConfig(IP_ADDRESS, IP_ADDRESS, SUBNET_MASK);
    WiFi.softAP(WIFI_NAME);

    dnsServer.start(53, "*", IP_ADDRESS);

    socketServer.onEvent(handleWebSocketEvent);

    socketServer.begin();

    pinMode(MOTOR_FL, OUTPUT);
    pinMode(MOTOR_FR, OUTPUT);
    pinMode(MOTOR_RL, OUTPUT); 
    pinMode(MOTOR_RR, OUTPUT);
}

void loop() {
    dnsServer.processNextRequest();

    socketServer.loop();

    switch(zustand) {
        case 0:
            digitalWrite(MOTOR_FL, LOW);
            digitalWrite(MOTOR_FR, LOW);
            digitalWrite(MOTOR_RL, LOW);
            digitalWrite(MOTOR_RR, LOW);
            break;
        case 1:
            if(derzGeschw < 511) {
                derzGeschw++;

                adjustMotorSpeed(derzGeschw);

                delay(5);

                return;
            }

            zustand = 2;
            break;
        case 3:
            if(derzGeschw > 0) {
                derzGeschw--;

                adjustMotorSpeed(derzGeschw);

                delay(2);

                return;
            }

            zustand = 0;
            break;
    }
}
