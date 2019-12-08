#include <NewPingESP8266.h>

#define STBY 15
#define AIN1 3
#define AIN2 12
#define BIN1 0
#define BIN2 2
#define PWM 14
#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 20 // Maximum distance (in cm) to ping.

NewPingESP8266 sonar[SONAR_NUM] = {   // Sensor object array.
  NewPingESP8266(5, 13, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPingESP8266(5, 16, MAX_DISTANCE), 
  NewPingESP8266(5, 4, MAX_DISTANCE)
};

int distance[3];

void setup() {
  pinMode(STBY, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWM, OUTPUT);
  analogWrite(PWM, 510);
  //Serial.begin(9600);
}

void loop() { 
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(30); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    distance[i] = sonar[i].ping_cm();
  }
  if(distance[0]!=0 && distance[1]!=0 && distance[2]==0)
  {
    turn_right();
  }
  else if(distance[0]!=0 && distance[1]==0 && distance[2]==0){
    turn_right();
  }
  else if(distance[0]==0 && distance[1]!=0 && distance[2]==0){
    turn_right();
  }
  else if(distance[0]==0 && distance[1]!=0 && distance[2]!=0){
    turn_left();
  }
  else if(distance[0]==0 && distance[1]==0 && distance[2]!=0){
    turn_left();
  }
  //while(distance[0]!=0 && distance[1]==0 && distance[2]!=0){
    //move_forward();
  //}
  else if(distance[0]!=0 && distance[1]!=0 && distance[2]!=0){
    stop_motor();
  }
  else {
  move_forward();
  }
}

void move_forward(){
  digitalWrite(STBY, HIGH);
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN2, LOW);
  //Serial.println("Forward");
}

void move_backward(){
  digitalWrite(STBY, HIGH);
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN2, HIGH);
  //Serial.println("Backwards");
}

void turn_left(){
  digitalWrite(STBY, HIGH);
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN2, LOW);
  //Serial.println("left");
}

void turn_right(){
  digitalWrite(STBY, HIGH);
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN2, LOW);
  //Serial.println("right");
}
void stop_motor(){
//enable standby
digitalWrite(STBY, LOW);
}
