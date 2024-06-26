// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char SSID[]     = SECRET_SSID;    // Network SSID (name)
const char PASS[]     = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)

void onPingsChange();

int pings;

void initProperties(){

  ArduinoCloud.addProperty(pings, READWRITE, ON_CHANGE, onPingsChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
