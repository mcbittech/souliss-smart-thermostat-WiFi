#include <Arduino.h>
#include "Ucglib.h"
#include "t_constants.h"

//LAYOUT
//////////////////////////////////////////////////////////
byte start_x = 10;
byte start_y = 80;
byte offset_x = 25;
byte offset_y = 80;
byte offset_text = 25;
byte dim_x = 10;
byte dim_y = 5;
byte text=0;


//Selezioni
//////////////////////////////////////////////////////////
byte dDay = 1;


void drawCrono(Ucglib_ILI9341_18x240x320_HWSPI ucg){ 
  //CANCELLO SCHERMO
  Serial.println("          Cancello Schermo");
  ucg.setColor(0, 0, 255);                                    //Blu 
  ucg.drawBox(0, 0, ucg.getWidth(), ucg.getHeight());
  //PREPARO LAYOUT
  ucg.setColor(255, 255, 255);                                //Bianco
  ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  ucg.setFont(ucg_font_helvB14_hf);
  ucg.setPrintPos(25,20);
  ucg.print("Programmazione Giornaliera"); 
  ucg.setFont(ucg_font_helvB12_hf);
  //Quadri BASE
  for(byte nv=0;nv<2;nv++){
    Serial.print("VERTICALE ");Serial.println(nv);
    for(byte nh=0;nh<12;nh++){
      ucg.setPrintPos(start_x+(offset_x*nh)+2,(start_y+(offset_y*nv))+offset_text);
      ucg.print(text); 
      ucg.drawBox(start_x+(offset_x*nh) , start_y+(offset_y*nv) , dim_x , dim_y);
      ucg.drawBox(start_x+(offset_x*nh)+dim_x+1, start_y+(offset_y*nv) , dim_x , dim_y);
      Serial.print("ORIZZONTALE1 ");Serial.print(nh);Serial.print("  X ");Serial.print(start_x+(offset_x*nh));Serial.print("  Y ");Serial.println(start_y+(offset_y*nv));
      Serial.print("ORIZZONTALE2 ");Serial.print(nh);Serial.print("  X ");Serial.print(start_x+(offset_x*nh)+dim_x+1);Serial.print("  Y ");Serial.println(start_y+(offset_y*nv));
      text++;
    }
  }
  text=0; 
}

void setDay(Ucglib_ILI9341_18x240x320_HWSPI ucg){ 
  ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  ucg.setFont(ucg_font_helvB14_hf);
  ucg.setPrintPos(70,235);
  ucg.print("GIORNO:"); 
  ucg.setPrintPos(160,235);
    switch (dDay) {
      case 1:
        ucg.print("LUNEDI'"); 
        break;
      case 2:
        ucg.print("MARTEDI'");       
        break;
      case 3:
        ucg.print("MERCOLEDI'");       
        break;
      case 4:
        ucg.print("GIOVEDI'");       
        break;
      case 5:
        ucg.print("VENERDI'");       
        break;
      case 6:
        ucg.print("SABATO");       
        break;
      case 7:
        ucg.print("DOMENICA");       
        break;
    default: 
    break;
    }
  delay(10000);  
  ucg.setColor(0, 0, 0);                                    //Nero
  ucg.drawBox(0, 0, ucg.getWidth(), ucg.getHeight());
  
}

void refreshPointer(Ucglib_ILI9341_18x240x320_HWSPI ucg){
  
}

