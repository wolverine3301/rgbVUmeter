// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            8

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      8

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second
int level=0;
int h=0;
int colors[] = {0,0,0};
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
//#if defined (__AVR_ATtiny85__)
//  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
//#endif
  // End of trinket special code
Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.
  for (uint16_t i=0; i < pixels.numPixels(); i++) {
        pixels.setPixelColor(i, 0);        //turn every third pixel off
        delay(1);
      }
}

void loop() {
  level=0;
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  //for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
   // pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.

      unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
  
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin; 
   colors[0]=100;
    if(peakToPeak > 350){
      level =8;
      
    }
    if(peakToPeak > 300 && peakToPeak < 350){
      level =7;
      colors[0]=0;
      colors[1]=0;
      colors[2]=0;
      if(h==3){ h=0;colors[h]=100;}
      else{
        colors[h]=100;
        h++;
      }
    }
    if(peakToPeak > 250 && peakToPeak < 300) level =6;
    if(peakToPeak > 200 && peakToPeak < 250) level =5;
    if(peakToPeak > 150 && peakToPeak < 200) level =4;
    if(peakToPeak > 100 && peakToPeak < 150) level =3;
    if(peakToPeak > 50 && peakToPeak < 100) level =2;
    if(peakToPeak < 50) level =1;
   //Serial.println(level);
   //Serial.println(peakToPeak);
   levels(level);
}
void levels(int level){
for(uint16_t i=0; i<level; i++) {
    pixels.setPixelColor(i,pixels.Color(colors[0],colors[1],colors[2]));
    pixels.show();
    delay(1);
  }
    for (uint16_t i=0; i < pixels.numPixels(); i++) {
        pixels.setPixelColor(i, 0);        //turn every third pixel off
        delay(1);
      }

  
}
