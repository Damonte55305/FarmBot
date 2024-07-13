/**
 * UnTref 2024
 * Laboratorio de Microprocesadores
 *
 * Proyecto: FarmBot
 * Integrantes:
 *  -Chazarreta, Gabriel Agustín
 *  -Damonte, Joel
 *  -Walter Julián Alfonso
 *  -Di Leo, Tomás
 *  -Deichmann, Ignacio
 *
 * Docentes:
 *  -Fossati, Jorge
 *  -Moreno Fernández, Joaquín
 */

#include <WiFi.h>
#include <WebServer.h>

#include "ContenidoHTML.h"
#include "Motor.h"
#include "ConfiguracionWiFi.h"
#include "SensorUltrasonico.h"

// Definicion del pin Buzzer y un metodo para hacer la inicializacion del FarmBot
#define BUZZ 4
#define LUZ 23
void buzz(int veces);

/*
Task1 es un proceso que se va a ejecutar en el segundo nucleo del ESP32 para controlar
el flujo de datos del sensor ultrasonico sin interferir en el control del FarmBot
*/
TaskHandle_t Task1;
SensorUltrasonico *sensor = new SensorUltrasonico();
Motor *motor = new Motor();
ConfiguracionWiFi *configuracionWiFi = new ConfiguracionWiFi();

WebServer server(80);

void manejarRutaRaiz()
{
    ContenidoHTML html = *new ContenidoHTML();
    server.send(200, "text/html", html.obtenerContenido());
}

//Funciones de control de los motores

void avanzar()
{
    motor->avanzar();
}

void avanzarAFull()
{
    motor->avanzarAFull();
}

void retroceder()
{
    motor->retroceder();
}

void retrocederAFull()
{
    motor->retrocederAFull();
}

void girarALaDerecha()
{
    motor->girarALaDerecha();
}

void girarALaIzquierda()
{
    motor->girarALaIzquierda();
}

void girarCortadora()
{
    motor->girarCortadora();
}

void parar()
{
    motor->parar();
}

//Funcion de control de la luz del FarmBot

void luz()
{
    digitalWrite(LUZ, HIGH);
    delay(100);
    digitalWrite(LUZ, LOW);
}

/**
 * @brief Loop infinito que se va a ejecutar en el segundo
 * nucleo del ESP32
 */
void loop2(void *parameter)
{
    for (;;)
    {
        sensor->sensar();
        delay(100);
    }
}

void setup()
{
    //Crea y asigna el task1 al segundo nucleo del ESP32 refiriendose al loop infinito "loop2" como funcion a ejecutar
    xTaskCreatePinnedToCore(loop2, "Task1", 8000, NULL, 1, &Task1, 0);

    pinMode(BUZZ, OUTPUT);
    pinMode(LUZ, OUTPUT);

    Serial.begin(115200);
    Serial.println("BEGIN");

    motor->inicializar();
    parar(); // Me aseguro que los motores estan parados antes de hacer cualquier otra cosa

    configuracionWiFi->inicializar();
    sensor->inicializar();

    delay(100);

    /*
    Inicio del robot
    Prueba de:
        Buzz
        Motores
    */

    buzz(10);

    avanzar();
    digitalWrite(LUZ, HIGH);
    delay(100);
    digitalWrite(LUZ, LOW);
    parar();
    delay(500);

    retroceder();
    digitalWrite(LUZ, HIGH);
    delay(100);
    digitalWrite(LUZ, LOW);
    parar();
    delay(500);

    girarALaDerecha();
    delay(100);
    parar();
    delay(500);

    girarALaIzquierda();
    delay(100);
    parar();
    delay(500);

    buzz(5);
    delay(10);

    // Configura las rutas, con sus funciones, que va a usar el servidor web para controlar el FarmBot
    server.on("/", manejarRutaRaiz);
    server.on("/AVANZAR", avanzar);
    server.on("/AVANZAR_A_FULL", avanzarAFull);
    server.on("/PARAR", parar);
    server.on("/RETROCEDER", retroceder);
    server.on("/RETROCEDER_A_FULL", retrocederAFull);
    server.on("/GIRO_DERECHA", girarALaDerecha);
    server.on("/GIRO_IZQUIERDA", girarALaIzquierda);
    server.on("/GIRO_MOTOR_MEDIO", girarCortadora);
    server.on("/FLASH", luz);

    // Inicia el servidor web
    server.begin();
}

void loop()
{
    // Maneja las solicitudes entrantes para controlar el FarmBot
    server.handleClient();
}

/**
 * @brief Activa de manera intermitente el Buzzer
 * @param veces cantidad de veces que se activa el buzzer
 */
void buzz(int veces)
{
    for (int i = 0; i < veces; i++)
    {
        digitalWrite(BUZZ, HIGH);
        delay(50);
        digitalWrite(BUZZ, LOW);
        delay(50);
    }
}