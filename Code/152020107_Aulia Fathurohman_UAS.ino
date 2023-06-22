#include "DHT.h"
#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#define DHTTYPE DHT11
#define dht_pint D5
#include <LiquidCrystal_I2C.h>
#define BACKLIGHT_PIN
#define pinLED D7
#define pinButton D8
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
char auth[]="3yoiOwwrXKTVliU0GswP5PEB237q8cnG";
char ssid[]="Galaxy";
char pass[]="residentevil12";
DHT dht(dht_pint, DHTTYPE);
const int sensor = A0;
const int buzz = D6 ;
int temp = 0; 
 int d = 50 ;
int h = dht.readHumidity();
 int t = dht.readTemperature();
 int b = analogRead(sensor);
 int bpm = (b/10)-4;

byte love[8] = { //karakter love
  0b00000,
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
  
};
byte drjt[8] = {
  0b00100,
  0b01010,
  0b10001,
  0b01010,
  0b00100,
  0b00000,
  0b00000,
  0b00000
};
void setup() {
 
 Serial.begin(9600);
 lcd.begin(16,2);
 lcd.backlight();
 lcd.createChar(0, love);
lcd.createChar(1, drjt);
lcd.setCursor(0,0); 
lcd.write("Selamat datang");
delay(1000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Tempelkan");
lcd.setCursor(0,1);
lcd.write("2 jari anda");

  delay(6000);

 pinMode(A0,INPUT);
 pinMode(D6,OUTPUT);
 pinMode(pinButton, INPUT);
 pinMode(pinLED, OUTPUT);
 dht.begin();
 Blynk.begin(auth,ssid,pass);
 
 lcd.clear();
}


void loop() {
    Blynk.run();
int pinLED = D7;
pinLED = 0 ;

int pinButton = D8;
 if (digitalRead(pinButton)==0) {
    do
    { }
    while (digitalRead(pinButton)==0);
    
                  digitalWrite(D7 , ! digitalRead (D7)); 
                  
 }
   

 
 if (pinLED == LOW) {
  
int h = dht.readHumidity();
 int t = dht.readTemperature();
 int b = analogRead(sensor);
 int bpm;
 bpm = 0;
 bpm = (b/10)-4;

 
  lcd.clear();
lcd.setCursor(0,0); 
 lcd.write((byte)0);
lcd.setCursor(1,0);
lcd.write("BPM");
lcd.setCursor(0,1);
lcd.print(bpm);
lcd.print("% sp02");
lcd.setCursor(6,0);
lcd.write("temp:");
lcd.setCursor(12,0);
lcd.print(t);
lcd.setCursor(14,0);
 lcd.write((byte)1);
lcd.setCursor(15,0);
lcd.write("C");
  Gaugebpm();
  Gaugetmp();
  Gaugehmd();
  lcdtmp();
  lcdbpm();
  lcdhmd();

  if (((bpm > 90 ) and (t < 38))) {
    Blynk.notify("Ada Pengunjung");
    digitalWrite(buzz,HIGH);
    
    lcd.clear();
 lcd.setCursor(0,0);
lcd.print("Anda di izinkan");
lcd.setCursor(0,1);
lcd.write("untuk masuk");
delay(2000);
  }
  else{
    digitalWrite(buzz,LOW);  // turn off
  }
  }
 
 else if (pinLED == HIGH){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Selamat Jalan");
  lcd.setCursor(0,1);
  lcd.write(byte(0));
   for(int u=0; u <16 ; u++) {
  lcd.scrollDisplayRight();
    delay(500);
 }
}
}

/*void lcdGG() {
int bpm = (b/10)-4;
 int b = analogRead(sensor);
 int h = dht.readHumidity();
 int t = dht.readTemperature();
   
  delay(100);
}*/

void Gaugebpm() {
  int b = analogRead(sensor);
int bpm = (b/10)-4;

 Blynk.virtualWrite(V1, bpm);
 delay(d);
}

void Gaugetmp() {
  int t = dht.readTemperature();
  Blynk.virtualWrite(V0, t); 
  delay(d);
}

void Gaugehmd() {
 int h = dht.readHumidity();
 Blynk.virtualWrite(V2, h);
 delay(d);
}
void lcdtmp() {
  int t = dht.readTemperature();
 Blynk.virtualWrite(V3, t);
 delay(d);
}

void lcdbpm() {
  int b = analogRead(sensor);
 int bpm = (b/10)-4;

 Blynk.virtualWrite(V4, bpm);
 delay(d);
}

void lcdhmd() {
 int h = dht.readHumidity();  
 Blynk.virtualWrite(V5, h);
 delay(d);
}
