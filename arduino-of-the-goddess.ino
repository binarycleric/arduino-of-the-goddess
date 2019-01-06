#include "notes.h"
#include "beats.h"

beat melody[] = {
  { NOTE_REST, QUARTER_NOTE },
  { NOTE_D4,   HALF_NOTE_TIE },

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
  { NOTE_D4,   HALF_NOTE_TIE },

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
  { NOTE_E4, QUARTER_NOTE_TIE },
  { NOTE_D4, EIGHTH_NOTE },
  { NOTE_G4, QUARTER_NOTE },

  { NOTE_E4, QUARTER_NOTE },
  { NOTE_C4, HALF_NOTE_TIE },

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
  { NOTE_E4, QUARTER_NOTE_TIE },
  { NOTE_D4, EIGHTH_NOTE },
  { NOTE_G4, QUARTER_NOTE },

  { NOTE_E4, QUARTER_NOTE },
  { NOTE_C4, HALF_NOTE_TIE },

  { NOTE_D4, QUARTER_NOTE },
  { NOTE_D4, QUARTER_NOTE },
  { NOTE_D4, QUARTER_NOTE },
  { NOTE_E4, QUARTER_NOTE },

  { NOTE_CS4, HALF_NOTE },
  { NOTE_B3,  HALF_NOTE },

  { NOTE_A4, WHOLE_NOTE },

  // Fifth stanza
  { NOTE_REST, QUARTER_NOTE },
  { NOTE_D4,   HALF_NOTE_TIE },

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

int totalNotes = sizeof(melody) / sizeof(beat);
int currentNote = 0;
int speakerPin = 8;

void setup() {
  pinMode(forwardButton.pin, INPUT);

  pinMode(playbackLED.rPin, OUTPUT);
  pinMode(playbackLED.gPin, OUTPUT);
  pinMode(playbackLED.bPin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(3), stopMelody, HIGH);
}

void stopMelody() {
  forwardButton.state = 0;
  playbackLEDRed();
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

    if ( currentNote > ( totalNotes - 1) ) {
      currentNote = 0;
    }
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
  noTone(speakerPin);
}

int beatsPerMinute = 60;

int noteDuration(int beat, int bpm) {
  int duration;

  if ( beat == WHOLE_NOTE ) {
    duration = 1000;
  } else if ( beat == HALF_NOTE_TIE ) {
    duration = 750;
  } else if ( beat == HALF_NOTE ) {
    duration = 500;
  } else if ( beat == QUARTER_NOTE_TIE ) {
    duration = (250 + 125);
  } else if ( beat == QUARTER_NOTE ) {
    duration = 250;
  } else if ( beat == EIGHTH_NOTE_TIE ) {
    duration = 125 + 62; // ( 62.5 )
  } else if ( beat == EIGHTH_NOTE ) {
    duration = 125;    
  } else {
    // SHRUG. Raise an error.
  }

  return duration;
}

void playNote(int note, int beat) {
  int duration = noteDuration(beat, 60);
  int pauseBetweenNotes = duration * 1.30;

  tone(speakerPin, note, duration);
  delay(pauseBetweenNotes);
  noTone(speakerPin);
}
