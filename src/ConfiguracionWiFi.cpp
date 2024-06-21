//
// Created by walal on 21/6/2024.
//

#include <Arduino.h>
#include <WiFi.h>
#include "ConfiguracionWiFi.h"

// Reemplaza estos con el nombre de tu red WiFi y la contraseña
const char *ssid = "WiFi_FarmBot";
const char *password = "12345678";

void ConfiguracionWiFi::inicializar() {

    Serial.begin(115200);

    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("Dirección IP: ");
    Serial.println(IP);
}

ConfiguracionWiFi::ConfiguracionWiFi() = default;
