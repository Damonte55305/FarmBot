#include <Arduino.h>
#include "ContenidoHTML.h"


ContenidoHTML::ContenidoHTML()= default;

String ContenidoHTML::obtenerContenido() {
    return html();
}

String ContenidoHTML::html() {
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
    return html;
}

