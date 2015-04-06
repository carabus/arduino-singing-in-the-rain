/*
  Melody

 Plays a melody

 circuit:
 * 8-ohm speaker on digital pin 8

 http://arduino.cc/en/Tutorial/Tone

 */
#include "pitches.h"

struct note {
  int pitch;
  float duration;
}; 

struct note melody[] = {
  {NOTE_D4, 0.5},
  {NOTE_D4, 0.25},
  {NOTE_D4, 0.5}
};

void setup() {
  Serial.begin(9600);
  buzzerSound();
}

void loop() {
  // no need to repeat the melody.
}

void buzzerSound() {
  Serial.println(sizeof(melody));
  Serial.println(sizeof(melody[0]));
  for (int thisNote = 0; thisNote < sizeof(melody)/sizeof(melody[0]); thisNote++) {
    int noteDuration = 1000 * melody[thisNote].duration;
    Serial.println(melody[thisNote].duration);
    Serial.println(melody[thisNote].duration);    
    tone(2, melody[thisNote].pitch, noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    // noTone(2);
  }  
}
