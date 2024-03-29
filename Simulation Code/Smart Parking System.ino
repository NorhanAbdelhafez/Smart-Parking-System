/**
   ESP32 + DHT22 Example for Wokwi
   
   https://wokwi.com/arduino/projects/322410731508073042
*/
#define echoPin 12 // attach pin D2 Arduino to pin Echo of HC-SR04 -> digital pin
#define trigPin 13 //attach pin D3 Arduino to pin Trig of HC-SR04 ->digital pin
#define maxDistanceFromUltrasonic2
#define LEDPerGarageSpotPins[6] ={}
// defines variables
int duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
int availableGarageSpots[6] = {0,0,0,0,0,0};
void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  //WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  //while (WiFi.status() != WL_CONNECTED) {
     // delay(1000);
      //Serial.println("Connecting to WiFi..");
  //}

    //Serial.println("Connected to the WiFi network");
}

void loop() {
  
  Serial.println(findEmptySpot());
  Serial.println(checkIfGarageIsFull());
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * distanceFromUltrasonic2 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(50000);
}

void turnOnGarageSpotLEDs(){
   for (int index =0;index<6;index++){
     if (availableGarageSpots[index]==0){
       digitalWrite(LEDPerGarageSpotPins[index], HIGH);
     }
     else {
       digitalWrite(LEDPerGarageSpotPins[index], LOW);
     }
   }
}
bool checkIfGarageIsFull(){
   int availableSpot = findEmptySpot();
   if (availableSpot ==-1){
     return true;
   }
   return false;
}
int findEmptySpot(){
  for (int index = 0;index <6;index++){
    if (availableGarageSpots[index]==0){
      return index;
    }
  }
  return -1;
}



