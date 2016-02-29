#include <Arduino.h>
#include <EEPROM.h>

void save_eeprom_byte(int,byte);
void save_eeprom_int(int,int);
byte read_eeprom_byte(int);
int read_eeprom_int(int);

