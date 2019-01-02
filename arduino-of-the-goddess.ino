#include "notes.h"

int melody[] = { 
  NOTE_REST, NOTE_D4, 
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_C5, 
  NOTE_D5, NOTE_G4, NOTE_E4,
  NOTE_D4, NOTE_G4, NOTE_E4, 
  NOTE_D4, NOTE_C4, NOTE_D4, NOTE_REST, NOTE_G4, NOTE_E4,

  NOTE_REST, NOTE_D4, 
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_C5, 
  NOTE_D5, NOTE_G4, NOTE_E4,
  NOTE_D4, NOTE_G4, NOTE_E4, 
  NOTE_D4, NOTE_C4, NOTE_D4, NOTE_REST, NOTE_G4, NOTE_E4,

  NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_REST,
  NOTE_F4, NOTE_E4, NOTE_D4, NOTE_G4, 
  NOTE_E4, NOTE_C4,
  NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4,
  NOTE_B3, NOTE_A3,
  NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_REST,

  NOTE_F4, NOTE_E4, NOTE_D4, NOTE_G4,
  NOTE_E4, NOTE_C4,
  NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4,
  NOTE_B3, NOTE_A3,
  NOTE_A4,
};

int beats[] = {
  4, 3, 
  8, 8, 2, 4, 
  2, 4, 4,
  2, 4, 4, 
  8, 8, 8, 8, 4, 4,

  4, 3, 
  8, 8, 2, 4, 
  2, 4, 4,
  2, 4, 4, 
  8, 8, 8, 8, 4, 4,

  2, 8, 8, 8, 8,
  4, 4, 4, 4,
  4, 3,
  4, 4, 4, 4,
  2, 2,
  2, 8, 8, 8, 8,

  4, 4, 4, 4,
  4, 3,
  4, 4, 4, 4,
  2, 2,
  1
};

struct playButton {
  int pin;
  int state;
};

struct indicatorLED {
  int rPin;
  int gPin;
  int bPin;
};

indicatorLED playbackLED = {
  11, 12, 13
};

playButton forwardButton = {
  2, 0
};

playButton backwardButton = {
  4, 0
};

void setup() {
  pinMode(forwardButton.pin, INPUT);
  pinMode(backwardButton.pin, INPUT);

  pinMode(playbackLED.rPin, OUTPUT);
  pinMode(playbackLED.gPin, OUTPUT);
  pinMode(playbackLED.bPin, OUTPUT);

}

void playbackLEDWhite() {
  analogWrite(playbackLED.rPin, 255);
  analogWrite(playbackLED.gPin, 255);
  analogWrite(playbackLED.bPin, 255);      
}

void playbackLEDGreen() {
  analogWrite(playbackLED.rPin, 0);
  analogWrite(playbackLED.gPin, 255);
  analogWrite(playbackLED.bPin, 0);    
}

void playbackLEDBlue() {
  analogWrite(playbackLED.rPin, 0);
  analogWrite(playbackLED.gPin, 0);
  analogWrite(playbackLED.bPin, 255);  
}

void playbackLEDRed() {
  analogWrite(playbackLED.rPin, 255);
  analogWrite(playbackLED.gPin, 0);
  analogWrite(playbackLED.bPin, 0);  
}

void blinkLEDBlueWhite() {
  playbackLEDWhite();
  delay(500);
  playbackLEDBlue();
  delay(500);
  
}

void loop() {
  playbackLEDWhite();
  // blinkLEDBlueWhite();
  
  if ( digitalRead(forwardButton.pin) == HIGH ) {
    int totalNotes = sizeof(beats) / sizeof(int);    

    playbackLEDGreen();
    playMelody(melody, beats, totalNotes);
  } else if ( digitalRead(backwardButton.pin) == HIGH ) {
    int totalNotes = sizeof(beats) / sizeof(int);    

    int reversedMelody[totalNotes];
    int reversedBeats[totalNotes];

    for (int i = 0; i < totalNotes; i++) {
      reversedMelody[i] = melody[(totalNotes - 1) - i];
      reversedBeats[i] = beats[(totalNotes - 1) - i];
    }

    playbackLEDRed();
    playMelody(reversedMelody, reversedBeats, totalNotes);
  }
}

int beatDuration(int beat) {
  return 1000 / beat;
}

void playMelody(int notes[], int beats[], int totalNotes) {
  for (int thisNote = 0; thisNote < totalNotes; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    // int noteDuration = 1000 / beats[thisNote];

    int noteDuration = beatDuration(beats[thisNote]);

    tone(8, notes[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    
    delay(pauseBetweenNotes);
   
    // stop the tone playing:
    noTone(8);
  }
}
