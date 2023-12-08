#include "EEPROMManager.h"
EEPROMManager memory(512);


void setup() {
  Serial.begin(115200);
  memory.begin();
  memory.clear();
}

void loop() {
  
}
