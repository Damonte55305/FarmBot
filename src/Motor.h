//
// Created by walal on 20/6/2024.
//

#ifndef FARMBOT_MOTOR_H
#define FARMBOT_MOTOR_H

/**
 * @brief Clase que se encarga de controlar los cuatro motores
 * que corresponden a las ruedas y a un motor correspondiente a
 * la cortadora de maleza
 */
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
    void girarCortadora();
    void parar();
};

#endif //FARMBOT_MOTOR_H