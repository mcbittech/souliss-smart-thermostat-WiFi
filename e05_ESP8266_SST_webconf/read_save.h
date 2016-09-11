#include <Arduino.h>
#include <EEPROM.h>

int read_spiffs_prefs(const char*);
void save_spiffs_prefs(int, int, int, int, int, int, int, int, int);
void spiffs_Reset();

