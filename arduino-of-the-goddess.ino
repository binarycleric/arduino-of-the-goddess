#include "notes.h"

#define WHOLE_NOTE     1
#define HALF_NOTE      2
#define QUARTER_NOTE   4
#define EIGHTH_NOTE    8

struct beat {
  int note;
  int duration;
};

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
  4, 0
};

int totalNotes = sizeof(melody) / sizeof(beat);
int currentNote = 0;
bool play = false;

void setup() {
  pinMode(forwardButton.pin, INPUT);
  pinMode(backwardButton.pin, INPUT);

  pinMode(playbackLED.rPin, OUTPUT);
  pinMode(playbackLED.gPin, OUTPUT);
  pinMode(playbackLED.bPin, OUTPUT);
}

void loop() { 
  if ( digitalRead(forwardButton.pin) == HIGH ) {
    play = true;
    playbackLEDGreen();

    bool backwards = true;
    currentNote = totalNotes - 1;
  } else if ( digitalRead(backwardButton.pin) == HIGH ) {
    play = false;
    playbackLEDRed();    
  } else {
    playbackLEDRed();
  }

  if ( play == true ) {
    playbackLEDGreen();
    playNote(melody[currentNote].note, melody[currentNote].duration);

    currentNote++;
  
    if ( currentNote > ( totalNotes - 1) )
      currentNote = 0;   
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

void playNote(int note, int beat) {
  int noteDuration = 1000 / beat;
  int pauseBetweenNotes = noteDuration * 1.30;
  
  tone(8, note, noteDuration);
  delay(pauseBetweenNotes);
  noTone(8); 
}
