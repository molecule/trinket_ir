// Convenient 2D point structure
struct Point {
  float x;
  float y;
};


float phase = 0.0;
float phaseIncrement = 0.03;  // Controls the speed of the moving points. Higher == faster. I like 0.08 .
float colorStretch = 0.11;    // Higher numbers will produce tighter color bands. I like 0.11 .

// This function is called every frame.
void plasma() {
  phase += phaseIncrement;
  
  // The two points move along Lissajious curves, see: http://en.wikipedia.org/wiki/Lissajous_curve
  // We want values that fit the LED grid: x values between 0..13, y values between 0..8 .
  // The sin() function returns values in the range of -1.0..1.0, so scale these to our desired ranges.
  // The phase value is multiplied by various constants; I chose these semi-randomly, to produce a nice motion.
  Point p1 = { (sin(phase*1.000)+1.0) * 4.5, (sin(phase*1.310)+1.0) * 4.0 };
  Point p2 = { (sin(phase*1.770)+1.0) * 4.5, (sin(phase*2.865)+1.0) * 4.0 };
  Point p3 = { (sin(phase*0.250)+1.0) * 4.5, (sin(phase*0.750)+1.0) * 4.0 };
  
  byte row, col;
  
  // For each row...
  for( row=0; row<5; row++ ) {
    float row_f = float(row);  // Optimization: Keep a floating point value of the row number, instead of recasting it repeatedly.
    
    // For each column...
    for( col=0; col<8; col++ ) {
      float col_f = float(col);  // Optimization.
      
      // Calculate the distance between this LED, and p1.
      Point dist1 = { col_f - p1.x, row_f - p1.y };  // The vector from p1 to this LED.
      float distance1 = sqrt( dist1.x*dist1.x + dist1.y*dist1.y );
      
      // Calculate the distance between this LED, and p2.
      Point dist2 = { col_f - p2.x, row_f - p2.y };  // The vector from p2 to this LED.
      float distance2 = sqrt( dist2.x*dist2.x + dist2.y*dist2.y );
      
      // Calculate the distance between this LED, and p3.
      Point dist3 = { col_f - p3.x, row_f - p3.y };  // The vector from p3 to this LED.
      float distance3 = sqrt( dist3.x*dist3.x + dist3.y*dist3.y );
      
      // Warp the distance with a sin() function. As the distance value increases, the LEDs will get light,dark,light,dark,etc...
      // You can use a cos() for slightly different shading, or experiment with other functions. Go crazy!
      float color_1 = distance1;  // range: 0.0...1.0
      float color_2 = distance2;
      float color_3 = distance3;
      float color_4 = (sin( distance1 * distance2 * colorStretch )) + 2.0 * 0.5;
      
      // Square the color_f value to weight it towards 0. The image will be darker and have higher contrast.
      color_1 *= color_1 * color_4;
      color_2 *= color_2 * color_4;
      color_3 *= color_3 * color_4;
      color_4 *= color_4;
 
      // Scale the color up to 0..7 . Max brightness is 7.
      //strip.setPixelColor(col + (8 * row), strip.Color(color_4, 0, 0) );

       // perfect fairies
      strip.setPixelColor(col + (8 * row), strip.Color(color_2, color_3, color_1));
      
      //strip.setPixelColor(col + (8 * row), strip.Color(color_1, color_2, color_3));
      //strip.setPixelColor(col + (8 * row), strip.Color(color_1/4, color_2, color_3*5));
    }
  }
  strip.show();
}



void red_flash() {
  cycle_color_flash(50, 0, 0);
}

void generate_rotation() {
  simple_rotate(50,10,5);
}

void turquoise_flash() {
  cycle_color_flash(25, 51, 42);
}

void qcom_blue_flash() {
  cycle_color_flash(0, 51, 160);
}

void chaseBlue() {
  chasePersist(strip.numPixels(), blue);
  delay(DISPLAY_DELAY/2);
}

void simple_rotate(float rate,uint32_t cycles, uint32_t wait) {
   uint32_t pos=5;
  // cycle through x times
  for(int x=0; x<(strip.numPixels()*cycles); x++)
  {
      pos = pos+rate;
      for(int i=0; i<strip.numPixels(); i++) {                
        float level = sin(i+pos) * 127 +128 ;
        // set color level 
        strip.setPixelColor(i,(uint32_t)level,50,24); // generates pink, blue
      }
         strip.show();
         delay(wait);
  }
}

void lightening() {
  uint32_t color1= strip.Color(255,255,255);
  uint32_t color2= strip.Color(0,0,0);
  uint32_t color3= strip.Color(255,255,0);
  multi_color_flash(color1,color2,color3);
}

