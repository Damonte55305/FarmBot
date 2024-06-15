#include <WiFi.h>
#include <WebServer.h>

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
    String html = "<!DOCTYPE html><html>";
    html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    html += "<style>";
    html += "body {";
    html += "  padding: 20px; /* Añade espacio alrededor del contenido */";
    html += "}";
    html += ".container {";
    html += "  display: flex;";
    html += "  justify-content: space-between; /* Distribuye los elementos a lo largo del contenedor */";
    html += "}";
    html += "button {";
    html += "  font-size: 24px; /* Cambia el tamaño de la letra */";
    html += "  color: white; /* Cambia el color del texto */";
    html += "  background-color: #4CAF50; /* Cambia el color de fondo */";
    html += "  border: none;";
    html += "  border-radius: 10px; /* Añade bordes redondeados */";
    html += "  padding: 15px 32px; /* Ajusta el espacio dentro del botón */";
    html += "  text-align: center;";
    html += "}";
    html += "</style>";
    html += "<script>";
    html += "function sendRequest(action) {";
    html += "    var xhttp = new XMLHttpRequest();";
    html += "    xhttp.onreadystatechange = function() {";
    html += "        if (this.readyState == 4 && this.status == 200) {";
    html += "            console.log(\"Respuesta del servidor:\", this.responseText);";
    html += "        }";
    html += "    };";
    html += "    xhttp.open('GET', action, true);";
    html += "    xhttp.send();";
    html += "}";
    html += "</script>";
    html += "</head>";

    html += "<img src=\"http://192.168.4.2/240x240.mjpeg\">";



    html += "<body>";
    html += "<h1 style=\"color: #14a741 ;text-align:center;\"> ---FarmBot---</h1>";

    html += "<table id=\"mainTable\" style=\"width:400px;margin:auto;table-layout:fixed\" CELLSPACING=10>";

    html += "<tr>";
    html += "<td class=\"button\" style=\"text-align: left;\">";
    html += "<div style=\"display: inline-block;\">";
    html += "<button style=\"background-color: white; color: black; border: none; box-shadow: none;\"> </button>";
    html += "</div>";
    html += "</td>";
    html += "<td class=\"button\" style=\"text-align: center;\">";
    html += "<div style=\"display: inline-block;\">";
    html += "<button style=\"background-color: #FFA500;\" ontouchstart=\"sendRequest('/AVANZAR'); this.style.backgroundColor = 'green';\" ontouchend=\"sendRequest('/PARAR'); this.style.backgroundColor = '#FFA500';\">&#9650;</button>";
    html += "</div>";
    html += "</td>";
    html += "</tr>";

    html += "<tr>";
    html += "<td class=\"button\" style=\"text-align: center;\">";
    html += "<div style=\"display: inline-block;\">";
    html += "<button style=\"background-color: #FFA500;\" ontouchstart=\"sendRequest('/GIRO_IZQUIERDA'); this.style.backgroundColor = 'green'; \" ontouchend=\"sendRequest('/PARAR'); this.style.backgroundColor = '#FFA500'\">&#9668;</button>";
    html += "</div>";
    html += "</td>";
    html += "<td class=\"button\" style=\"text-align: center;\">";
    html += "<div style=\"display: inline-block;\">";
    html += "<button style=\"background-color: #FFA500;\" ontouchstart=\"sendRequest('/GIRO_MOTOR_MEDIO'); this.style.backgroundColor = 'green'; \" ontouchend=\"this.style.backgroundColor = '#FFA500'\">&#9762;</button>";
    html += "</div>";
    html += "</td>";
    html += "<td class=\"button\" style=\"text-align: center;\">";
    html += "<div style=\"display: inline-block;\">";
    html += "<button style=\"background-color: #FFA500;\" ontouchstart=\"sendRequest('/GIRO_DERECHA'); this.style.backgroundColor = 'green'; \" ontouchend=\"sendRequest('/PARAR'); this.style.backgroundColor = '#FFA500'\">&#9658;</button>";
    html += "</div>";
    html += "</td>";
    html += "</tr>";

    html += "<tr>";
    html += "<td class=\"button\" style=\"text-align: left;\">";
    html += "<div style=\"display: inline-block;\">";
    html += "<button style=\"background-color: white; color: black; border: none; box-shadow: none;\"> </button>";
    html += "</div>";
    html += "</td>";
    html += "<td class=\"button\" style=\"text-align: center;\">";
    html += "<div style=\"display: inline-block;\">";
    html += "<button style=\"background-color: #FFA500;\" ontouchstart=\"sendRequest('/RETROCEDER'); this.style.backgroundColor = 'green';\" ontouchend=\"sendRequest('/PARAR'); this.style.backgroundColor = '#FFA500';\">&#9660;</button>";
    html += "</div>";
    html += "</td>";
    html += "</tr>";

    html += "</table>";
    html += "</body></html>";



    server.send(200, "text/html", html);
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



