/*
Senses motion and volume and sends this information to the pi via USB.
*/

int motion = 0; //store IR value
int volume = 0; //store volume value

void setup() {
  //put your setup code here, to run once:
  Serial.begin(9600);
  
  while (!Serial)  {}
  establishContact();

  pinMode(A8, INPUT); //IR sensor
  pinMode(A10, INPUT); //volume sensor
}

//If the serial connection is not ready, wait
void establishContact() {
  while (Serial.available() <= 0) {
    delay(300);
  }
}

/*
Right now:
The arduino uses a serial connection to send data to the pi

For later:
Each arduino is a client which connects to a python server running on the pi (no usb necessary)
https://www.arduino.cc/reference/en/libraries/wifi/
*/

void loop() {
  //put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
		motion = digitalRead(A8);
    volume = digitalRead(A10);

    if (motion == HIGH){
      //send high motion data point
      Serial.println("Motion: HIGH");
    }
    if (volume == HIGH){
      //send high volume data point
      Serial.println("Volume: HIGH");
    }
  }
}
