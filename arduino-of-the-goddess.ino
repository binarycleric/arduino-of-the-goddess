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
  NOTE_CS4, NOTE_B3,
  NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_REST,

  NOTE_F4, NOTE_E4, NOTE_D4, NOTE_G4,
  NOTE_E4, NOTE_C4,
  NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4,
  NOTE_CS4, NOTE_B3,
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

int currentNote = 0;
int currentBeat = 0;
bool play = false;

void setup() {
  pinMode(forwardButton.pin, INPUT);
  pinMode(backwardButton.pin, INPUT);

  pinMode(playbackLED.rPin, OUTPUT);
  pinMode(playbackLED.gPin, OUTPUT);
  pinMode(playbackLED.bPin, OUTPUT);
}

void loop() {
  // playbackLEDRed();
  // playSingleBeat();
  // playWholeMelody();


  if ( digitalRead(forwardButton.pin) == HIGH ) {
    play = true;
    playbackLEDGreen();
  } else if ( digitalRead(backwardButton.pin) == HIGH ) {
    play = false;
    playbackLEDRed();    
  } else {
    playbackLEDRed();
  }

  if ( play == true ) {
    int totalNotes = sizeof(beats) / sizeof(int);    

    playbackLEDGreen();
    playNote(melody[currentNote], beats[currentNote]);
  
    currentNote++;
    currentBeat++;
  
    if ( currentNote > ( totalNotes - 1) )
      currentNote = 0;
  
    if (currentBeat > ( totalNotes  - 1 ) )
      currentBeat = 0;
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

void playSingleBeat() {
  int totalNotes = sizeof(beats) / sizeof(int);    

  if ( digitalRead(forwardButton.pin) == HIGH ) {
    playNote(melody[currentNote], beats[currentNote]);

    currentNote++;
    currentBeat++;

    if ( currentNote > ( totalNotes - 1) )
      currentNote = 0;

    if (currentBeat > ( totalNotes  - 1 ) )
      currentBeat = 0;
  }

  if ( digitalRead(backwardButton.pin) == HIGH  ) {
    playNote(melody[currentNote], beats[currentNote]); 
    
    currentNote--;
    currentBeat--;
    
    if ( currentNote < 0 )
      currentNote = (totalNotes - 1);

    if ( currentBeat < 0 )
      currentBeat = (totalNotes - 1);
  }  
}

void playWholeMelody() {
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

    playbackLEDBlue();
    playMelody(reversedMelody, reversedBeats, totalNotes);
  }  
}

void playNote(int note, int beat) {
  int noteDuration = 1000 / beat;
  int pauseBetweenNotes = noteDuration * 1.30;
  
  tone(8, note, noteDuration);
  delay(pauseBetweenNotes);
  noTone(8); 
}

void playMelody(int notes[], int beats[], int totalNotes) {
  for (int thisNote = 0; thisNote < totalNotes; thisNote++) {
    playNote(notes[thisNote], beats[thisNote]);
  }
}
