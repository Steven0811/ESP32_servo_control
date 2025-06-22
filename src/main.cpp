#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32-SERVO";
const char* password = "12345678";
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
    Serial.printf("Servo %d -> %d deg\n", servo, angle);
  } else {
    server.send(400, "text/plain", "Missing parameters");
  }
}

void setup() {
  Serial.begin(115200);
  BusSerial.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);

  WiFi.softAP(ssid, password);
  Serial.println("AP Ready. IP:");
  Serial.println(WiFi.softAPIP());

  server.on("/move", handleMove);
  server.begin();
}

void loop() {
  server.handleClient(); 
}