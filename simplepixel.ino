#include <Gaussian.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN        6
#define NUMPIXELS 60

struct color{
  char r;
  char g;
  char b;
};

union colors{
  color C;
  char A[3]; 
};

Gaussian G = Gaussian(60, 5);

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 20

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin();
}

void loop() {
  pixels.clear();
  static int j=0;
  G.setVariance(NUMPIXELS);
  if(j<=NUMPIXELS*2){j++;}else{j=0;};
  if(j<=NUMPIXELS){
    G.setMean(j);
    G.setVariance(j);
  }else{
    G.setMean(-j+2*NUMPIXELS);
    G.setVariance(-j+2*NUMPIXELS);
  }
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255*G.plot(i),255*G.plot(i),255*G.plot(i)));
  }
  
  pixels.show();
  delay(DELAYVAL);
}
