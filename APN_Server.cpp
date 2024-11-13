#include <WiFi.h>
#include <WebServer.h>


const char* ssid = "ESP32";     
const char* password = "";     


WebServer server(80);                   

const int ledPin = 2; 

void handleRoot() {
  String html = "<html><head><title>SoyKhaler Server</title></head><body>";
  html += "<h1>SoyKhaler Server Utility</h1>";
  html += "<p>Este es el servidor web del ESP32. Puedes agregar más contenido o enlaces aquí.</p>";
  html += "<a href=\"/led/on\"><button>Encender LED</button></a>";
  html += "<a href=\"/led/off\"><button>Apagar LED</button></a>";
  html += "</body></html>";

  server.send(200, "text/html", html);   
}

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando Sistema");


  WiFi.softAP(ssid, password);
  Serial.print("Punto de acceso creado. Dirección IP: ");
  Serial.println(WiFi.softAPIP()); 

  pinMode(ledPin, OUTPUT); 

  server.on("/", handleRoot); 
  server.on("/led/on", []() {
    digitalWrite(ledPin, HIGH); 
    server.send(200, "text/html", "LED encendido. <a href=\"/\">Volver</a>");
  });
  server.on("/led/off", []() {
    digitalWrite(ledPin, LOW); 
    server.send(200, "text/html", "LED apagado. <a href=\"/\">Volver</a>");
  });

  server.begin();
  Serial.println("Servidor iniciado. Puedes acceder a él en la IP mostrada.");
}

void loop() {
  server.handleClient(); 
}
