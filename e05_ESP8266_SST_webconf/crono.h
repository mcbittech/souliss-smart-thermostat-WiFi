#include <Arduino.h>
#include "Ucglib.h"




void drawCrono(Ucglib_ILI9341_18x240x320_HWSPI);
void drawSetpoint(Ucglib_ILI9341_18x240x320_HWSPI);
void setSetpoint(Ucglib_ILI9341_18x240x320_HWSPI);
void setDay(Ucglib_ILI9341_18x240x320_HWSPI);
void drawBoxes(Ucglib_ILI9341_18x240x320_HWSPI);
void setBoxes(Ucglib_ILI9341_18x240x320_HWSPI);
void clearScreen(Ucglib_ILI9341_18x240x320_HWSPI);
void refreshPointer();
void SaveCronoMatrixSPIFFS(Ucglib_ILI9341_18x240x320_HWSPI);
void ReadCronoMatrixSPIFFS();
void copyDay(int);
void pasteDay(int);
float checkNTPcrono(Ucglib_ILI9341_18x240x320_HWSPI);
boolean exitmainmenu();
