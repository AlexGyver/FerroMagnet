#define MAGNET_PIN 3    // пин магнита
#define SOUND_PIN A0    // пин микрофона
#define DELAY_PIN A1    // крутилка длины импульса
#define POWER_PIN A2    // крутилка силы импульса

#define POWER_MIN 30    // постоянный сигнал на магнит (0-255)

#include <VolAnalyzer.h>
VolAnalyzer vol(SOUND_PIN);

void setup() {
  //Serial.begin(9600);
  pinMode(MAGNET_PIN, OUTPUT);
  vol.setTrsh(60);
  vol.setVolMax(255);
  vol.setPulseMin(80);
  vol.setPulseMax(200);
}

void loop() {
  static uint32_t tmr;
  
  if (vol.tick()) {
    if (vol.pulse()) {      // зарегистрирован громкий звук
      tmr = millis();       // сброс таймера
      // включаем магнит
      analogWrite(MAGNET_PIN, analogRead(POWER_PIN) / 4);
    }
    //Serial.println(vol.getVol());
  }
    
  // таймер активен и пришло время выключать магнит
  if (tmr && millis() - tmr > (analogRead(DELAY_PIN) / 10)) {
    tmr = 0;
    // ставим на указанный минимальный сигнал
    analogWrite(MAGNET_PIN, POWER_MIN);
  }
}