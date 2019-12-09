#include <ESP8266WiFi.h>
#include <NewPingESP8266.h>

#define STBY 15
#define AIN1 3
#define AIN2 12
#define BIN1 0
#define BIN2 2
#define PWM 14
#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 20 // Maximum distance (in cm) to ping.

const char *ssid = "RTES-2019";
const char *pass = "rtes2019";
long rssi_array[21];
long prev_rssi = 0;
bool beaconReached = false;

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
  analogWrite(PWM, 400);
  wificonnect();
  //Serial.begin(9600);
}

void loop() { 
  if(!beaconReached)
  {
    update_rssi();
    if(prev_rssi<rssi){
      for (uint8_t i = 0; i < SONAR_NUM; i++)
      { // Loop through each sensor and display results.
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
  }
  if(rssi>-50)
  {
    stop_motor();
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

void wificonnect(){
  WiFi.begin(ssid,pass);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
  }
  for(int i=0; i<=25; i++)
  {
    rssi_array[i] = (WiFi.RSSI()*100);
    turn_right();
    delay(500);
  }
  max_rssi = getMaximum(rssi_array, 25);
  for(int j=0; j<25; j++)
  {
    if(rssi_array[j]<max_rssi)
    {
      turn_left();
      break;
    }
  }
}

void update_rssi(){
  prev_rssi =rssi();
  rssi = WiFi.RSSI();
}

int getMaximum(long array_name, int size_array){
 int maxIndex = 0;
 int max_value = array_name[maxIndex];
 for (int i=1; i<size_array; i++){
   if (max_value<array_name[i]){
     maxValue = array_name[i];
     maxIndex = i;
   }
 }
 return maxValue;
}

//void wifistrenght(){
//  for(int i=0;i<=21;i++){
//  rssi_array[i] = (WiFi.RSSI()*100);
//  }
//  int rssi, max_i=maximum();
//  Serial.print("RSSI:"); 
//  Serial.println(rssi); 
//  Serial.print("position_i:"); 
//  Serial.println(max_i);
//  adjust_bot();
//}

//int maximum(){
//  for ( int i = 0; i < sizeof(rssi_array)/sizeof(rssi_array[0]); i++ )
//  {
//    if ( rssi_array[i] > max_v )
//    {
//      max_v = rssi_array[i];
//      max_i = i;
//    }
//  }
//  return max_v,max_i;
//}
