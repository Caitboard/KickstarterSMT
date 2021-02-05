#include <Adafruit_GFX.h>       // include Adafruit graphics library
#include <Adafruit_ILI9341.h>   // include Adafruit ILI9341 TFT library
#include "timer.h"
#include <FastLED.h> //library voor LEDstrip

#define LED_PIN     1 // LEDstrip pin is connected to NodeMCU pin D1
#define NUM_LEDS    20 // max number of LEDs used
#define TFT_CS    D2     // TFT CS  pin is connected to NodeMCU pin D2
#define TFT_RST   D3     // TFT RST pin is connected to NodeMCU pin D3
#define TFT_DC    D4     // TFT DC  pin is connected to NodeMCU pin D4
 
// initialize ILI9341 TFT library with hardware SPI module
// SCK (CLK) ---> NodeMCU pin D5 (GPIO14)
// MOSI(DIN) ---> NodeMCU pin D7 (GPIO13)

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

//button variables
const int buttonPin = 16;
int buttontrigger2;                 
int buttonState = 0;                
int buttonTrigger=0;
int buttonTriggerHigh=0;

int FSR = A0; // FSR Sensor
int glassesPerDay = 0; // Variable for amount of glasses water in a day
int glassesPerDayOld = 0; // Variable for refreshing the screen
int counter = 0; // Variable for the function to count glasses. Can only be 0 or 1
CRGB leds[NUM_LEDS];
//display variables
int count=0;                        //display counter
int ledIndication=0;                

//variables for calculating the percentages
float puntenLopen=0;
float puntenWater=0;
float puntenTotaal = 0;
float puntenGroep = 0;
float puntenTotaalLed = 0;
float puntenGroepOld = 0;
int minutes = 29;
int seconds = 59;

//Timers
Timer delayTime(2000);              // 2 sec
Timer longHighTime(500);            // 0.5 sec
Timer timer(710);
Timer looptime(1800000);            //30min

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.println("Start ILI9341"); 
  tft.begin();
  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 
  Serial.println(F("Benchmark                Time (microseconds)"));
  Serial.print(F("Screen fill              "));
  Serial.println(testFillScreen());                                  //intro screen SMART MOUSEPAD - only happens once
  
  pinMode(buttonPin, INPUT_PULLDOWN_16);              //button

  //start de timers
  delayTime.start();
  longHighTime.start();
  timer.start();
  looptime.start(); 
}

