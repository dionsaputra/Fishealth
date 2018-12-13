#include <FirebaseArduino.h>
#include <dht.h>
dht DHT;
#include  <ESP8266WiFi.h>

#define FIREBASE_HOST "tubesrobotika.firebaseio.com"
#define WIFI_SSID "KOST PAK NANA ATAS 2" // Change the name of your WIFI
#define WIFI_PASSWORD "evalia00" // Change the password of your WIFI

#define DHT11_PIN 2    // Data Pin of DHT 11 , for NodeMCU D5 GPIO no. is 14


void setup() {
  Serial.begin(9600);

   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST);
  
}

void loop() {
 
  
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(1000);
  String name = Firebase.pushInt("Temp",DHT.temperature);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
   String nama = Firebase.pushInt("Humidity",DHT.humidity);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
 
  delay(200);
}
