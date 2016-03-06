#define PAGE_HOME 0
#define PAGE_TOPICS1 1
#define PAGE_TOPICS2 2
#define PAGE_MENU 10
#define PAGE_CRONO 11

#include <Arduino.h>
#include "pagesStruct.h"



void resetNeedRefresh(Page P){
	P.bNeedRefresh=false;
}
