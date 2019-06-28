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

/* gesetzte Einstellungen */

#define WIFI_NAME "DroneMaschien"

#define IP_ADDRESS IPAddress(192, 168, 187, 1)
#define SUBNET_MASK IPAddress(255, 255, 255, 0)

#define MOTOR_FL 5
#define MOTOR_FR 4
#define MOTOR_RL 0
#define MOTOR_RR 13

/* globale Variablen */

DNSServer dnsServer;

WebSocketsServer socketServer(187);

/* Socket-Event-Handler */

void handleWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    if(type != WStype_TEXT) {
        return;
    }

    switch((int) payload[0]) {
        case 48:
            digitalWrite(MOTOR_FL, LOW);
            digitalWrite(MOTOR_FR, LOW);
            digitalWrite(MOTOR_RL, LOW);
            digitalWrite(MOTOR_RR, LOW);
            break;
        case 49:
            digitalWrite(MOTOR_FL, HIGH);
            digitalWrite(MOTOR_FR, HIGH);
            digitalWrite(MOTOR_RL, HIGH);
            digitalWrite(MOTOR_RR, HIGH);
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
}
