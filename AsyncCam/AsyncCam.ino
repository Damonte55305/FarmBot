#include "AsyncCam.hpp"
#include <WiFi.h>

#define LED 33
#define FLASH_LED 4

#define WARNING_LED 12
#define SUCCESSFUL_LED 13

#define LUZ_SIGNAL 1

static const char* WIFI_SSID = "WiFi_FarmBot";
static const char* WIFI_PASS = "12345678";

esp32cam::Resolution initialResolution;
esp32cam::Resolution currentResolution;

AsyncWebServer server(80);

IPAddress staticIP(192, 168, 4, 186);
IPAddress gateway(192, 168, 4, 1);   
IPAddress subnet(255, 255, 0, 0); 
IPAddress dns(192, 168, 1, 1); 

bool luces_encendidas;

void WiFiEvent(WiFiEvent_t event) {
  switch(event) {
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());

      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("WiFi lost connection");
      flash(LED);
      flash(WARNING_LED);
      delay(50);
      ESP.restart();
      break;
    default:
      break;
  }
}

void
setup()
{
  pinMode(LED, OUTPUT);
  pinMode(FLASH_LED, OUTPUT);

  pinMode(WARNING_LED, OUTPUT);
  pinMode(SUCCESSFUL_LED, OUTPUT);

  pinMode(LUZ_SIGNAL, INPUT);

  luces_encendidas = false;

  WiFi.onEvent(WiFiEvent);

  Serial.begin(115200);
  Serial.println();
  delay(50);

  digitalWrite(LED, HIGH);
  digitalWrite(WARNING_LED, HIGH);
  digitalWrite(FLASH_LED, LOW);
  digitalWrite(SUCCESSFUL_LED, LOW);
  delay(500);

  if (WiFi.config(staticIP, gateway, subnet, dns, dns) == false) {
   Serial.println("Configuration failed.");
   delay(50);

   flash(FLASH_LED);

   ESP.restart();
  }

  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi failure");
    delay(5000);
    ESP.restart();
  }

  flash(SUCCESSFUL_LED);

  Serial.println("WiFi connected");

  {
    using namespace esp32cam;

    initialResolution = Resolution::find(1024, 768);
    currentResolution = initialResolution;

    Config cfg;
    cfg.setPins(pins::AiThinker);
    cfg.setResolution(initialResolution);
    cfg.setJpeg(80);

    bool ok = Camera.begin(cfg);
    if (!ok) {
      Serial.println("camera initialize failure");
      delay(5000);
      ESP.restart();
    }
    Serial.println("camera initialize success");
  }

  Serial.println("camera starting");
  Serial.print("http://");
  Serial.println(WiFi.localIP());

  addRequestHandlers();
  server.begin();

  digitalWrite(LED, LOW);
  digitalWrite(WARNING_LED, LOW);
  digitalWrite(SUCCESSFUL_LED, HIGH);
}

void
loop()
{
  int luz = digitalRead(LUZ_SIGNAL);
  delay(100);
  if(luz == HIGH){
    luces();
  }
}

void luces(){
    if(luces_encendidas){
        digitalWrite(FLASH_LED, LOW);
        Serial.println("Luz APAGADA");
        luces_encendidas = false;
    }else{
        digitalWrite(FLASH_LED, HIGH);
        Serial.println("Luz PRENDIDA");
        luces_encendidas = true;
    }
}

void flash(int PIN){
  for(int i = 0; i<3; i++){
    digitalWrite(PIN, HIGH);
    delay(200);
    digitalWrite(PIN, LOW);
    delay(200);
  }
  delay(250);
  for(int i = 0; i<3; i++){
    digitalWrite(PIN, HIGH);
    delay(200);
    digitalWrite(PIN, LOW);
    delay(200);
  }
}
