#ifndef DANCE_H
#define DANCE_H
#include "Motor.h"

class Dance {
public:
    Dance(int* secuencia, int* tiempos, int sizeD, Motor *motor);
    void bailar();

private:
    Motor *motor;
    int* secuencia;
    int* tiempos;
    int size;
};

#endif //DANCE_H