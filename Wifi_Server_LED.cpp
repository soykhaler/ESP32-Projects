#include <WiFi.h>
#include <WebServer.h>

// Configuración de la red Wi-Fi existente
const char* ssid = "ssid";     // Nombre de la red Wi-Fi
const char* password = "password";     // Contraseña de la red Wi-Fi

// Configuración del servidor
WebServer server(80);                    // Crea el servidor en el puerto 80

// Definir el pin del LED
const int ledPin = 2; // Cambia este número al pin que estés usando para el LED

// Función para manejar la ruta raíz ("/")
void handleRoot() {
  // HTML básico para la página principal
  String html = "<html><head><title>SoyKhaler Server</title></head><body>";
  html += "<h1>Bienvenido a SoyKhaler Server</h1>";
  html += "<p>Controla el LED:</p>";
  html += "<button onclick=\"location.href='/on'\">Encender LED</button>";
  html += "<button onclick=\"location.href='/off'\">Apagar LED</button>";
  html += "</body></html>";

  server.send(200, "text/html", html);   // Enviar la página al cliente
}

// Función para encender el LED
void handleLedOn() {
  digitalWrite(ledPin, HIGH); // Encender el LED
  handleRoot(); // Volver a mostrar la página principal
}

// Función para apagar el LED
void handleLedOff() {
  digitalWrite(ledPin, LOW); // Apagar el LED
  handleRoot(); // Volver a mostrar la página principal
}

void setup() {
  Serial.begin(115200);

  // Configurar el pin del LED como salida
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Asegurarse de que el LED esté apagado al inicio

  // Conectar el ESP32 a la red Wi-Fi existente
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado a la red WiFi.");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());        // Muestra la IP asignada al ESP32

  // Configura las rutas del servidor
  server.on("/", handleRoot);            // Ruta para la página principal
  server.on("/on", handleLedOn);        // Ruta para encender el LED
  server.on("/off", handleLedOff);      // Ruta para apagar el LED

  // Iniciar el servidor web
  server.begin();
  Serial.println("Servidor iniciado. Puedes acceder a él en la IP mostrada.");
}

void loop() {
  server.handleClient();                 // Gestiona las peticiones de los clientes
}
