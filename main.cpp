#include <Arduino.h>

const int pinLED = 2;  

//delay v milisekundach
const int dotDuration = 200;    
const int dashDuration = 600;   
const int letterSpace = 600;    
const int wordSpace = 1400;
                     

// Pole pismen
const char* morseCode[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",    // A-I
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",   // J-R
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."          // S-Z
};


void blinkLED(int duration) {
  digitalWrite(pinLED, HIGH);
  delay(duration);
  digitalWrite(pinLED, LOW);
  delay(dotDuration);  
}

// Funkce pro konverzi pismen do morseovky
void printMorse(char c) {
  if (c >= 'a' && c <= 'z') {
    c = c - 'a';
  } else if (c >= 'A' && c <= 'Z') {
    c = c - 'A';
  } else if (c == ' ') {
    delay(wordSpace);
    return;
  } else {
    Serial.println("Enter letters from a-z or A-Z");
    return; 
  }

  const char* morse = morseCode[c];
  for (int i = 0; morse[i] != '\0'; i++) {
    if (morse[i] == '.') {
      blinkLED(dotDuration);
    } else if (morse[i] == '-') {
      blinkLED(dashDuration);  
    }
  }
  delay(letterSpace);
}

void setup() {
  pinMode(pinLED, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter text to convert to Morse code:");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();  // Remove any extra whitespace

    for (int i = 0; i < input.length(); i++) {
      printMorse(input[i]);  //Prelozi kazde pismeno do morseovky a zobrazi na ledce
    }

    Serial.println("Conversion complete. Enter another text:");
  }
}
