#include <Arduino.h>
#include "pagesStruct.h"



void resetNeedRefresh(Page P){
	P.bNeedRefresh=false;
}
