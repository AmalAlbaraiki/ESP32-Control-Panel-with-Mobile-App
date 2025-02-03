#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

WebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.print("Connecting to WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.print("Connected! IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/move", HTTP_GET, handleMove);

  server.begin();
}

void handleMove() {
  String direction = server.arg("direction");
  Serial.print("Received Direction: ");
  Serial.println(direction);

  if (direction == "forward") {
    Serial.println(" Forward");
  } else if (direction == "backward") {
    Serial.println(" Backward");
  } else if (direction == "left") {
    Serial.println(" Left");
  } else if (direction == "right") {
    Serial.println("Right");
  } else {
    Serial.println("Unknown Direction");
  }
  
  server.send(200, "text/plain", "Direction Received: " + direction);
}

void loop() {
  server.handleClient();
}
