#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Your_WiFi_NAME";
const char* password = "Your_WiFi_PASSWORD";

WebServer server(80);

#define RX_PIN 18
#define TX_PIN 19
HardwareSerial BusSerial(2);

#define HDR       0x55
#define CMD_MOVE  0x01
#define CMD_LOAD  0x1F

uint8_t chk(const uint8_t* b) {
  uint16_t s = 0;
  for (uint8_t i = 2; i < b[3] + 2; i++) s += b[i];
  return ~s;
}

void sendPack(uint8_t id, uint8_t cmd, const uint8_t* p, uint8_t n) {
  uint8_t buf[6 + n];
  buf[0] = buf[1] = HDR;
  buf[2] = id;
  buf[3] = n + 3;
  buf[4] = cmd;
  for (uint8_t i = 0; i < n; i++) buf[5 + i] = p[i];
  buf[5 + n] = chk(buf);
  BusSerial.write(buf, 6 + n);
}

void moveServo(uint8_t id, uint16_t angle) {
  if (angle > 1000) angle = 1000; 
  uint8_t pos[4] = { uint8_t(angle & 0xFF), uint8_t(angle >> 8), 100, 0 };
  sendPack(id, CMD_MOVE, pos, 4);
}

void handleMove() {
  if (server.hasArg("servo") && server.hasArg("angle")) {
    uint8_t servo = server.arg("servo").toInt();
    uint16_t angle = server.arg("angle").toInt();
    moveServo(servo, angle);
    server.send(200, "text/plain", "OK");
    Serial.printf("Servo %d → %d°\n", servo, angle);
  } else {
    server.send(400, "text/plain", "Missing parameters");
  }
}

void setup() {
  Serial.begin(115200);
  BusSerial.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/move", handleMove);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