void multi_color_blue_yellow()
{
  multi_color_flash(honeyDew,sapphire,yellowOrange); 
}

void multi_color_blue_green()
{
  multi_color_flash(mediumSpringGreen,light_blue,leaf_green); 
}

void multi_color_flash(uint32_t color1, uint32_t color2, uint32_t color3){
    
    for(int i=0; i<NUM_LEDS; i++) {
    strip.setPixelColor(i, color1);
    strip.show();
  }
  delay(200);
 
   for(int i=0; i<NUM_LEDS; i++) {
    strip.setPixelColor(i, color2); 
    strip.show();
  }
  delay (100);
 
     for(int i=0; i<NUM_LEDS; i++) {
    strip.setPixelColor(i, color3);
    strip.show();
  }
  delay(200);
 
     for(int i=0; i<NUM_LEDS; i++) {
    strip.setPixelColor(i, color2);
    strip.show();
  }
  delay(50);
 
     for(int i=0; i<NUM_LEDS; i++) {
    strip.setPixelColor(i, color3);
    strip.show();
  }
  delay(40);
 
     for(int i=0; i<NUM_LEDS; i++) {
    strip.setPixelColor(i, color2);
    strip.show();
  }
  delay(20);
   
       for(int i=0; i<NUM_LEDS; i++) {
    strip.setPixelColor(i, color1 );
    strip.show();
  }
  delay(200);
 
     for(int i=0; i<NUM_LEDS; i++) {
    strip.setPixelColor(i, color2);
    strip.show();
  }
  delay(100);
 
     for(int i=0; i<NUM_LEDS; i++) {
    strip.setPixelColor(i, color1);
    strip.show();
  }
  delay(200);
 
   for(int i=0; i<NUM_LEDS; i++) {
    strip.setPixelColor(i, color2);
    strip.show();
  }
  delay (100);
 
     for(int i=0; i<NUM_LEDS; i++) {
    strip.setPixelColor(i, color3);
    strip.show();
  }
  delay(100);
 
    for(int i=0; i<NUM_LEDS; i++) {
    strip.setPixelColor(i, color2);
    strip.show();
  }
  delay(30);
}

void chaseYellowOrange() {
  chasePersist(strip.numPixels(), yellowOrange);
  delay(DISPLAY_DELAY/2);
}

void chaseLime() {
  chasePersist(strip.numPixels(), lime);
  delay(DISPLAY_DELAY/2);
}

void chaseHotPink() {
  chasePersist(strip.numPixels(), hot_pink);
  delay(DISPLAY_DELAY/2);
}

void chaseTurquoise() {
  chasePersist(strip.numPixels(), turquoise);
  delay(DISPLAY_DELAY/2);
}

void mediumOrchidAlternate() {
  colorAlternate(strip.numPixels(), mediumOrchid, 0);
  delay(DISPLAY_DELAY);
}

void mediumOrchidBlueAlternate() {
  colorAlternate(strip.numPixels(), mediumOrchid, blue);
  delay(DISPLAY_DELAY);
}

static void colorAlternate(int numPixels, uint32_t c, uint32_t d) {
  for(int i=0;i<numPixels;i++){
  // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    if( (i % 2) == 0) { 
      strip.setPixelColor(i, c);
    }
   else{ 
     strip.setPixelColor(i, d);
    }
  strip.setBrightness(brightness); strip.show(); // This sends the updated pixel color to the hardware.
  delay(delayVal); // Delay for a period of time (in milliseconds).
  }
}

static void chaseFlip() {
 flip(12,lightGreen);
 flip(11,honeyDew);
 flip(10,rosyBrown);
 flip(9,thistle);
 flip(8,plum);
 flip(7,mediumOrchid);
 flip(6,mediumPurple);
 flip(5,mediumSlateBlue);
 flip(4,cornFlowerBlue);
 flip(3,skyBlue);
 flip(16,turquoise);
 flip(17,aquamarine);
 flip(2,lightSkyBlue);
 flip(1,paleTurquoise);
 flip(0,powderBlue);
 flip(15,mediumTurquoise);
 flip(14,mediumSeaGreen);
 flip(13,mediumSpringGreen);
}

static void flip(int i, uint32_t c){
  strip.setPixelColor(i, c);
  strip.setBrightness(brightness); strip.show();
  delay(delayVal);
  strip.setPixelColor(i,0);
  strip.setBrightness(brightness); strip.show();
}

// An equally distributed rainbow. Is there any other kind?
void rainbowCycle() {
  uint8_t wait = 5;
  uint16_t i, j;

  for(j=0; j<256*2; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.setBrightness(70); strip.show();
    delay(wait);
  }
}

