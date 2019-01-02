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

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);

  int totalNotes = sizeof(beats) / sizeof(int);

  if (false) {
    int reversedMelody[totalNotes];
    int reversedBeats[totalNotes];

    for (int i = 0; i < totalNotes; i++) {
      reversedMelody[i] = melody[(totalNotes - 1) - i];
      reversedBeats[i] = beats[(totalNotes - 1) - i];
    }
    
    playMelody(reversedMelody, reversedBeats, totalNotes);
  } else {
    playMelody(melody, beats, totalNotes);
  }
}

void loop() {
}

void playMelody(int notes[], int beats[], int totalNotes) {
  for (int thisNote = 0; thisNote < totalNotes; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / beats[thisNote];

    tone(8, notes[thisNote], noteDuration);

    if (melody[thisNote] <= NOTE_E4) {
      digitalWrite(13, HIGH);      
    } else {
      digitalWrite(12, HIGH);    
    }

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    
    delay(pauseBetweenNotes);

    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    
    // stop the tone playing:
    noTone(8);
  }
}
