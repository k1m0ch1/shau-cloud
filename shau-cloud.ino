#include <FastLED.h>

#define LED_PIN     8
#define NUM_LEDS    20
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_STRIPS   3
#define UPDATES_PER_SECOND 100

CRGB leds[NUM_STRIPS][NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
const uint8_t PIN_NO[] = { 8, 9, 11 };

extern CRGBPalette16 langitsenja, langitbiru;
extern const TProgmemPalette16 langitsenja_p PROGMEM;
extern const TProgmemPalette16 langitbiru_p PROGMEM;

void setup() {
    delay( 3000 ); // power-up safety delay

//    FastLED.addLeds<LED_TYPE, 8, COLOR_ORDER>(leds[0], NUM_LEDS).setCorrection( TypicalLEDStrip );
//    FastLED.addLeds<LED_TYPE, 9, COLOR_ORDER>(leds[1], NUM_LEDS).setCorrection( TypicalLEDStrip );
//    FastLED.addLeds<LED_TYPE, 11, COLOR_ORDER>(leds[2], NUM_LEDS).setCorrection( TypicalLEDStrip );
//    FastLED.addLeds<LED_TYPE, 8, COLOR_ORDER>(leds[3], NUM_LEDS).setCorrection( TypicalLEDStrip );
//    FastLED.addLeds<LED_TYPE, 9, COLOR_ORDER>(leds[4], NUM_LEDS).setCorrection( TypicalLEDStrip );
//    FastLED.addLeds<LED_TYPE, 11, COLOR_ORDER>(leds[5], NUM_LEDS).setCorrection( TypicalLEDStrip );
//    FastLED.addLeds<LED_TYPE, 8, COLOR_ORDER>(leds[6], NUM_LEDS).setCorrection( TypicalLEDStrip );
//    FastLED.addLeds<LED_TYPE, 9, COLOR_ORDER>(leds[7], NUM_LEDS).setCorrection( TypicalLEDStrip );
//    FastLED.addLeds<LED_TYPE, 11, COLOR_ORDER>(leds[8], NUM_LEDS).setCorrection( TypicalLEDStrip );
//    FastLED.addLeds<LED_TYPE, 8, COLOR_ORDER>(leds[9], NUM_LEDS).setCorrection( TypicalLEDStrip );
//    FastLED.addLeds<LED_TYPE, 9, COLOR_ORDER>(leds[10], NUM_LEDS).setCorrection( TypicalLEDStrip );

    FastLED.setBrightness(BRIGHTNESS);    
}


void loop(){

    static uint8_t startIndex = 0;
    startIndex = startIndex + 1;

    awan(langitbiru_p, startIndex);
    
    FastLED.show();
    FastLED.delay(15000 / UPDATES_PER_SECOND);
}

void awan( CRGBPalette16 warna, uint8_t colorIndex ){
    currentPalette = langitbiru_p;           
    currentBlending = LINEARBLEND;
    
    uint8_t brightness = 255;
    
    for(uint8_t a=0;a<NUM_STRIPS;a++){
      for( uint8_t i = 0; i < NUM_LEDS; i++) {
          leds[a][i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
      }
      colorIndex += 3;
    }
}

const TProgmemRGBPalette16 langitsenja_p PROGMEM ={
    0xff751a, 0xff6600, 0xff6600, 0x87ceeb,    
    0xff751a, 0xff6600, 0xff6600, 0x87ceeb,  
    0xff751a, 0xff6600, 0xff6600, 0x87ceeb,    
    0xff751a, 0xff6600, 0xff6600, 0x87ceeb
};

const TProgmemRGBPalette16 langitbiru_p PROGMEM ={
    0x0000ff, 0x0000ff, 0xadd8e6, 0x87ceeb,    
    0x0000ff, 0x0000ff, 0xadd8e6, 0x87ceeb,    
    0x0000ff, 0x0000ff, 0xadd8e6, 0x87ceeb,    
    0x0000ff, 0x0000ff, 0xadd8e6, 0x87ceeb
};

