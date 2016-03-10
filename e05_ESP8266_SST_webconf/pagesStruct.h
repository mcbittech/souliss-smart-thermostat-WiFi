#include <Arduino.h>

#define PAGE_HOME 0
#define PAGE_TOPICS1 1
#define PAGE_TOPICS2 2
#define PAGE_MENU 8
#define PAGE_CRONO 9


typedef struct {
  byte actualPage;
  bool bNeedRefresh;
} Page;


void resetNeedRefresh(Page P);
