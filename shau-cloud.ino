#include <Hx711.h>
#include <FastLED.h>

Hx711 scale(A1, A0);

#define NUM_LEDS    114
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_STRIPS   11
#define UPDATES_PER_SECOND 100

CRGB leds[NUM_STRIPS][NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
const uint8_t timernya = 1;
unsigned long time;
uint8_t lapse = 0;


extern CRGBPalette16 langitsenja, langitbiru, warnadunia;
extern const TProgmemPalette16 langitsenja_p PROGMEM;
extern const TProgmemPalette16 langitbiru_p PROGMEM;
extern const TProgmemPalette16 warnadunia_p PROGMEM;

const uint8_t BUKU[4][2]    = { { 7,0 }, { 7,1 }, { 7,2 }, { 7,3 } };
const uint8_t ADALAH[7][2]  = { { 8,0 }, { 8,1 }, { 8,2 }, { 8,3 }, { 8,4 }, { 8,5 }, { 8,6 } };
const uint8_t JENDELA[7][2] = { { 0,2 }, { 1,2 }, { 2,3 }, { 3,3 }, { 4,4 }, { 5,4 }, { 6,5 } };
const uint8_t DUNIA[5][2]   = { { 9,1 }, { 7,1 }, { 5,1 }, { 3,1 }, { 1,1 } };
const uint8_t MICLIB[7][2]  = { { 10,0 }, { 10,1 }, { 10,2 }, { 10,3 }, { 10,4 }, { 10,5 } };
const uint8_t ALUN[4][2]    = { { 6,5 }, { 4,5 }, { 2,5 }, { 0,5 } };
const uint8_t BANDUNG[7][2] = { { 7,0 }, { 6,1 }, { 5,1 }, { 4, 2 }, { 3,2 }, { 2,3 }, { 1,3 } };
const uint8_t SHAU[4][2]    = { { 4,0 }, { 5,0 }, { 6,1 }, { 7,1 } };

int eeq = 0 ;

void setup() {
    delay( 3000 ); // power-up safety delay
  
    FastLED.addLeds<LED_TYPE, 2, COLOR_ORDER>(leds[10], NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, 3, COLOR_ORDER>(leds[9], NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, 4, COLOR_ORDER>(leds[8], NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, 5, COLOR_ORDER>(leds[7], NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, 6, COLOR_ORDER>(leds[6], NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, 7, COLOR_ORDER>(leds[5], NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, 8, COLOR_ORDER>(leds[4], NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, 9, COLOR_ORDER>(leds[3], NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, 10, COLOR_ORDER>(leds[2], NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, 11, COLOR_ORDER>(leds[1], NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, 12, COLOR_ORDER>(leds[0], NUM_LEDS).setCorrection( TypicalLEDStrip );

    FastLED.setBrightness(BRIGHTNESS);    
    Serial.begin(9600);
}


void loop(){

   
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1;

    time = millis();

    lapse = time%10000?lapse+1:lapse;

    if(time<13000){
       awan(langitbiru_p, startIndex);
    }else{
      awan(warnadunia_p, startIndex);
     // crosswords(500,500,100);
    }

    if(eeq==60){
      Serial.print(scale.getGram(), 1);
      Serial.println(" g");
      if(scale.getGram()>100  || scale.getGram()<-100 ){
        crosswords(500,500,100);
      }
      eeq=0;
    }

    FastLED.show();
    FastLED.delay(500 / UPDATES_PER_SECOND);
    eeq++;
}

void awan( CRGBPalette16 warna, uint8_t colorIndex ){
    currentBlending = LINEARBLEND;
    
    uint8_t brightness = 255;
    
    for(uint8_t a=0;a<NUM_STRIPS;a++){
      for( uint8_t i = 0; i < NUM_LEDS; i++) {
          leds[a][i] = ColorFromPalette( warna, colorIndex, brightness, currentBlending);
      }
      colorIndex += 3;
    }
}

void crosswords(int timeDelayBright, int timeDelayDark, int timeDelayPerWord){
    
    resetLed(timeDelayPerWord);
    uint8_t brightness = 255;
    uint8_t fadeAmount = 5;
    uint8_t fadeTime = 0;
    boolean notEnd = true;

    while(notEnd){
      for(uint8_t x=0; x<4; x++){ 
        for(uint8_t y=0; y<=76;y++){
           leds[BUKU[x][0]][y] = CRGB::DarkRed; 
           leds[BUKU[x][0]][y].fadeLightBy(brightness);
        }
       }
       
      FastLED.show();
      brightness = brightness -  fadeAmount;
      if(brightness == 0 || brightness == 255){ fadeAmount = -fadeAmount; }   
      delay(20);
      if(brightness == 255){ delay(timeDelayBright); fadeTime++; }
      if(brightness == 0){ delay(timeDelayDark); fadeTime++; }
      if(fadeTime == 2 ){ notEnd = false; }
    }

    resetLed(timeDelayPerWord); brightness = 255; fadeAmount = 5; fadeTime = 0; notEnd = true;

    while(notEnd){
      for(uint8_t x=0; x<7; x++){ 
        for(uint8_t y=0; y<=114;y++){
           leds[ADALAH[x][0]][y] = CRGB::DarkRed; 
           leds[ADALAH[x][0]][y].fadeLightBy(brightness);
        }
       }
       
      FastLED.show();
      brightness = brightness -  fadeAmount;
      if(brightness == 0 || brightness == 255){ fadeAmount = -fadeAmount; }   
      delay(20);
      if(brightness == 255){ delay(timeDelayBright); fadeTime++; }
      if(brightness == 0){ delay(timeDelayDark); fadeTime++; }
      if(fadeTime == 2 ){ notEnd = false; }
    }

    resetLed(timeDelayPerWord); brightness = 255; fadeAmount = 5; fadeTime = 0; notEnd = true;

    while(notEnd){
      for(uint8_t x=0; x<7; x++){ 
        for(uint8_t y=(JENDELA[x][1]*19);y<((JENDELA[x][1]*19)+19); y++){
           leds[JENDELA[x][0]][y] = CRGB::DarkRed; 
           leds[JENDELA[x][0]][y].fadeLightBy(brightness);
        }
       }
       
      FastLED.show();
      brightness = brightness -  fadeAmount;
      if(brightness == 0 || brightness == 255){ fadeAmount = -fadeAmount; }   
      delay(20);
      if(brightness == 255){ delay(timeDelayBright); fadeTime++; }
      if(brightness == 0){ delay(timeDelayDark); fadeTime++; }
      if(fadeTime == 2 ){ notEnd = false; }
    }

    resetLed(timeDelayPerWord); brightness = 255; fadeAmount = 5; fadeTime = 0; notEnd = true;

    while(notEnd){
      for(uint8_t x=0; x<5; x++){ 
        for(uint8_t y=(DUNIA[x][1]*19);y<((DUNIA[x][1]*19)+19); y++){
           leds[DUNIA[x][0]][y] = CRGB::DarkRed; 
           leds[DUNIA[x][0]][y].fadeLightBy(brightness);
        }
       }
       
      FastLED.show();
      brightness = brightness -  fadeAmount;
      if(brightness == 0 || brightness == 255){ fadeAmount = -fadeAmount; }   
      delay(20);
      if(brightness == 255){ delay(timeDelayBright); fadeTime++; }
      if(brightness == 0){ delay(timeDelayDark); fadeTime++; }
      if(fadeTime == 2 ){ notEnd = false; }
    }

    resetLed(timeDelayPerWord); brightness = 255; fadeAmount = 5; fadeTime = 0; notEnd = true;

    while(notEnd){
      for(uint8_t x=0; x<6; x++){ 
        for(uint8_t y=(MICLIB[x][1]*19);y<((MICLIB[x][1]*19)+19); y++){
           leds[MICLIB[x][0]][y] = CRGB::DarkRed; 
           leds[MICLIB[x][0]][y].fadeLightBy(brightness);
        }
       }
       
      FastLED.show();
      brightness = brightness -  fadeAmount;
      if(brightness == 0 || brightness == 255){ fadeAmount = -fadeAmount; }   
      delay(20);
      if(brightness == 255){ delay(timeDelayBright); fadeTime++; }
      if(brightness == 0){ delay(timeDelayDark); fadeTime++; }
      if(fadeTime == 2 ){ notEnd = false; }
    }

    resetLed(timeDelayPerWord); brightness = 255; fadeAmount = 5; fadeTime = 0; notEnd = true;

    while(notEnd){
      for(uint8_t x=0; x<4; x++){ 
        for(uint8_t y=(ALUN[x][1]*19);y<((ALUN[x][1]*19)+19); y++){
           leds[ALUN[x][0]][y] = CRGB::DarkRed; 
           leds[ALUN[x][0]][y].fadeLightBy(brightness);
        }
       }
       
      FastLED.show();
      brightness = brightness -  fadeAmount;
      if(brightness == 0 || brightness == 255){ fadeAmount = -fadeAmount; }   
      delay(20);
      if(brightness == 255){ delay(timeDelayBright); fadeTime++; }
      if(brightness == 0){ delay(timeDelayDark); fadeTime++; }
      if(fadeTime == 2 ){ notEnd = false; }
    }

    resetLed(timeDelayPerWord); brightness = 255; fadeAmount = 5; fadeTime = 0; notEnd = true;

    while(notEnd){
      for(uint8_t x=0; x<4; x++){ 
        for(uint8_t y=(ALUN[x][1]*19);y<((ALUN[x][1]*19)+19); y++){
           leds[ALUN[x][0]][y] = CRGB::DarkRed; 
           leds[ALUN[x][0]][y].fadeLightBy(brightness);
        }
       }
       
      FastLED.show();
      brightness = brightness -  fadeAmount;
      if(brightness == 0 || brightness == 255){ fadeAmount = -fadeAmount; }   
      delay(20);
      if(brightness == 255){ delay(timeDelayBright); fadeTime++; }
      if(brightness == 0){ delay(timeDelayDark); fadeTime++; }
      if(fadeTime == 2 ){ notEnd = false; }
    }

    resetLed(timeDelayPerWord); brightness = 255; fadeAmount = 5; fadeTime = 0; notEnd = true;

    while(notEnd){
      for(uint8_t x=0; x<7; x++){ 
        for(uint8_t y=(BANDUNG[x][1]*19);y<((BANDUNG[x][1]*19)+19); y++){
           leds[BANDUNG[x][0]][y] = CRGB::DarkRed; 
           leds[BANDUNG[x][0]][y].fadeLightBy(brightness);
        }
       }
       
      FastLED.show();
      brightness = brightness -  fadeAmount;
      if(brightness == 0 || brightness == 255){ fadeAmount = -fadeAmount; }   
      delay(20);
      if(brightness == 255){ delay(timeDelayBright); fadeTime++; }
      if(brightness == 0){ delay(timeDelayDark); fadeTime++; }
      if(fadeTime == 2 ){ notEnd = false; }
    }

    resetLed(timeDelayPerWord); brightness = 255; fadeAmount = 5; fadeTime = 0; notEnd = true;

    while(notEnd){
      for(uint8_t x=0; x<4; x++){ 
        for(uint8_t y=(SHAU[x][1]*19);y<((SHAU[x][1]*19)+19); y++){
           leds[SHAU[x][0]][y] = CRGB::DarkRed; 
           leds[SHAU[x][0]][y].fadeLightBy(brightness);
        }
       }
       
      FastLED.show();
      brightness = brightness -  fadeAmount;
      if(brightness == 0 || brightness == 255){ fadeAmount = -fadeAmount; }   
      delay(20);
      if(brightness == 255){ delay(timeDelayBright); fadeTime++; }
      if(brightness == 0){ delay(timeDelayDark); fadeTime++; }
      if(fadeTime == 2 ){ notEnd = false; }
    }
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

const TProgmemRGBPalette16 warnadunia_p PROGMEM ={
    0x0000ff, 0x0000ff, 0x00c6ff, 0x00c6ff,    
    0xff00a2, 0xff00a2, 0x00c6ff, 0x0000ff,    
    0x00c6ff, 0x0000ff, 0xff00a2, 0x00c6ff,    
    0x0000ff, 0x0000ff, 0xadd8e6, 0xff00a2
};
