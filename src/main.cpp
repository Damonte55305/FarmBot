#include <WiFi.h>
#include <WebServer.h>
#include "ContenidoHTML.h"
#include "Motor.h"
#include "ConfiguracionWiFi.h"
#include "SensorUltrasonico.h"
#include "pitches.h"
#include "Musica.h"

//BROWNOUT DETECT no esta desactivado en esta instancia
#include <soc/soc.h>
#include <soc/rtc_cntl_reg.h> 

#define BUZZ 4
#define LUZ 23
void buzz(int amount);

TaskHandle_t Task1;
SensorUltrasonico *sensor = new SensorUltrasonico();
Motor *motor = new Motor();
ConfiguracionWiFi *configuracionWiFi = new ConfiguracionWiFi();

int melody[] = {
  NOTE_C4, NOTE_E4, NOTE_FS4, REST, NOTE_A4,
  NOTE_G4, NOTE_E4, NOTE_C4, NOTE_A3,
  NOTE_FS3, NOTE_FS3, NOTE_FS3, NOTE_G3, REST,
  NOTE_FS3, NOTE_FS3, NOTE_FS3, NOTE_G3, NOTE_AS3,
  NOTE_B3, REST
};

int durations[] = {
  2, 4, 4, 32, 8,
  2, 4, 4, 8,
  8, 8, 8, 4, 2,
  8, 8, 8, 4, 2,
  2, 2
};
Musica *musica = new Musica(melody, durations, sizeof(durations) / sizeof(int));

// Crear un servidor web en el puerto 80
WebServer server(80);

// Función para manejar la ruta raíz "/"
void handleRoot()
{
    ContenidoHTML html = *new ContenidoHTML();

    server.send(200, "text/html", html.obtenerContenido());
}

// Función para manejar la ruta "/LED_ON"
void avanzar()
{
    motor->avanzar();
}

void avanzarAFull() {
    motor->avanzarAFull();
}

void retroceder()
{
    motor->retroceder();
}

void retrocederAFull() {
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

void girarUnTiempo()
{
    motor->girarUnTiempo();
}

// función para apagar el motor
void parar()
{
    motor->parar();
}

void luces(){
    digitalWrite(LUZ, HIGH);
    delay(100);
    digitalWrite(LUZ, LOW);
}

void loop2(void *parameter){
    for(;;){
        sensor->sensar();
        delay(100);
    }
}

void setup()
{
    musica->reproducir();
    xTaskCreatePinnedToCore(loop2,"Task1",8000,NULL,1,&Task1,0);
    pinMode(BUZZ, OUTPUT);
    pinMode(LUZ, OUTPUT);

    Serial.begin(115200);
    Serial.println("BEGIN");

    motor->inicializar();
    parar();

    configuracionWiFi->inicializar();
    sensor->inicializar();
    
    delay(100);

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
    server.on("/FLASH", luces);

    // Inicia el servidor web
    server.begin();
}

void loop()
{
    // Maneja las solicitudes entrantes
    server.handleClient();


}

void buzz(int amount){
    for(int i = 0; i < amount; i++){
        digitalWrite(BUZZ, HIGH);
        delay(50);
        digitalWrite(BUZZ, LOW);
        delay(50);
    }
}