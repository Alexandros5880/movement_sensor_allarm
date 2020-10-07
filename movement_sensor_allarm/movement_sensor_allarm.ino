#define switch_pin 2
#define bip_pin 4
#define move_pin 3
#define led_pin 13
#define trigPin 5
#define echoPin 6



int wait_seconds = 9; // Alarm delay

int delay_time = 10000;
long previusTime_main = 0;
int counter = 0;

// Bip Function
void bip();


// Ultra sonic function
int ultra_sonic();





void setup() {
  pinMode(switch_pin, OUTPUT);
  pinMode(bip_pin, OUTPUT);
  pinMode(move_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
  // Rele ON
  digitalWrite(switch_pin, HIGH);
  // Ultra Sonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}




void loop() {


  
  // Read sensor
  int mov = digitalRead( move_pin );
  boolean dist = ultra_sonic();

  // Ultrasonic Sensor
  if (dist) {
    counter = 0;
    digitalWrite(bip_pin, HIGH);
    Serial.println("Ultrasonic Sensor Alarm ON");
    digitalWrite(switch_pin, LOW);
    digitalWrite(led_pin, HIGH);
    long startTime = millis();
    while ( (millis()-startTime) <= 3000 );
  }
  /*
  // If movment sensor gets movement
  else if ( mov ) {
    bip(); // Bip Functio every time sensor see movement bip function is enable
    if ( (millis()-previusTime_main) >= 1000 ) {
      previusTime_main = millis();
      counter++;
      Serial.println("Wait Seconds: " + String(counter));
    } // If sensor gets movement under of 9 seonds Allarm On
    if ( (mov == 1) && (counter == wait_seconds) ) {
      counter = 0;
      Serial.println("Movement Sensor Alarm ON");
      digitalWrite(switch_pin, LOW);
      digitalWrite(led_pin, HIGH);
      long startTime = millis();
      while ( (millis()-startTime) <= 3000 );
    }
  } 
  */
  // OFF
  else {
    counter = 0;
    digitalWrite(trigPin, HIGH);
    digitalWrite(switch_pin, HIGH);
    digitalWrite(bip_pin, LOW);
    digitalWrite(led_pin, LOW);
  }
  
  
}








// Ultra sonic function
int distance_last = 0;

int ultra_sonic() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
  //Serial.println("Duration: " + String(duration));
  // Calculating the distance
  int distance = (duration*0.034)/2;
  //Serial.println("Distance: " + String(distance) + "  Last: " + String(distance_last));
  if ( (distance >= distance_last+200) || (distance <= distance_last-200)  ) {
    distance_last = distance;
    return 1;
  } else {
    return 0;
  }

}






// Bip Function
long previusTime = 0;
int wait = 77;
boolean bip_on = true;


void bip() {
  if ( (millis()-previusTime) >= wait ) {
    previusTime = millis();
    bip_on = !bip_on;
  }
  digitalWrite(bip_pin, bip_on);
}
