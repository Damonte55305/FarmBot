#include <WiFi.h>
#include <WebServer.h>
#include "ContenidoHTML.h"
#include "Motor.h"


// Reemplaza estos con el nombre de tu red WiFi y la contraseña
const char *ssid = "WiFi_FarmBot";
const char *password = "12345678";
Motor *motor = new Motor();


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

    Serial.begin(115200);

    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("Dirección IP: ");
    Serial.println(IP);

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



