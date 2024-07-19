//
// Created by Agustín on 27/06/2024.
//

#ifndef FARMBOT_SENSORULTRASONICO_H
#define FARMBOT_SENSORULTRASONICO_H

 /**
  * @brief Clase que se encarga de manejar los datos del sensor ultrasonico
  */
class SensorUltrasonico {
public:
    SensorUltrasonico();
    void inicializar();
    bool verificarDistancia(long distancia);
    bool sensar();

};


#endif //FARMBOT_SENSORULTRASONICO_H