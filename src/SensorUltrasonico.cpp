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

/**
 * @brief Sensa la distancia, es decir, calcula la distancia desde el sensor 
 * ultrasonico hasta el obstaculo, luego verifica y maneja el comportamiento del Buzzer
 */
bool SensorUltrasonico::sensar() {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    duration = pulseIn(ECHO, HIGH);
    distance = duration / 58.2;
    String distancia = String(distance);

    Serial.println("Distancia: " + distancia + " cm");

/**
 * @brief Controla el comportamiento del Buzzer dependiendo de la distancia sensada
 * @param distancia Distancia sensada
 */
    return verificarDistancia(distance);;
}

bool SensorUltrasonico::verificarDistancia(long distancia) {
    if(distancia == 0){
        return false;
    }else if (distancia <= 35) {
        return true;
    } else {
        return false;
    }
    delay(500);
}