//
// Created by Agustín on 27/06/2024.
//

#include "SensorUltrasonico.h"
#include <Arduino.h>

#define BuzzerPin 15
#define echoPin 5
#define trigPin 4

long duration, distance;

SensorUltrasonico::SensorUltrasonico() = default;

void SensorUltrasonico::inicializar() {
    Serial.begin(115200);
    pinMode(BuzzerPin, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void SensorUltrasonico::sensar() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = duration / 58.2;
    String distancia = String(distance);

    Serial.println("Distancia: "+distancia+" cm");
    verificarDistancia(distance);
}

void SensorUltrasonico::verificarDistancia(long distancia){
    if(distancia<30 && distancia>=15){
        tone(BuzzerPin, 500, 100);
    }
    if(distancia<15) {
        tone(BuzzerPin, 500, 500);
    }
    delay(500);
}