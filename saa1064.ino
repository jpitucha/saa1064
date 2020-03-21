#include <Wire.h>

byte saa1064 = 0x70 >> 1;

int digits[10]={0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};
int lines[9] = {0b00000000, 0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000, 0b10000000};
int filledLines[9] = {0b00000000, 0b00000001, 0b00000011, 0b00000111, 0b00001111, 0b00011111, 0b00111111, 0b01111111, 0b11111111};

void setup() {
  Wire.begin();
  delay(500);
  initDisplay();
}

void initDisplay() {
  Wire.beginTransmission(saa1064);
  Wire.write(0);
  Wire.write(0b00100111);
  Wire.endTransmission();
}

void displayDigits(byte num) {
  byte d1 = num / 10;
  byte d2 = num % 10;
  Wire.beginTransmission(saa1064);
  Wire.write(3);
  Wire.write(digits[d2]);
  Wire.write(digits[d1]);
  Wire.endTransmission();
}

void displayLine(byte num, bool fill) {
  clearLines();
  if (fill) {
    if (num <= 8) {
      Wire.beginTransmission(saa1064);
      Wire.write(1);
      Wire.write(filledLines[num]);
      Wire.endTransmission();
    } else {
      Wire.beginTransmission(saa1064);
      Wire.write(1);
      Wire.write(filledLines[8]);
      Wire.write(filledLines[num - 8]);
      Wire.endTransmission();
    }
  } else {
    if (num <= 8) {
      Wire.beginTransmission(saa1064);
      Wire.write(1);
      Wire.write(lines[num]);
      Wire.endTransmission();
    } else {
      Wire.beginTransmission(saa1064);
      Wire.write(1);
      Wire.write(0);
      Wire.write(lines[num - 8]);
      Wire.endTransmission();
    }
  }
}

void clearDigits() {
  Wire.beginTransmission(saa1064);
  Wire.write(3);
  Wire.write(0);
  Wire.write(0);
  Wire.endTransmission();
}

void clearLines() {
  Wire.beginTransmission(saa1064);
  Wire.write(1);
  Wire.write(0);
  Wire.write(0);
  Wire.endTransmission();
}

void loop() {
  for (int i = 0; i <= 99; i++) {
    displayDigits(i);
    displayLine(map(i, 0, 99, 1, 16), false);
    delay(100);
  }
  for (int i = 0; i <= 99; i++) {
    displayDigits(i);
    displayLine(map(i, 0, 99, 1, 16), true);
    delay(100);
  }
}
