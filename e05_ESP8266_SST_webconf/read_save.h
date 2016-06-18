#include <Arduino.h>
#include <EEPROM.h>

boolean read_spiffs_prefs();
void save_spiffs_prefs(int, int, int, int, int, int, int, int, int);
int read_JSON_integer(const char*);
