//
// Created by Agustín on 27/06/2024.
//

#include "SensorUltrasonico.h"
#include <Arduino.h>

#define BUZZER 4
#define ECHO 34
#define TRIG 5

long duration, distance;

SensorUltrasonico::SensorUltrasonico() = default;

void SensorUltrasonico::inicializar() {
    Serial.begin(115200);
    pinMode(BUZZER, OUTPUT);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
}

void SensorUltrasonico::sensar() {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    duration = pulseIn(ECHO, HIGH);
    distance = duration / 58.2;
    String distancia = String(distance);

    Serial.println("Distancia: "+distancia+" cm");
    verificarDistancia(distance);
}

void SensorUltrasonico::verificarDistancia(long distancia){
    if(distancia <= 10){
        tone(BUZZER, 200);
        delay(50);
        noTone(BUZZER);
    }else if(distancia > 10 && distancia <= 20){
        tone(BUZZER, 100);
        delay(150);
        noTone(BUZZER);
    }
    else if(distancia > 20 && distancia <= 30){
        tone(BUZZER, 50);
        delay(300);
        noTone(BUZZER);
    }
    delay(500);
}