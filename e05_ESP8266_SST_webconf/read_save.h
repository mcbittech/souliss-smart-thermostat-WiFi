#include <Arduino.h>
#include <EEPROM.h>

void save_eeprom_byte(int,byte);
void save_eeprom_int(int,int);
byte read_eeprom_byte(int);
int read_eeprom_int(int);
const char* read_spiffs_prefs(const char*);
//void save_spiffs_prefs();
void save_spiffs_prefs(int, int, int, int, int, int, int ,int);