void loop() {
  int FSRValue = analogRead(FSR); // analog value from the force sensor
  puntenTotaal = (puntenWater*0.5) + (puntenLopen*0.5); //calculates the total percentage of 1 person
  puntenGroep = (puntenTotaal*0.25) + (0); // calculates the total percentage of the group, multiple people need to be added to function
  puntenTotaalLed = ceil((puntenGroep*10) + 10); // calculates how many LEDs need to be turned on
  
  buttonState = digitalRead(buttonPin); //reading the button value
  if (buttonState == HIGH) {
    if (longHighTime.done()) {                  //Detects a long button press
      Serial.println("HIGH-long");
      buttonTrigger=0;
      buttonTriggerHigh=1;
    }else {                                    //Detects a short button press
      Serial.println("HIGH-short");
      buttonTrigger=1;
    }
  } else {
    if(buttonTrigger==1){                      //Decides which counter to raise to switch between screens
      count++;
      buttonTrigger=0;
    }
    if(buttonTriggerHigh==1&&count>7){
      ledIndication++;
      count=8;
      if (ledIndication>1){
        ledIndication=0;
      }
      buttonTriggerHigh=0;
    }
    if(buttonTriggerHigh==1&&count<4){
      buttontrigger2++;
      count=2;
      buttonTriggerHigh=0;
    }
    longHighTime.restart();
  }
  Serial.println(count);
  //Serial.println(count);
  if (count==0){                          //screen 1
      buttontrigger2=0;
      seconds=59;
      minutes=29;
      tft.fillScreen(ILI9341_BLACK);
      tft.setRotation(3);
      PersentageBar(ILI9341_YELLOW, puntenLopen, 40, "Lopen");
      PersentageBar(ILI9341_CYAN, puntenWater, 100, "Water");
      PersentageBar(ILI9341_RED, puntenTotaal, 160, "Totale score");
//      testText("De tijd",20,225, ILI9341_WHITE,2);
      testText("Caitlin",170,225, ILI9341_WHITE,2);
      testText("Eigen score",20,0, ILI9341_WHITE,3);
      testText("1/1",300,0, ILI9341_WHITE,1);
      count =1;
    
  }
  /*TO DO
  If timerX is done{
    Update data(puntenLopen, puntenWater).  //update api 
  }
  
  if data(lopen/water ischanged)is updated{
  count=0;
  }
  */
  if (count==2){                      //screen 2
    if (buttontrigger2==0){
      tft.fillScreen(ILI9341_BLACK);
      testText("1/1",300,0, ILI9341_WHITE,1);
      PersentageBar(ILI9341_YELLOW, puntenLopen, 40, "Lopen"); 
      testText("30:00",20,95, ILI9341_WHITE,4);
      tft.setRotation(3);
      testText("Lopen",20,0, ILI9341_WHITE,3);
      testText("Houd ingedrukt om te beginnen",20,180, ILI9341_WHITE,1);
      count=3;      
    }
    if (minutes==0&&seconds==0){
          minutes=0;
          seconds=0;
          tft.fillScreen(ILI9341_BLACK);
          buttontrigger2=2;
    }
    if (buttontrigger2==1&&timer.done()){
      blackLines2();
      if (minutes>=0){
        seconds--;
        puntenLopen=puntenLopen+0.000833;
        PersentageBar(ILI9341_YELLOW, puntenLopen, 40, "Lopen");
        if (minutes==0&&seconds==0){
          minutes=0;
          seconds=0;
          tft.fillScreen(ILI9341_BLACK);
          buttontrigger2=2;
          }
        if (seconds==0){
        minutes--;
        seconds=59;
        }        
      }
      if (minutes<1&&seconds<1){
        minutes=0;
        seconds=0;
      }
      testText2((minutes),20,95, ILI9341_WHITE,4);
      testText(":",70,95, ILI9341_WHITE,4);
      testText2((seconds),95,95, ILI9341_WHITE,4);
      testText("Dubbel klik om te stoppen",20,180, ILI9341_WHITE,1);
      timer.restart();
    }
    if (buttontrigger2==2){
      tft.fillScreen(ILI9341_BLACK);
      testText("1/1",300,0, ILI9341_WHITE,1);
      testText("+100 Punten",180,90, ILI9341_WHITE,2);      //je heb xx punten verdien met 30 min lopen.
      testText("Lopen",20,0, ILI9341_WHITE,3);
      //puntenLopen=puntenLopen+0.5;
      PersentageBar(ILI9341_YELLOW, puntenLopen, 40, "Lopen"); 
      count=3;
    }
    if (buttontrigger2>2){
      buttontrigger2=0;
    }
  }
  if (count==4){                    //screen 3
      tft.fillScreen(ILI9341_BLACK);
      testText("1/1",300,0, ILI9341_WHITE,1);
      PersentageBar(ILI9341_RED, puntenGroep, 160, "Totale score groepnaam");
      testText("Groep 1",20,0, ILI9341_WHITE,3); 
      testText("John     Teus",20,60, ILI9341_RED,2); 
      testText("Caitlin  Robert",20,80, ILI9341_RED,2); 
      count=5;
  }
  if (count==6){                    //screen 4
      tft.fillScreen(ILI9341_BLACK);
      testText("1/1",300,0, ILI9341_WHITE,1);
      PersentageBar(ILI9341_RED, puntenGroep, 24, "Totale score groep 1");
      PersentageBar(ILI9341_BLUE, 0.8, 68, "Totale score groep 2");
      PersentageBar(ILI9341_GREEN, 0.25, 112, "Totale score groep 3");
      PersentageBar(ILI9341_MAGENTA, 0.9, 156, "Totale score groep 4");
      PersentageBar(ILI9341_CYAN, 0.9, 200, "Totale score groep 5");
      testText("Score bord",20,0, ILI9341_WHITE,3); 
      count=7;
  }
  
  if (count==8){                  //screen 5
      if (ledIndication==0){                        //optie 1
        testFastLines(ILI9341_RED, ILI9341_CYAN); 
        blackLines();
        testText("1/2",300,0, ILI9341_WHITE,1);
        testText("Led indicator ",20,0, ILI9341_WHITE,3);
        testText("<--      --> ",20,110, ILI9341_BLACK,4);
        tft.setRotation(4);//2
        testText("     Water ",0,170, ILI9341_BLACK,3);
        tft.setRotation(2);//4
        testText("Groep score ",2,170, ILI9341_BLACK,3);
        tft.setRotation(3);//1
      }
      if (ledIndication==1){                      //optie 2
        testFastLines(ILI9341_RED, ILI9341_YELLOW);
        blackLines();
        testText("2/2",300,0, ILI9341_WHITE,1);
        testText("Led indicator ",20,0, ILI9341_WHITE,3);
        testText("<--      --> ",20,110, ILI9341_BLACK,4);
        tft.setRotation(4);//2
        testText("     Lopen ",0,170, ILI9341_BLACK,3);
        tft.setRotation(2);//4
        testText("Groep score ",2,170, ILI9341_BLACK,3);
        tft.setRotation(3);//1
      }
      count=9;
  }
  if (count>9){                                 //loops screen counter
    count=0;
  }

//  Measuring an empty glass:
  Serial.println(FSRValue);
  if(FSRValue >300 && FSRValue < 580 && counter ==1) { 
    glassesPerDay++;
    counter = 0;
  }
//  Measuring a non-empty glass:
  else if (FSRValue > 580) {
    counter = 1;
  }
  
// LED INDICATORS

// 20 red LEDs
  if(glassesPerDay == 0){
      for (int i = 0; i <= 19; i++) {
      leds[i] = CRGB ( 255, 0, 0);
      FastLED.show();
      //delay(40);
    }
  }
  //  1 glass is 25%, so 2 green and one half green LEDs
  if(glassesPerDay == 1){
      for (int i = 0; i <= 1; i++) {
        leds[i] = CRGB ( 0, 255, 0);
        FastLED.show();
        //delay(40);
      }
      leds[2] = CRGB(102,255,102);
      FastLED.show();
      //delay(40);
      puntenWater = 0.25;
  }
  // 5 green LEDS
  if(glassesPerDay == 2){
        for (int i = 0; i <= 4; i++) {
        leds[i] = CRGB ( 0, 255, 0);
        FastLED.show();
        //delay(40);
        puntenWater = 0.5;
    }
  }
  // 7 and a half green LEDs
  if(glassesPerDay == 3){
      for (int i = 0; i <= 6; i++) {
        leds[i] = CRGB ( 0, 255, 0);
        FastLED.show();
        //delay(40);
        }
      leds[7] = CRGB(102,255,102);
      FastLED.show();
      //delay(40);
      puntenWater = 0.75;
  }
  // 10 green LEDs
  if(glassesPerDay == 4){
      for (int i = 0; i <= 9; i++) {
        leds[i] = CRGB ( 0, 255, 0);
        FastLED.show();
        //delay(40);
        puntenWater = 1;
    }
  }

// LEDs on the right side of the mousepad
// Is based on the total percentage of the group. 10% is 1 LED, 20% is 2 LEDs, and so on.
  if(puntenTotaalLed == 11) {
    leds[10] = CRGB(102,102,255);
    FastLED.show();
    delay(40);
  }
    if(puntenTotaalLed == 12) {
       for (int i = 10; i <= 11; i++) {
        leds[i] = CRGB (102,102,255);
        FastLED.show();
        //delay(40);
       }
  }
    if(puntenTotaalLed == 13) {
      for (int i = 10; i <= 12; i++) {
        leds[i] = CRGB (102,102,255);
        FastLED.show();
        //delay(40);
      }
  }
    if(puntenTotaalLed == 14) {
      for (int i = 10; i <= 13; i++) {
        leds[i] = CRGB (102,102,255);
        FastLED.show();
        //delay(40);
      }
  }
    if(puntenTotaalLed == 15) {
      for (int i = 10; i <= 14; i++) {
        leds[i] = CRGB (102,102,255);
        FastLED.show();
        //delay(40);
      }
  }
      if(puntenTotaalLed == 16) {
      for (int i = 10; i <= 15; i++) {
        leds[i] = CRGB (102,102,255);
        FastLED.show();
        //delay(40);
      }
  }
      if(puntenTotaalLed == 17) {
      for (int i = 10; i <= 16; i++) {
        leds[i] = CRGB (102,102,255);
        FastLED.show();
        //delay(40);
      }
  }
      if(puntenTotaalLed == 18) {
      for (int i = 10; i <= 17; i++) {
        leds[i] = CRGB (102,102,255);
        FastLED.show();
        //delay(40);
      }
  }
      if(puntenTotaalLed == 19) {
      for (int i = 10; i <= 18; i++) {
        leds[i] = CRGB (102,102,255);
        FastLED.show();
        //delay(40);
      }
  }
      if(puntenTotaalLed == 20) {
      for (int i = 10; i <= 19; i++) {
        leds[i] = CRGB (102,102,255);
        FastLED.show();
        //delay(40);
      }
  }
    if (glassesPerDay!=glassesPerDayOld){ //Resets the screen to update percentage bar immediately
    count--;
    glassesPerDayOld=glassesPerDay;
  }

}

