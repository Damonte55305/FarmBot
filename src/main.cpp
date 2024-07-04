#include <WiFi.h>
#include <WebServer.h>
#include "ContenidoHTML.h"
#include "Motor.h"
#include "ConfiguracionWiFi.h"
#include "SensorUltrasonico.h"
#include "pitches.h"
#include "Musica.h"
#include "Dance.h"
#include "moves.h"

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

int secuencia[] = {
    IZQUIERDA, DERECHA, DERECHA, IZQUIERDA,
    IZQUIERDA, IZQUIERDA, IZQUIERDA, 
    DERECHA,
    DERECHA, DERECHA, DERECHA,
    IZQUIERDA,
    ATRAS, IZQUIERDA, DERECHA, DERECHA, IZQUIERDA, ADELANTE, 
    ATRAS, DERECHA, IZQUIERDA, IZQUIERDA, DERECHA, ADELANTE,
    IZQUIERDA, DERECHA, ADELANTE, ATRAS,
    DERECHA, IZQUIERDA, ATRAS, ADELANTE,
    DERECHA,
    IZQUIERDA, DERECHA, DERECHA, IZQUIERDA,
    IZQUIERDA, DERECHA, DERECHA, IZQUIERDA
};

int tiempos[] = {
    100, 100, 100, 100,
    50, 50, 100,
    200,
    50, 50, 100,
    200,
    100, 50, 50, 50, 50, 100,
    100, 50, 50, 50, 50, 100,
    100, 100, 50, 50,
    100, 100, 50, 50,
    1000,
    50, 50, 50, 50,
    50, 50, 50, 50
};

int sizeD = sizeof(tiempos) / sizeof(int);

int melody[] = {
  NOTE_A4, REST, NOTE_B4, REST, NOTE_C5, REST, NOTE_A4, REST,
  NOTE_D5, REST, NOTE_E5, REST, NOTE_D5, REST,

  NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_E5, NOTE_E5, REST,
  NOTE_D5, REST,

  NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_D5, NOTE_D5, REST,
  NOTE_C5, REST, NOTE_B4, NOTE_A4, REST,

  NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_D5, REST,
  NOTE_B4, NOTE_A4, NOTE_G4, REST, NOTE_G4, REST, NOTE_D5, REST, NOTE_C5, REST,

  NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_E5, NOTE_E5, REST,
  NOTE_D5, REST,

  NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_G5, NOTE_B4, REST,
  NOTE_C5, REST, NOTE_B4, NOTE_A4, REST,

  NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_D5, REST,
  NOTE_B4, NOTE_A4, NOTE_G4, REST, NOTE_G4, REST, NOTE_D5, REST, NOTE_C5, REST,

  NOTE_C5, REST, NOTE_D5, REST, NOTE_G4, REST, NOTE_D5, REST, NOTE_E5, REST,
  NOTE_G5, NOTE_F5, NOTE_E5, REST,

  NOTE_C5, REST, NOTE_D5, REST, NOTE_G4, REST
};

int durations[] = {
  8, 8, 8, 8, 8, 8, 8, 4,
  8, 8, 8, 8, 2, 2,

  8, 8, 8, 8, 2, 8, 8,
  2, 8,

  8, 8, 8, 8, 2, 8, 8,
  4, 8, 8, 8, 8,

  8, 8, 8, 8, 2, 8, 8,
  2, 8, 4, 8, 8, 8, 8, 8, 1, 4,

  8, 8, 8, 8, 2, 8, 8,
  2, 8,

  8, 8, 8, 8, 2, 8, 8,
  2, 8, 8, 8, 8,

  8, 8, 8, 8, 2, 8, 8,
  4, 8, 3, 8, 8, 8, 8, 8, 1, 4,

  2, 6, 2, 6, 4, 4, 2, 6, 2, 3,
  8, 8, 8, 8,

  2, 6, 2, 6, 2, 1
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
        musica->reproducir();
        vTaskDelete(&Task1);
    }
}

void setup()
{
    xTaskCreatePinnedToCore(loop2,"Task1",8000,NULL,1,&Task1,0);
    

    pinMode(BUZZ, OUTPUT);
    pinMode(LUZ, OUTPUT);

    Serial.begin(115200);
    Serial.println("BEGIN");

    motor->inicializar();

    for (int i = 0; i < sizeD; i++) {
        int duration = tiempos[i] * 4;
        int movimiento = secuencia[i];
        if(movimiento == 0){
            avanzar();
        }else if(movimiento == 1){
            girarALaDerecha();
        }else if(movimiento == 2){
            retroceder();
        }else if(movimiento == 3){
            girarALaIzquierda();
        }
        Serial.println("Moved");
        delay(duration);
        parar();
        delay(200);
    }

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