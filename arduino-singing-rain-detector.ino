#include "pitches.h"
#include "melody.h"

const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read the sensor on analog A0:
  int sensorReading = analogRead(A0);
  // map the sensor range (four options):
  // ex: 'long int map(long int, long int, long int, long int, long int)'
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);

  // range value:
  switch (range) {
    case 0:    // Sensor getting wet
      Serial.println("Flood");
      buzzerSound();
      break;
    case 1:    // Sensor getting wet
      Serial.println("Rain Warning");
      buzzerSound();
      break;
    case 2:    // Sensor dry - To shut this up delete the " Serial.println("Not Raining"); " below.
      Serial.println("Not Raining");
      break;
  }
  delay(1);  // delay between reads
}

void buzzerSound() {
  Serial.println(sizeof(melody));
  Serial.println(sizeof(melody[0]));
  for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote++) {
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
