#include <WiFi.h>
#include <WebServer.h>
#include "ContenidoHTML.h"
#include "Motor.h"
#include "ConfiguracionWiFi.h"
#include "SensorUltrasonico.h"

Motor *motor = new Motor();
ConfiguracionWiFi *configuracionWiFi = new ConfiguracionWiFi();
TaskHandle_t Task1;
SensorUltrasonico *sensor = new SensorUltrasonico();

// Crear un servidor web en el puerto 80
WebServer server(80);

// Función para manejar la ruta raíz "/"
void handleRoot() {
    ContenidoHTML html = *new ContenidoHTML();

    server.send(200, "text/html", html.obtenerContenido());
}

// Función para manejar la ruta "/LED_ON"
void avanzar() {
    motor->avanzar();
}

void avanzarAFull() {
    motor->avanzarAFull();
}

void retroceder() {
    motor->retroceder();
}

void retrocederAFull() {
    motor->retrocederAFull();
}

void girarALaDerecha() {
    motor->girarALaDerecha();

}

void girarALaIzquierda() {
    motor->girarALaIzquierda();

}

void girarUnTiempo() {
    motor->girarUnTiempo();
}

//función para apagar el motor
void parar() {
    motor->parar();
}


//Segundo loop para ejecutar las operaciones de sensado en el Core0.
void loop2(void *parameter){
    for(;;){
        sensor->sensar();
        delay(100);
    }
}

void setup() {
    Serial.begin(115200);
    xTaskCreatePinnedToCore(loop2,"Task1",1000,NULL,1,&Task1,0);

    // Inicializa el pin del LED como salida
    motor->inicializar();
    configuracionWiFi->inicializar();
    sensor->inicializar();

    // Configura las rutas del servidor web
    server.on("/", handleRoot);
    server.on("/AVANZAR", avanzar);
    server.on("/AVANZAR_A_FULL", avanzarAFull);
    server.on("/PARAR", parar);
    server.on("/RETROCEDER", retroceder);
    server.on("/RETROCEDER_A_FULL", retrocederAFull);
    server.on("/GIRO_DERECHA", girarALaDerecha);
    server.on("/GIRO_IZQUIERDA", girarALaIzquierda);
    server.on("/GIRO_MOTOR_MEDIO", girarUnTiempo);

    // Inicia el servidor web
    server.begin();
    Serial.println("Servidor HTTP iniciado");
}

void loop() {
    // Maneja las solicitudes entrantes
    server.handleClient();
}



