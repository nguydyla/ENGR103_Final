#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>

float X, Y, Z, totalAccel;
bool hitMark = 0;
int hitCounter = 0;
int speed = 500;
int level = 1;

bool switchState; 

const uint8_t spSTART[] PROGMEM = {0x04,0xF8,0xC5,0x9C,0x03,0x1A,0xD0,0x80,0x04,0x38,0x00,0x06,0x58,0x22,0x7D,0x65,0x9D,0x87,0x8B,0x5B,0xD7,0x53,0x67,0x37,0x96,0x21,0x79,0x6F,0x7D,0xEB,0xD5,0x64,0xB7,0x92,0x43,0x9B,0xC7,0x50,0xDD,0x92,0x1D,0xF7,0x9E,0x53,0xDF,0xDD,0x59,0xCB,0x21,0xAD,0xF6,0x46,0xA0,0x08,0xE5,0x2E,0x22,0x1B,0x40,0x01,0xDD,0xB2,0x2A,0xE0,0xB7,0x0C,0x03,0x4C,0x9D,0x4A,0x80,0xEA,0x54,0xFE,0x1F};
  
///////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);
  switchState = CircuitPlayground.slideSwitch();

}

///////////////////////////////////////////////////////////////////////////////
void loop() {
  switchState = CircuitPlayground.slideSwitch();
  Serial.print("Current Level: ");
  Serial.println(level);
  pattern(speed);
  hitCheck();

  if (level < 6){
    if (hitCounter >= 4){
      hitCounter = 0;
      Serial.println("Level Passed!");
      speed = speed - 100;
      level++;
      delay(1000);
    }
  
    else{
      hitCounter = 0;
      Serial.println("Game Over!");
      Serial.print("Level Reached: ");
      Serial.println(level);
      level = 1;
      speed = 500;
      delay(1000);
    }
  }

  else if (level >= 6){
    Serial.println("You win!");
    level = 7;
    rainbowCycle(10, 10);
  }   
}

void pattern(int speed){
  CircuitPlayground.speaker.say(spSTART);
  delay(500);

  if (switchState == true){
    flashOn();
    CircuitPlayground.playTone(440, 100);
    CircuitPlayground.clearPixels();
    delay(speed);

    flashOn();
    CircuitPlayground.playTone(440, 100);
    CircuitPlayground.clearPixels();
    delay(speed);

    flashOn();
    CircuitPlayground.playTone(440, 100);
    CircuitPlayground.clearPixels();
    delay(speed);

    flashOn();
    CircuitPlayground.playTone(440, 100);
    CircuitPlayground.clearPixels();
    delay(speed);
  }
  
  else{
    flashOn();
    delay(100);
    CircuitPlayground.clearPixels();
    delay(speed);

    flashOn();
    delay(100);
    CircuitPlayground.clearPixels();
    delay(speed);

    flashOn();
    delay(100);
    CircuitPlayground.clearPixels();
    delay(speed);

    flashOn();
    delay(100);
    CircuitPlayground.clearPixels();
    delay(speed);
  }
}

void hitCheck(){
  for (int i=0; i<4; i++){
    hitMark = true;

    X = 0;
    Y = 0;
    Z = 0;

    for (int i=0; i<10; i++) {
      X += CircuitPlayground.motionX();
      Y += CircuitPlayground.motionY();
      Z += CircuitPlayground.motionZ();
      delay(1);
    }

    X /= 10;
    Y /= 10;
    Z /= 10;

    totalAccel = sqrt(X*X + Y*Y + Z*Z); //total acceleration is the magnitude of this vector?

    Serial.println(totalAccel);

    if (hitMark && totalAccel > 10){
      hitCounter++;
    }
    delay(100);
    hitMark = false;
    delay(speed);
  }

  Serial.println(hitCounter);
}

void flashOn(){
  CircuitPlayground.setPixelColor(0, 0xFFFFFF);
  CircuitPlayground.setPixelColor(1, 0xFFFFFF);
  CircuitPlayground.setPixelColor(2, 0xFFFFFF);
  CircuitPlayground.setPixelColor(3, 0xFFFFFF);
  CircuitPlayground.setPixelColor(4, 0xFFFFFF);
  CircuitPlayground.setPixelColor(5, 0xFFFFFF);
  CircuitPlayground.setPixelColor(6, 0xFFFFFF);
  CircuitPlayground.setPixelColor(7, 0xFFFFFF);
  CircuitPlayground.setPixelColor(8, 0xFFFFFF);
  CircuitPlayground.setPixelColor(9, 0xFFFFFF);
}
  
void rainbowCycle(int currentSpeed, int stripLen) {

  // Make an offset based on the current millisecond count scaled by the current speed.

  uint32_t offset = millis() / currentSpeed;

  // Loop through each pixel and set it to an incremental color wheel value.

  for(int i=0; i<10; ++i) {
    CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(((i * 256 / stripLen) + offset) & 255));

  }
}