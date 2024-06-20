#include <Arduino.h>
#include "Led.h"
#define LED 2

Led::Led(){

}

void Led::inicializar(){
    pinMode(LED, OUTPUT);
}

void Led::parpadear(){
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(200);
}
