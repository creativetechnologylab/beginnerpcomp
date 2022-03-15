#include <HCSR04.h>
UltraSonicDistanceSensor distanceSensor(13, 12); 

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 8

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


void setup() {
  Serial.begin(9600);

  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50);
  

}

void loop() {
 
  float distance = distanceSensor.measureDistanceCm() ;
  Serial.println(distance);
  
if (distance > 0){
  if (distance>=10 && distance < 30 ){
    strip.clear();
    int j = map(distance,10, 30, 0, strip.numPixels());
    Serial.println(j);
    for(long firstPixelHue = 0; firstPixelHue < 3072; firstPixelHue += 256) {
    for(int i=0; i<=j; i++) { // For each pixel in strip...
    int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));         //  Set pixel's color (in RAM)
     
     }
    strip.show(); 
    delay(10); 
  }
  
}else if (distance >= 30){
    for(long firstPixelHue = 0; firstPixelHue < 3072; firstPixelHue += 256) {
    for (int i=0; i<strip.numPixels(); i++){
    int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));         //  Set pixel's color (in RAM)         
    
      }
       strip.show();
       delay(1);
    }
    
}else {
    for (int i=0; i<strip.numPixels(); i++){
     strip.clear();
     strip.show();
    }
  }
}
}
