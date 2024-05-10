/*
Sketch generated by the Arduino IoT Cloud Thing "Untitled"
  https://create.arduino.cc/cloud/things/6d28a7e1-2afb-406c-96ba-ab9aab1de73d

Arduino IoT Cloud Variables description

The following variables are automatically generated and updated when changes are made to the Thing

int pings;

Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
which are called when their values are changed from the Dashboard.
These functions are generated with the Thing and added at the end of this sketch.
*/
#include <WiFiS3.h>
#include "thingProperties.h"

int status = WL_IDLE_STATUS;
char ssid[] = SECRET_SSID;
WiFiClient client;

int motion = 0; //store IR value
int volume = 0; //store volume value

void setup() {
// Initialize serial and wait for port to open:
Serial.begin(9600);
// This delay gives the chance to wait for a Serial Monitor without blocking if none is found
delay(1500);
 
// Connect Sensors
pinMode(A0, INPUT); //IR sensor
pinMode(A1, INPUT); //volume sensor

// Defined in thingProperties.h
initProperties();

if (WiFi.status() == WL_NO_MODULE) {
Serial.println("Communication with WiFi module failed!");
// don't continue
while (true);
  }

//String fv = WiFi.firmwareVersion();
//if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
//Serial.println("Please upgrade the firmware");
  //}

// attempt to connect to WiFi network:
while (status != WL_CONNECTED) {
Serial.print("Attempting to connect to SSID: ");
Serial.println(ssid);
status = WiFi.begin(ssid);
// wait 10 seconds for connection:
delay(10000);
  }
Serial.println("Connected to WiFi");

// Connect to Arduino IoT Cloud
ArduinoCloud.begin(ArduinoIoTPreferredConnection);
 
  /*
The following function allows you to obtain more information
related to the state of network and IoT Cloud connection and errors
the higher number the more granular information you’ll get.
The default is 0 (only errors).
Maximum is 4
 */
setDebugMessageLevel(2);
ArduinoCloud.printDebugInfo();
 
pinMode(A0, INPUT); //IR sensor
pinMode(A1, INPUT); //volume sensor
}

void loop() {
ArduinoCloud.update();
motion = analogRead(A0);
volume = digitalRead(A1);

if (motion >= 200){
  Serial.print(motion);
  pings = 5;
  }
else if (volume == HIGH){
  pings = 1;
  }
else {
  pings = 0;
}
}


/*
Since Pings is READ_WRITE variable, onPingsChange() is
executed every time a new value is received from IoT Cloud.
*/
void onPingsChange() {
// Add your code here to act upon Pings change
Serial.print(pings);
}
