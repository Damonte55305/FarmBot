//
// Created by walal on 20/6/2024.
//

#include "Motor.h"
#include <Arduino.h>


#define motor_derecha_a 12
#define motor_derecha_b 14
#define enable_derecha 13
#define motor_izquierda_a 26
#define motor_izquierda_b 27
#define enable_izquierda 25
#define motor_medio_a 32
#define motor_medio_b 33

Motor::Motor() = default;

void Motor::inicializar() {
    pinMode(motor_derecha_a, OUTPUT);
    pinMode(motor_derecha_b, OUTPUT);
    pinMode(enable_derecha, OUTPUT);
    pinMode(motor_izquierda_a, OUTPUT);
    pinMode(motor_izquierda_b, OUTPUT);
    pinMode(enable_izquierda, OUTPUT);
    pinMode(motor_medio_a, OUTPUT);
    pinMode(motor_medio_b, OUTPUT);
}

void Motor::avanzar() {
    digitalWrite(motor_derecha_a, HIGH);
    digitalWrite(motor_derecha_b, LOW);
    digitalWrite(motor_izquierda_a, HIGH);
    digitalWrite(motor_izquierda_b, LOW);
    analogWrite(enable_derecha, 180);
    analogWrite(enable_izquierda, 180);
}

void Motor::retroceder() {
    digitalWrite(motor_derecha_a, LOW);
    digitalWrite(motor_derecha_b, HIGH);
    digitalWrite(motor_izquierda_a, LOW);
    digitalWrite(motor_izquierda_b, HIGH);
    analogWrite(enable_derecha, 180);
    analogWrite(enable_izquierda, 180);

}

void Motor::girarALaDerecha() {
    digitalWrite(motor_derecha_a, LOW);
    digitalWrite(motor_derecha_b, HIGH);
    digitalWrite(motor_izquierda_a, HIGH);
    digitalWrite(motor_izquierda_b, LOW);
    analogWrite(enable_derecha, 255);
    analogWrite(enable_izquierda, 255);
}

void Motor::girarALaIzquierda() {
    digitalWrite(motor_derecha_a, HIGH);
    digitalWrite(motor_derecha_b, LOW);
    digitalWrite(motor_izquierda_a, LOW);
    digitalWrite(motor_izquierda_b, HIGH);
    analogWrite(enable_derecha, 255);
    analogWrite(enable_izquierda, 255);
}

void Motor::parar() {
    digitalWrite(motor_derecha_a, LOW);
    digitalWrite(motor_derecha_b, LOW);
    digitalWrite(motor_izquierda_a, LOW);
    digitalWrite(motor_izquierda_b, LOW);
}


void Motor::girarUnTiempo() {
    digitalWrite(motor_medio_a, HIGH);
    digitalWrite(motor_medio_b, LOW);
}
