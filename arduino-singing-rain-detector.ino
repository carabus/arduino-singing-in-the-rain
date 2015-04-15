#include "pitches.h"
#include "melody.h"

const int RAIN_THRESHOLD = 700;
const int SENSOR_PIN = A0;
const int BUZZER_PIN = 2;
  
const int SILENCE_COMMAND = 1;

enum mode {SOUND_ON, SOUND_OFF};
enum mode deviceMode = SOUND_ON;

void setup() {
  Serial.begin(115200);
}

void loop() {

  if (Serial.available()) {
    if (Serial.read() == SILENCE_COMMAND) {
      deviceMode = SOUND_OFF;
    } 
  }

  int sensorReading = analogRead(SENSOR_PIN);
  Serial.println(sensorReading);

  if (sensorReading < RAIN_THRESHOLD) {
    if (deviceMode != SOUND_OFF) {
      //Serial.println("I'm singing in the rain");
      buzzerSound();
    }   
  }
  else {
    deviceMode = SOUND_ON;
  }

  delay(1000*20); // delay between reads = 1 minute
}

void buzzerSound() {
  for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote++) {
    int noteDuration = 1000 * melody[thisNote].duration;
    tone(BUZZER_PIN, melody[thisNote].pitch, noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
  }
}
