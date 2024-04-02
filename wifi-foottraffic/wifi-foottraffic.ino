//INCOMPLETE
//Based on example sketch "WiFi UDP Send and Receive String"

//need to remove serial outputs, configure to work with python script

#include <WiFiS3.h>
#include "arduino_secrets.h" // file for sensitive info

char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key index number (needed only for WEP)
unsigned int localPort = 2390;      // local port to listen on

WiFiUDP Udp;
int status = WL_IDLE_STATUS;

int motion = 0; //store IR value
int volume = 0; //store volume value

void setup() {
  pinMode(A0, INPUT); //IR sensor
  pinMode(A1, INPUT); //volume sensor

  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

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
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to WiFi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  Udp.begin(localPort);
}

void loop() {
  motion = digitalRead(A0);
  volume = digitalRead(A1);

  if (motion == HIGH){
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(motion);
    Udp.endPacket();
  }

  if (volume == HIGH){
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(volume);
    Udp.endPacket();
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