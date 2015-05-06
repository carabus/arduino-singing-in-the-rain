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

  int sensorReading = 1023;//analogRead(SENSOR_PIN);

  bool isRaining = sensorReading < RAIN_THRESHOLD;

  sendMessage(isRaining, sensorReading);

  if (isRaining) {
    if (deviceMode != SOUND_OFF) {
      //Serial.println("I'm singing in the rain");
      //buzzerSound();
    }
  }
  else {
    deviceMode = SOUND_ON;
  }

  delay(1000 * 20); // delay between reads = 1 minute
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

/*
Message format:
5 bytes
1 - beginning of the message
2 - isRaining
3 - buzzerMode
4,5 - sensorReading
*/

void sendMessage(bool isRaining, int sensorReading) {
  byte message[] = {0xff, isRaining ? 1 : 0, deviceMode == SOUND_ON ? 1 : 0, lowByte(sensorReading), highByte(sensorReading)};
  Serial.write(message, 5);
}

