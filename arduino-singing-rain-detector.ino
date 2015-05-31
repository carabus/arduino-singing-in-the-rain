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
  
  // Listen on bluetooth serial port for command to stop the music
  if (gotSilenceCommand()) {
      deviceMode = SOUND_OFF;
  }

  int sensorReading = 1023;//analogRead(SENSOR_PIN);

  bool isRaining = sensorReading < RAIN_THRESHOLD;

  // Send message via bluetooth serial port with current sensor reading
  sendMessage(isRaining, sensorReading);

  if (isRaining) {
    if (deviceMode != SOUND_OFF) {
      mockBuzzerSound();
    }
  }
  else {
    // turn device sound mode on when current rain event is ended (sensor getting dry)
    deviceMode = SOUND_ON;
  }

  delay(1000 * 20); // delay between reads
}

/*
Play melody on the buzzer
*/
void buzzerSound() {
  for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote++) {
    if (gotSilenceCommand()) {
      deviceMode = SOUND_OFF;
      break;
    }
    int noteDuration = 1000 * melody[thisNote].duration;
    tone(BUZZER_PIN, melody[thisNote].pitch, noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
  }
}

void mockBuzzerSound() {
  for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote++) {
    int noteDuration = 1000 * melody[thisNote].duration;
    Serial.print("la");
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
  }  
}

boolean gotSilenceCommand() {
  if (Serial.available()) {
    if (Serial.read() == SILENCE_COMMAND) {
      return true;
    }
  }
  return false;  
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

