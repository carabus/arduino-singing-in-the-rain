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

struct note melody1[] = {
  {NOTE_D4, 0.5},
  {NOTE_D4, 0.25},
  {NOTE_D4, 0.5}
};

// notes in the melody:
int melody[] = {
  NOTE_D4, NOTE_D4, NOTE_B3, NOTE_A3, NOTE_G3, NOTE_E3, NOTE_E3, NOTE_D3, NOTE_G3, 
  NOTE_G3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_D4, NOTE_D4, NOTE_D3, NOTE_E3, NOTE_G3, NOTE_G3,
  NOTE_A3, NOTE_B3, NOTE_D4, NOTE_B3, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_B3, NOTE_A3,
  NOTE_E3, NOTE_E3
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
float noteDurations[] = {
  2, 8, 8, 8, 8, 2, 4, 4, 2, 8, 8, 8, 8, 8, 2, 4, 8, 8, 2, 8, 8, 8, 2, 8, 8, 2, 8, 8, 8, 2, 4
};

void setup() {
  Serial.begin(9600);
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < sizeof(melody1)/sizeof(melody1[0]); thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 * melody1[thisNote].duration;
    tone(2, melody1[thisNote].pitch, noteDuration);
    Serial.println(melody1[thisNote].pitch);
    Serial.println(melody1[thisNote].duration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(2);
  }
}

void loop() {
  // no need to repeat the melody.
}
