#include <WiFi.h>
#include <WebServer.h>

// Configuración de la red Wi-Fi que creará el ESP32
const char* ssid = "Hola Aaron";     // Nombre de la red Wi-Fi
const char* password = "";     // Contraseña de la red Wi-Fi

// Configuración del servidor
WebServer server(80);                    // Crea el servidor en el puerto 80

const int ledPin = 2; // Cambia esto al pin donde tienes conectado el LED

// Función para manejar la ruta raíz ("/")
void handleRoot() {
  String html = "<html><head><title>SoyKhaler Server</title></head><body>";
  html += "<h1>SoyKhaler Server Utility</h1>";
  html += "<p>Este es el servidor web del ESP32. Puedes agregar más contenido o enlaces aquí.</p>";
  html += "<a href=\"/led/on\"><button>Encender LED</button></a>";
  html += "<a href=\"/led/off\"><button>Apagar LED</button></a>";
  html += "</body></html>";

  server.send(200, "text/html", html);   // Enviar la página al cliente
}

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando Sistema");

  // Crear un punto de acceso Wi-Fi
  WiFi.softAP(ssid, password);
  Serial.print("Punto de acceso creado. Dirección IP: ");
  Serial.println(WiFi.softAPIP()); // Muestra la dirección IP del AP

  pinMode(ledPin, OUTPUT); // Configura el pin del LED como salida

  server.on("/", handleRoot); // Maneja la ruta raíz
  server.on("/led/on", []() {
    digitalWrite(ledPin, HIGH); // Enciende el LED
    server.send(200, "text/html", "LED encendido. <a href=\"/\">Volver</a>");
  });
  server.on("/led/off", []() {
    digitalWrite(ledPin, LOW); // Apaga el LED
    server.send(200, "text/html", "LED apagado. <a href=\"/\">Volver</a>");
  });

  server.begin();
  Serial.println("Servidor iniciado. Puedes acceder a él en la IP mostrada.");
}

void loop() {
  server.handleClient(); // Maneja las solicitudes del cliente
}
