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

const uint8_t BUKU[4][2]    = { { 7,0 }, { 7,1 }, { 7,2 }, { 7,3 } };
const uint8_t ADALAH[7][2]  = { { 8,0 }, { 8,1 }, { 8,2 }, { 8,3 }, { 8,4 }, { 8,5 }, { 8,6 } };
const uint8_t JENDELA[7][2] = { { 0,2 }, { 1,2 }, { 2,3 }, { 3,3 }, { 4,4 }, { 5,4 }, { 6,5 } };
const uint8_t DUNIA[5][2]   = { { 9,1 }, { 7,1 }, { 5,1 }, { 3,1 }, { 1,1 } };
const uint8_t MICLIB[7][2]  = { { 10,0 }, { 10,1 }, { 10,2 }, { 10,3 }, { 10,4 }, { 10,5 } };
const uint8_t ALUN[4][2]    = { { 6,5 }, { 4,5 }, { 2,5 }, { 0,5 } };
const uint8_t BANDUNG[7][2] = { { 6,1 }, { 5,1 }, { 4,2 }, { 3,2 }, { 2,3 }, { 1,3 } };
const uint8_t SHAU[4][2]    = { { 4,0 }, { 5,0 }, { 6,1 }, { 7,1 } };

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

// leds[10] = { "M", "I", "C", "L", "I", "B" }
// leds[9]  = { "O", "D", "I", "N", "E" }
// leds[8]  = { "A", "D", "A", "L", "A", "H" }
// leds[7]  = { "B", "U", "K", "U", "Q" }
// leds[6]  = { "C", "A", "L", "Y", "D", "A" }
// leds[5]  = { "H", "N", "E", "E", "L" }
// leds[4]  = { "S", "L", "D", "S", "E", "L" }
// leds[3]  = { "I", "I", "U", "D", "R" }
// leds[2]  = { "X", "U", "V", "N", "E", "U" }
// leds[1]  = { "M", "A", "E", "G", "Z"" }
// leds[0]  = { "I", "N", "J", "S", "U", "N" }

//sequence
// 1. BUKU
// leds[7][0-3]
// 2. ADALAH
// leds[8][0-6]
// 3. JENDELA
// leds[0][2], leds[1][2], leds[2][3], leds[3][3], leds[4][4], leds[5][4], leds[6][5]
// 4. DUNIA
// leds[9][1], leds[7][1], leds[5][1], leds[3][1], leds[1][1]
// 5. MICLIB
// leds[10][0-5]
// 6. ALUN
// leds[6][5], leds[4][5], leds[2][5], leds[0][5]
// 7. BANDUNG
// leds[7][0], leds[6][1], leds[5][1], leds[4][2], leds[3][2], leds[2][3], leds[1][3]
// 8. SHAU
// leds[4][0], leds[5][0], leds[6][1], leds[7][1]

// v0.2 crosswords with fadeout effect

void crosswords(int timeDelayBright, int timeDelayDark, int timeDelayPerWord){
    
    resetLed(timeDelayPerWord);
    uint8_t brightness = 0;
    uint8_t fadeAmount = 5;
    uint8_t fadeTime = 0;
    boolean notEnd = true;

    while(notEnd){
      for(uint8_t x=0; x<sizeof(BUKU); x++){ leds[BUKU[x][0]][BUKU[x][1]].setHSV(255, 0, brightness); }
      FastLED.show();
      brightness += fadeAmount;
      if(brightness == 0 || brightness == 255){ fadeAmount = -fadeAmount; }   
      delay(20);
      if(brightness == 0){ delay(timeDelayBright); fadeTime++; }
      if(brightness == 255){ delay(timeDelayDark); fadeTime++; }
      if(fadeTime == 2 ){ notEnd = false; }
    }

    resetLed(timeDelayPerWord); notEnd=true; brightness=0; fadeAmount=5; fadeTime=0;
}

void resetLed(int timedelay){
    for(uint8_t i=0;i<NUM_STRIPS;i++){
        for(uint8_t j=0;j<NUM_LEDS;j++){
            leds[i][j] = 0x000000;
        }
    }
    FastLED.show();
    delay(timedelay);
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

