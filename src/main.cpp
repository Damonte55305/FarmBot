#include <WiFi.h>
#include <WebServer.h>
#include "ContenidoHTML.h"
#include "Motor.h"
#include "ConfiguracionWiFi.h"


Motor *motor = new Motor();
ConfiguracionWiFi *configuracionWiFi = new ConfiguracionWiFi();


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

void retroceder() {
    motor->retroceder();
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


void setup() {
    // Inicializa el pin del LED como salida

    motor->inicializar();
    configuracionWiFi->inicializar();

    // Configura las rutas del servidor web
    server.on("/", handleRoot);
    server.on("/AVANZAR", avanzar);
    server.on("/PARAR", parar);
    server.on("/RETROCEDER", retroceder);
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



