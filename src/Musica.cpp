#include "Musica.h"
#include <Arduino.h>

#define BUZZER_PIN 4


Musica::Musica(int* melody, int* durations, int size){
    this->melody = melody;
    this->durations = durations;
    this->size = size;
}

void Musica::reproducir(){
    for (int note = 0; note < this->size; note++) {
        int duration = 1000 / this->durations[note];

        tone(BUZZER_PIN, this->melody[note], duration);

        int pauseBetweenNotes = duration * 1.30;
        delay(pauseBetweenNotes);

        //stop the tone playing:
        noTone(BUZZER_PIN);
    }
}