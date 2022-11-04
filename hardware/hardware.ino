#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>

AsyncWebServer server(80);
DNSServer dnsServer;

class CaptiveRequestHandler : public AsyncWebHandler {
  public:
    CaptiveRequestHandler() {}
    virtual ~CaptiveRequestHandler() {}

    bool canHandle(AsyncWebServerRequest* request) {
      return true;
    }

    void handleRequest(AsyncWebServerRequest* request) {
      request->send(SPIFFS, "/www/index.html");
    }
};

void setupNetwork() {
  WiFi.softAP("RGB-Camera-Light");
  Serial.println("AP Started: ");
  Serial.println(WiFi.softAPIP());
  dnsServer.start(53, "*", WiFi.softAPIP());
}

void setupServer() {
  server.serveStatic("/", SPIFFS, "/www/").setDefaultFile("index.html").setCacheControl("max-age=60000");

  AsyncCallbackJsonWebHandler* restHandler =
  new AsyncCallbackJsonWebHandler("/rest/update", [](AsyncWebServerRequest * request, JsonVariant & json) {
    StaticJsonDocument<96> doc = json.as<JsonObject>();

    const char* key = doc["key"];
    const char* value = doc["value"];

    Serial.print(key);
    Serial.print(" => ");
    Serial.println(value);
    request->send(200);
  });

  server.addHandler(restHandler);

  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);

  server.begin();
}

void setup() {
  Serial.begin(9600);
  SPIFFS.begin();
  setupNetwork();
  setupServer();
}

void loop() {
  dnsServer.processNextRequest();
}
