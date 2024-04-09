//INCOMPLETE
//Based on example sketch "WiFi UDP Send and Receive String"

#include <WiFiS3.h>
#include "arduino_secrets.h" // file for sensitive info

int status = WL_IDLE_STATUS;

char ssid[] = SECRET_SSID;        // your network SSID (name)
int keyIndex = 0;            // your network key index number (needed only forWEP)

unsigned int localPort = 31415;      // local port to listen on
IPAddress server(137, 146, 126, 121);
WiFiClient client;

int motion = 0; //store IR value
int volume = 0; //store volume value

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  pinMode(A0, INPUT); //IR sensor
  pinMode(A1, INPUT); //volume sensor

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid);
    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to WiFi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  
  while (!client.connected()) {
    Serial.println("Connection failed");
    delay(10000);
    client.connect(server, localPort);
  }
  Serial.println("Connection successful!");
}

void loop() {
  motion = digitalRead(A0);
  volume = digitalRead(A1);

  if (motion == HIGH){
    client.write(motion);
    //Serial.println("MOTION");
  }

  if (volume == HIGH){
    client.write(volume);
    //Serial.println("VOLUME");
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}