// Flash all the pixels white, then fade away.
void white_flash_fade() {
  for (int i = 100; i > 0; i--) {
    for (int j = 0; j<strip.numPixels();j++) {
      strip.setPixelColor(j, strip.Color(i,i,i));
    }
  strip.setBrightness(brightness); strip.show();
  delay(50);
  }
}

//sets the strip to all one color
static void setAll(uint32_t color) {
   for(int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
      strip.setBrightness(brightness); strip.show();
   } 
   delay(delayVal);
   strip.setBrightness(brightness); strip.show();
}

static void sparklePurple() {
  //Set all the pixels to the background color
  setAll(strip.Color(8, 0, 25));
  strip.setBrightness(brightness); strip.show();
  delay(1500);
  //Make an odd one light up and fade to the ones around it
  sparkleAll();  
  setAll(strip.Color(40, 40, 40));
  strip.setBrightness(brightness); strip.show();
}

//sparkles each of the pixels on the ring
static void sparkleAll(){
sparkleOne(7);
  delay(200);
  sparkleOne(10);
  delay(200);
  sparkleOne(1);
  delay(200);
  sparkleOne(15);
  delay(200);
  sparkleOne(2);
  delay(200);
  sparkleOne(13);
  delay(200);
  sparkleOne(16);
    delay(200);
  sparkleOne(0);
  
    delay(200);
  sparkleOne(8);
    delay(200);
  sparkleOne(3);
    delay(200);
  sparkleOne(16);
    delay(200);
  sparkleOne(6);
    delay(200);
  sparkleOne(11);
    delay(200);
  sparkleOne(4);
    delay(200);
  sparkleOne(14);
    delay(200);
  sparkleOne(5);
  delay(200);
  sparkleOne(9);
  delay(200);
  sparkleOne(12);
  delay(200);
}

static void sparkleOne(int pinNum) {
   strip.setPixelColor(pinNum, strip.Color(50, 50, 50));
   strip.setBrightness(brightness); strip.show();
   int transition = 5; 
   
   int Rstart = 50;
   int Gstart = 50; 
   int Bstart = 50;
   
   int Rend = 17;
   int Gend = 0;
   int Bend = 44;
   
   for(int i = 0; i < transition; i++) // larger values of 'n' will give a smoother/slower transition.
   {
       int Rnew = Rstart + (Rend - Rstart) * i / transition;
       int Gnew = Gstart + (Gend - Gstart) * i / transition;
       int Bnew = Bstart + (Bend - Bstart) * i / transition;
      // set pixel color here
      strip.setPixelColor(pinNum, strip.Color(Rnew, Gnew, Bnew));
      delay(100);
      strip.setBrightness(brightness); strip.show();
   }   
}

void cycle_color_flash(int rStart, int gStart, int bStart) {
  int Rstart = rStart;
  int Gstart = gStart;
  int Bstart = bStart;

  int Rend, Gend, Bend = 0;
  int n = 100;
  for(int i = 0; i < n; i++) {// larger values of 'n' will give a smoother/slower transition.
    for(int j = 0; j<strip.numPixels(); j++) {
      float Rnew = Rstart + (Rend - Rstart) * i / n;
      float Gnew = Gstart + (Gend - Gstart) * i / n;
      float Bnew = Bstart + (Bend - Bstart) * i / n;
      strip.setPixelColor(j, strip.Color(Rnew, Gnew, Bnew));
    }
    strip.setBrightness(brightness); strip.show();
    delay(10);
  }  
}

static void chaseCCW() {
  for(uint16_t i=strip.numPixels()-1; i<=0-1; i--) {
      strip.setPixelColor(i  , blue); // Draw new pixel
      strip.setPixelColor(i+1, 0); // Erase pixel a few steps back
      strip.setBrightness(brightness); strip.show();
      delay(delayVal);
  }
}

static void chasePersistCCW(int numPixels, uint32_t c) {
 for(int i=numPixels-1;i>=0;i--) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, c); // Moderately bright green color.
    strip.show(); // This sends the updated pixel color to the hardware.
    delay(delayVal); // Delay for a period of time (in milliseconds).
  } 
}

static void chasePersist(int numPixels, uint32_t c) {
 for(int i=0;i<numPixels;i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, c); // Moderately bright green color.
    strip.setBrightness(brightness); strip.show(); // This sends the updated pixel color to the hardware.
    delay(delayVal); // Delay for a period of time (in milliseconds).
  } 
}

static void chase() {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , blue); // Draw new pixel
      strip.setPixelColor(i-1, 0); // Erase pixel a few steps back
      strip.setBrightness(brightness); strip.show();
      delay(delayVal);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
