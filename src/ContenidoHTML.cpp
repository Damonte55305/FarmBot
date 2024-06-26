#include <Arduino.h>
#include "ContenidoHTML.h"


ContenidoHTML::ContenidoHTML()= default;

String ContenidoHTML::obtenerContenido() {
    return html();
}

String ContenidoHTML::html() {
    String html = "<!DOCTYPE html><html>"
    "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
    "<style>"
    "body {padding: 20px; /* Añade espacio alrededor del contenido */}"
    ".container {"
    "  display: flex;"
    "  justify-content: space-between; /* Distribuye los elementos a lo largo del contenedor */"
    "}"
    "button {"
    "  font-size: 24px; /* Cambia el tamaño de la letra */"
    "  color: white; /* Cambia el color del texto */"
    "  background-color: #4CAF50; /* Cambia el color de fondo */"
    "  border: none;"
    "  border-radius: 10px; /* Añade bordes redondeados */"
    "  padding: 15px 32px; /* Ajusta el espacio dentro del botón */"
    "  text-align: center"
    "  user-select: none;"
    "  -webkit-user-select: none;"
    "  -moz-user-select: none;"
    "  -ms-user-select: none;}"
    "</style>"
    "<script>"
    "function sendRequest(action) {"
    "    var xhttp = new XMLHttpRequest();"
    "    xhttp.onreadystatechange = function() {"
    "        if (this.readyState == 4 && this.status == 200) {"
    "            console.log(\"Respuesta del servidor:\", this.responseText);"
    "        }"
    "    };"
    "    xhttp.open('GET', action, true);"
    "    xhttp.send();"
    "}"
    "</script>"
    "</head>"

    "<img src=\"http://192.168.4.2/240x240.mjpeg\">"

    "<body>"
    "<h1 style=\"color: #14a741 ;text-align:center;\"> ---FarmBot---</h1>"

    "<table id=\"mainTable\" style=\"width:400px;margin:auto;table-layout:fixed\" CELLSPACING=10>"

    "<tr>"
    "<td class=\"button\" style=\"text-align: left;\">"
    "<div style=\"display: inline-block;\">"
    "<button style=\"background-color: white; color: black; border: none; box-shadow: none;\"> </button>"
    "</div>"
    "</td>"
    "<td class=\"button\" style=\"text-align: center;\">"
    "<div style=\"display: inline-block;\">"
    "<button style=\"background-color: #FFA500;\" ontouchstart=\"sendRequest('/AVANZAR'); this.style.backgroundColor = 'green';\" ontouchend=\"sendRequest('/PARAR'); this.style.backgroundColor = '#FFA500';\">&#9650;</button>"
    "</div>"
    "</td>"
    "</tr>"

    "<tr>"
    "<td class=\"button\" style=\"text-align: center;\">"
    "<div style=\"display: inline-block;\">"
    "<button style=\"background-color: #FFA500;\" ontouchstart=\"sendRequest('/GIRO_IZQUIERDA'); this.style.backgroundColor = 'green'; \" ontouchend=\"sendRequest('/PARAR'); this.style.backgroundColor = '#FFA500'\">&#9668;</button>"
    "</div>"
    "</td>"
    "<td class=\"button\" style=\"text-align: center;\">"
    "<div style=\"display: inline-block;\">"
    "<button style=\"background-color: #FFA500;\" ontouchstart=\"sendRequest('/GIRO_MOTOR_MEDIO'); this.style.backgroundColor = 'green'; \" ontouchend=\"this.style.backgroundColor = '#FFA500'\">&#9762;</button>"
    "</div>"
    "</td>"
    "<td class=\"button\" style=\"text-align: center;\">"
    "<div style=\"display: inline-block;\">"
    "<button style=\"background-color: #FFA500;\" ontouchstart=\"sendRequest('/GIRO_DERECHA'); this.style.backgroundColor = 'green'; \" ontouchend=\"sendRequest('/PARAR'); this.style.backgroundColor = '#FFA500'\">&#9658;</button>"
    "</div>"
    "</td>"
    "</tr>"

    "<tr>"
    "<td class=\"button\" style=\"text-align: left;\">"
    "<div style=\"display: inline-block;\">"
    "<button style=\"background-color: white; color: black; border: none; box-shadow: none;\"> </button>"
    "</div>"
    "</td>"
    "<td class=\"button\" style=\"text-align: center;\">"
    "<div style=\"display: inline-block;\">"
    "<button style=\"background-color: #FFA500;\" ontouchstart=\"sendRequest('/RETROCEDER'); this.style.backgroundColor = 'green';\" ontouchend=\"sendRequest('/PARAR'); this.style.backgroundColor = '#FFA500';\">&#9660;</button>"
    "</div>"
    "</td>"
    "</tr>"
    "</table>"
    "</body></html>";
    return html;
}

