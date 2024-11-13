#include <WiFi.h>
#include <WebServer.h>

// Configuración de la red Wi-Fi existente
const char* ssid = "SSID";     // Nombre de la red Wi-Fi
const char* password = "password";     // Contraseña de la red Wi-Fi

// Configuración del servidor
WebServer server(80);                    // Crea el servidor en el puerto 80

// Función para manejar la ruta raíz ("/")
void handleRoot() {
  // HTML básico para la página principal
  String html = "<html><head><title>SoyKhaler Server</title></head><body>";
  html += "<h1>Bienvenido a SoyKhaler Server</h1>";
  html += "<p>Este es el servidor web del ESP32. Puedes agregar mas contenido o enlaces aqui.</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);   // Enviar la página al cliente
}

void setup() {
  Serial.begin(115200);

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

  // Iniciar el servidor web
  server.begin();
  Serial.println("Servidor iniciado. Puedes acceder a él en la IP mostrada.");
}

void loop() {
  server.handleClient();                 // Gestiona las peticiones de los clientes
}
