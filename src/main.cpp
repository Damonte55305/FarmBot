#include <WiFi.h>
#include <WebServer.h>
#include "ContenidoHTML.h"

#define motor_derecha_a 12
#define motor_derecha_b 14
#define enable_derecha 13
#define motor_izquierda_a 26
#define motor_izquierda_b 27
#define enable_izquierda 25
#define motor_medio_a 32
#define motor_medio_b 33

// Reemplaza estos con el nombre de tu red WiFi y la contraseña
const char* ssid     = "WiFi_FarmBot";
const char* password = "12345678";

// Crear un servidor web en el puerto 80
WebServer server(80);

// Función para manejar la ruta raíz "/"
void handleRoot() {
    ContenidoHTML html = *new ContenidoHTML();

    server.send(200, "text/html", html.obtenerContenido());
}

// Función para manejar la ruta "/LED_ON"
void avanzar() {
    digitalWrite (motor_derecha_a, HIGH);
    digitalWrite (motor_derecha_b, LOW);
    digitalWrite (motor_izquierda_a, HIGH);
    digitalWrite (motor_izquierda_b, LOW);
    analogWrite(enable_derecha, 180);
    analogWrite(enable_izquierda, 180);
}
void retroceder() {
    digitalWrite (motor_derecha_a, LOW);
    digitalWrite (motor_derecha_b, HIGH);
    digitalWrite (motor_izquierda_a, LOW);
    digitalWrite (motor_izquierda_b, HIGH);
    analogWrite(enable_derecha, 180);
    analogWrite(enable_izquierda, 180);
}
void girarALaDerecha() {
    digitalWrite (motor_derecha_a, LOW);
    digitalWrite (motor_derecha_b, HIGH);
    digitalWrite (motor_izquierda_a, HIGH);
    digitalWrite (motor_izquierda_b, LOW);
    analogWrite(enable_derecha, 255);
    analogWrite(enable_izquierda, 255);
}
void girarALaIzquierda() {
    digitalWrite (motor_derecha_a, HIGH);
    digitalWrite (motor_derecha_b, LOW);
    digitalWrite (motor_izquierda_a, LOW);
    digitalWrite (motor_izquierda_b, HIGH);
    analogWrite(enable_derecha, 255);
    analogWrite(enable_izquierda, 255);
}
void girarUnTiempo(){
    digitalWrite(motor_medio_a,HIGH);
    digitalWrite(motor_medio_b,LOW);
}

//función para apagar el motor
void parar(){
    digitalWrite (motor_derecha_a, LOW);
    digitalWrite (motor_derecha_b, LOW);
    digitalWrite (motor_izquierda_a, LOW);
    digitalWrite (motor_izquierda_b, LOW);
}


void setup() {
    // Inicializa el pin del LED como salida
    pinMode(motor_derecha_a, OUTPUT);
    pinMode(motor_derecha_b, OUTPUT);
    pinMode(enable_derecha, OUTPUT);
    pinMode(motor_izquierda_a, OUTPUT);
    pinMode(motor_izquierda_b, OUTPUT);
    pinMode(enable_izquierda, OUTPUT);
    pinMode(motor_medio_a, OUTPUT);
    pinMode(motor_medio_b, OUTPUT);
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