unsigned long testText(char Str1[], int positiex, int positiey, uint16_t color1, int TextSize ) {   // function for adding text to TFT screen
  //tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setCursor(positiex, positiey);    //SHIFT,REGEL
  tft.setTextColor(color1);  tft.setTextSize(1);
  tft.setTextSize(TextSize);
  tft.println(Str1);
  return micros() - start;
}
unsigned long testText2(int chard, int positiex, int positiey, uint16_t color1, int TextSize ) { // function for adding numbers to TFT screen
  //tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setCursor(positiex, positiey);    //SHIFT,REGEL
  tft.setTextColor(color1);  tft.setTextSize(1);
  tft.setTextSize(TextSize);
  tft.println(chard);
  return micros() - start;
}

unsigned long testFillScreen() {              //Start screen, only visible once
  unsigned long start = micros();
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(3);
  testText("SMART",100,50, ILI9341_WHITE,4);
  testText("MOUSEPAD",80,100, ILI9341_RED,4);
  delay(1000);
  return micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2) {  //in vullen van 2 gekleurde gedeeltes zoals scherm 5 opties 1 en 2
  unsigned long start;
  int           x, y, w = tft.width(), h = tft.height();
  
  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  
  for(x=0 ; x<160; x+=1) tft.drawFastVLine(x, 0, h, color2);
  for(x=160 ; x<320; x+=1) tft.drawFastVLine(x, 0, 320, color1);
  return micros() - start;
}
unsigned long blackLines() { //voor hat zwart maken van kleine gedeelte
  unsigned long start;
  int           x, y, w = tft.width(), h = tft.height();
  start = micros();
  for(y=0; y<30; y+=1) tft.drawFastHLine(0, y, w, ILI9341_BLACK);
  return micros() - start;
}
unsigned long blackLines2() { //voor hat zwart maken van kleine gedeelte
  unsigned long start;
  int           x, y, w = tft.width(), h = tft.height();
  start = micros();
  for(y=40; y<280; y+=1) tft.drawFastHLine(0, y, w, ILI9341_BLACK);
  return micros() - start;
}
unsigned long PersentageBar(uint16_t color1, float procentige, int positionh, char Str1[] ) { //voor de percentage balken met variable input.
  unsigned long start;
  int           x, y;
  float q =procentige*280;
  int w = procentige*100;

  start = micros();
  for(y=(positionh+2); y<(positionh+20); y+=1) tft.drawFastHLine(20, y, q, color1);
  for(y=positionh; y<(positionh+2); y+=1) tft.drawFastHLine(20, y, 280,ILI9341_WHITE);
  for(y=(positionh+20); y<(positionh+22); y+=1) tft.drawFastHLine(20, y, 280,ILI9341_WHITE);
  for(x=20; x<22; x+=1) tft.drawFastVLine(x, positionh, 22, ILI9341_WHITE);
  for(x=298; x<300; x+=1) tft.drawFastVLine(x, positionh, 22, ILI9341_WHITE);
  tft.setCursor(140, (positionh+4)); tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println(w);
  if (procentige==1){
    tft.setCursor(180, (positionh+4));
    tft.println("%");
  }
  else{
    tft.setCursor(170, (positionh+4));
    tft.println("%");
  }
  tft.setCursor(20, (positionh+26)); tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println(Str1);

  return micros() - start;
}
