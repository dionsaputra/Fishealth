#include <FirebaseArduino.h>  // firebase library
#include <dht.h>              // temperature sensor library
#include <ESP8266WiFi.h>      // wifi module library

#define FIREBASE_HOST "tubesrobotika.firebaseio.com"
#define WIFI_SSID "KOST PAK NANA ATAS 2" 
#define WIFI_PASSWORD "evalia00" 
#define DHT11_PIN 2
#define TRIG_PIN 16 // D0
#define ECHO_PIN 5  // D1

dht DHT;

void setup() {
  Serial.begin(9600);

  // wifi module setup
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }

  // firebase setup
  Firebase.begin(FIREBASE_HOST);

  // ultrasonic setup
  pinMode(TRIG_PIN,OUTPUT); pinMode(ECHO_PIN,INPUT);
  
}

void loop() {

  // DHT sensor read temperature and humidity
  int i = DHT.read11(DHT11_PIN);

  // clear trigger pin then set to HIGH state for 10 ms
  digitalWrite(TRIG_PIN,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN,LOW);

  // calculate distance1
  int duration; int distance;
  duration = pulseIn(ECHO_PIN,HIGH);
  Serial.print("Duration: "); Serial.println(duration);
  distance = duration * 0.034 / 2;
  delay(1000);
  
  Serial.print("Distance: "); Serial.println(distance);
  
  String s1 = Firebase.pushFloat("Temp",DHT.temperature);
  if (Firebase.failed()) {
      Serial.print("pushing temperature failed:");
      Serial.println(Firebase.error());  
      return;
  }

  String s2 = Firebase.pushFloat("Humidity",DHT.humidity);
  if (Firebase.failed()) {
      Serial.print("pushing humidity failed:");
      Serial.println(Firebase.error());  
      return;
  }

  Firebase.setFloat("FoodVolume",distance);
  
}
