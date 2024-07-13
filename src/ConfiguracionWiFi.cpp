//
// Created by walal on 21/6/2024.
//

#include <Arduino.h>
#include <WiFi.h>
#include "ConfiguracionWiFi.h"

// Nombre y contraseña de punto de acceso emitido por el ESP32
const char *ssid = "WiFi_FarmBot";
const char *password = "12345678";

void ConfiguracionWiFi::inicializar() {
    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
}

ConfiguracionWiFi::ConfiguracionWiFi() = default;
