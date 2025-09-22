#include <Arduino.h>
#include <FastLED.h>
#include <MicroOscSlip.h>
MicroOscSlip<128> monOsc(&Serial);

#define MA_BROCHE_ANGLE 32
#define MA_BROCHE_BOUTON 39
CRGB monPixel;

void setup() {
  pinMode( MA_BROCHE_BOUTON , INPUT );

  Serial.begin(115200);

  FastLED.addLeds<WS2812, 27, GRB>(&monPixel, 1);
}

void loop() {
  // oscslip_pd
  int maLectureBouton = digitalRead( MA_BROCHE_BOUTON );
  monOsc.sendInt("/pot", maLectureBouton);

  // oscslip_angle
  int maLectureAnalogique = analogRead(MA_BROCHE_ANGLE);
  monOsc.sendInt("/but", maLectureAnalogique);
  delay(50);

  // couleur_pixel
  if (maLectureAnalogique >= 2047)
  {
    monPixel = CRGB(0, 0, 255);
    FastLED.show();
  } else if (maLectureAnalogique < 2047) {
    monPixel = CRGB(255, 255, 0);
    FastLED.show();
  }


}