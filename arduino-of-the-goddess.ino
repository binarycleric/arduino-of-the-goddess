#include "notes.h"
#include "beats.h"

beat melody[] = {
  { NOTE_REST, QUARTER_NOTE },
  { NOTE_D4,   HALF_NOTE },
  { NOTE_D4,   QUARTER_NOTE },

  { NOTE_E4, EIGHTH_NOTE },
  { NOTE_F4, EIGHTH_NOTE },
  { NOTE_G4, HALF_NOTE },
  { NOTE_C5, QUARTER_NOTE },

  { NOTE_D5, HALF_NOTE },
  { NOTE_G4, QUARTER_NOTE },
  { NOTE_E4, QUARTER_NOTE },

  { NOTE_D4, HALF_NOTE },
  { NOTE_G4, QUARTER_NOTE },
  { NOTE_E4, QUARTER_NOTE },

  { NOTE_D4,   EIGHTH_NOTE },
  { NOTE_C4,   EIGHTH_NOTE },
  { NOTE_D4,   EIGHTH_NOTE },
  { NOTE_REST, EIGHTH_NOTE },
  { NOTE_G4,   QUARTER_NOTE },
  { NOTE_E4,   QUARTER_NOTE },

  // Second stanza
  { NOTE_REST, QUARTER_NOTE },
  { NOTE_D4,   HALF_NOTE },
  { NOTE_D4,   QUARTER_NOTE },

  { NOTE_E4, EIGHTH_NOTE },
  { NOTE_F4, EIGHTH_NOTE },
  { NOTE_G4, HALF_NOTE },
  { NOTE_C5, QUARTER_NOTE },

  { NOTE_D5, HALF_NOTE },
  { NOTE_G4, QUARTER_NOTE },
  { NOTE_E4, QUARTER_NOTE },

  { NOTE_D4, HALF_NOTE },
  { NOTE_G4, QUARTER_NOTE },
  { NOTE_E4, QUARTER_NOTE },

  { NOTE_D4,   EIGHTH_NOTE },
  { NOTE_C4,   EIGHTH_NOTE },
  { NOTE_D4,   EIGHTH_NOTE },
  { NOTE_REST, EIGHTH_NOTE },
  { NOTE_G4,   QUARTER_NOTE },
  { NOTE_E4,   QUARTER_NOTE },

  // Third stanza
  { NOTE_A4,   HALF_NOTE },
  { NOTE_A4,   EIGHTH_NOTE },
  { NOTE_G4,   EIGHTH_NOTE },
  { NOTE_F4,   EIGHTH_NOTE  },
  { NOTE_REST, EIGHTH_NOTE },

  { NOTE_F4, QUARTER_NOTE },
  { NOTE_E4, QUARTER_NOTE /* technically 4 + 1 */  },
  { NOTE_D4, EIGHTH_NOTE },
  { NOTE_G4, QUARTER_NOTE },

  { NOTE_E4, QUARTER_NOTE },
  { NOTE_C4, HALF_NOTE /* half + 1 */ },

  { NOTE_D4, QUARTER_NOTE },
  { NOTE_D4, QUARTER_NOTE },
  { NOTE_D4, QUARTER_NOTE },
  { NOTE_E4, QUARTER_NOTE },

  { NOTE_CS4, HALF_NOTE },
  { NOTE_B3,  HALF_NOTE },

  // Forth stanza
  { NOTE_A4,   HALF_NOTE },
  { NOTE_A4,   EIGHTH_NOTE },
  { NOTE_G4,   EIGHTH_NOTE },
  { NOTE_F4,   EIGHTH_NOTE  },
  { NOTE_REST, EIGHTH_NOTE },

  { NOTE_F4, QUARTER_NOTE },
  { NOTE_E4, QUARTER_NOTE /* technically 4 + 1 */  },
  { NOTE_D4, EIGHTH_NOTE },
  { NOTE_G4, QUARTER_NOTE },

  { NOTE_E4, QUARTER_NOTE },
  { NOTE_C4, HALF_NOTE /* half + 1 */ },

  { NOTE_D4, QUARTER_NOTE },
  { NOTE_D4, QUARTER_NOTE },
  { NOTE_D4, QUARTER_NOTE },
  { NOTE_E4, QUARTER_NOTE },

  { NOTE_CS4, HALF_NOTE },
  { NOTE_B3,  HALF_NOTE },

  { NOTE_A4, WHOLE_NOTE },

  // Fifth stanza
  { NOTE_REST, QUARTER_NOTE },
  { NOTE_D4,   HALF_NOTE },
  { NOTE_D4,   QUARTER_NOTE },

  { NOTE_E4, EIGHTH_NOTE },
  { NOTE_F4, EIGHTH_NOTE },
  { NOTE_G4, HALF_NOTE },
  { NOTE_C5, QUARTER_NOTE },

  { NOTE_D5, HALF_NOTE },
  { NOTE_G4, QUARTER_NOTE },
  { NOTE_E4, QUARTER_NOTE },

  { NOTE_D4, HALF_NOTE },
  { NOTE_G4, QUARTER_NOTE },
  { NOTE_E4, QUARTER_NOTE },

  { NOTE_D4,   EIGHTH_NOTE },
  { NOTE_C4,   EIGHTH_NOTE },
  { NOTE_D4,   EIGHTH_NOTE },
  { NOTE_REST, EIGHTH_NOTE },
  { NOTE_G4,   QUARTER_NOTE },
  { NOTE_E4,   QUARTER_NOTE },

  { NOTE_D4, WHOLE_NOTE },

  // Break.
  { NOTE_REST, WHOLE_NOTE },
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
  3, 0
};

int totalNotes = sizeof(melody) / sizeof(beat);
int currentNote = 0;

void setup() {
  pinMode(forwardButton.pin, INPUT);
  pinMode(backwardButton.pin, INPUT);

  pinMode(playbackLED.rPin, OUTPUT);
  pinMode(playbackLED.gPin, OUTPUT);
  pinMode(playbackLED.bPin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(3), stopMelody, CHANGE);
}

void stopMelody() {
  forwardButton.state = 0;
  stopNote();
}

void loop() { 
  if ( digitalRead(forwardButton.pin) == HIGH ) {
    forwardButton.state = 1;
  }

  if ( forwardButton.state == 1 ) {
    playbackLEDGreen();
    playNote(melody[currentNote].note, melody[currentNote].duration);

    currentNote++;

    if ( currentNote > ( totalNotes - 1) )
      currentNote = 0;
  } else {
    playbackLEDRed();
  }
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

void stopNote() {
  noTone(8);
}

void playNote(int note, int beat) {
  int noteDuration = 1000 / beat;
  int pauseBetweenNotes = noteDuration * 1.30;

  tone(8, note, noteDuration);
  delay(pauseBetweenNotes);
  noTone(8);
}
