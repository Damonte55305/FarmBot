//
// Created by walal on 20/6/2024.
//

#ifndef FARMBOT_MOTOR_H
#define FARMBOT_MOTOR_H

class Motor {
public:
    Motor();
    void inicializar();
    void avanzar();
    void avanzarAFull();
    void retroceder();
    void retrocederAFull();
    void girarALaDerecha();
    void girarALaIzquierda();
    void girarUnTiempo();
    void parar();
};

#endif //FARMBOT_MOTOR_H