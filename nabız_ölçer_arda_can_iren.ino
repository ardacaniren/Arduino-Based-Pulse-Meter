#define USE_ARDUINO_INTERRUPTS true // En doğru BPM sonucunu elde etmek adına ufak süreli kesmeler eklenmiştir.
#include <PulseSensorPlayground.h> // Kütüphaneler eklenmiştir.
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h> 
#define I2C_ADDR 0x27 // Denetleyici için LCD EKRAN I2C Adresi tanımlanmıştır.
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
#define BACKLIGHT 3

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
 
// Değişkenler
const int PulseWire = 0; // Nabız sensörünün pembe kablosu A0'a bağlanmıştır.
const int LED13 = 13; // Yerleşik Arduino LED'i, PIN 13'ü yakmak üzerine ayarlanmıştır.
int Threshold = 550; // Hangi Sinyalin "vuruş olarak sayılacağını" ve hangilerinin göz ardı edileceğini belirlenmiştir.

 PulseSensorPlayground pulseSensor; // PulseSensorPlayground nesnesinin "pulseSensor" adlı bir örneğini oluşturur.
void setup() {
 
Serial.begin(9600); // Serial monitör frekans değeri 9600 olarak belirlenmiştir.
lcd.begin(16,2);
lcd.setBacklightPin(BACKLIGHT,POSITIVE);
lcd.setBacklight(HIGH);
 
// Değişkenlerimizi atayarak PulseSensor nesnesini yapılandırılmıştır.
pulseSensor.analogInput(PulseWire);
pulseSensor.blinkOnPulse(LED13); //Arduino LED'ini kalp atışı ile otomatik olarak yanıp söner.
pulseSensor.setThreshold(Threshold);
 
// "pulseSensor" nesnesinin oluşturulduğunu ve bir sinyal görmeye "başladığını" iki kez kontrol edilmelidir.
if (pulseSensor.begin()) {
Serial.println("We created a pulseSensor Object !"); //Bu, Arduino açılışında veya Arduino sıfırlamasında bir kez yazdırılmıştır.
lcd.setCursor(0,0);
lcd.print("  Nabiz Olcer");// "LCD ekran açılınca ekranın üstüne Nabiz Olcer" yazdırır.
 
}
}
 
void loop() {
 
int (BPM) = pulseSensor.getBeatsPerMinute(); // Çağrılar, BPM'yi bir "int" olarak döndüren pulseSensor nesnemizde çalışmaktadır.

if (pulseSensor.sawStartOfBeat()) { //"Bir vuruş olup olmadığını" görmek için sürekli olarak test edilmektedir.
Serial.println("Nabiz "); // Ekrana nabız algılanınca "Nabiz" yazdır.
Serial.print("(BPM): "); // 
Serial.println((BPM)); // Print the value inside of myBPM.
lcd.setCursor(0,2);
lcd.print("Nabiz"); // Ekrana nabız algılanınca "Nabiz" yazdır.
lcd.setCursor(5,3);
lcd.print("(BPM): "); // 
lcd.print((BPM));
}
delay(20); // Gecikme süresi ayarlanmıştır.
}