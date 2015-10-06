#include <Arduino.h>
#include "Ucglib.h"
#include "t_constants.h"


//GENERAL
///////////////////////////////////////////////////////////
bool pushed=0;
bool changeday=0;
bool delday=0;
int encoder0PinALast1 = 0;
int n = 0;


//LAYOUT
///////////////////////////////////////////////////////////
byte start_x = 10;        //Start Position Layout X (pixel)
byte start_y = 80;        //Start Position Layout Y (pixel)
byte offset_x = 25;       //Offset between  columns (pixel)
byte offset_y = 80;       //Offset between  rows (pixel)
byte offset_text = 25;    //Offset between Text (pixel)
byte dim_x = 10;          //Box Dimension in X (pixel)
byte dim_y = 5;           //Box Dimension in Y (pixel)
byte texthour = 0;        //Text to be write (hour index)


//SELECTION
///////////////////////////////////////////////////////////
byte dDaysel = 1;         //Day Selected
byte dHourSel [7][48];    //Array Matrix
byte setP1 = 180;         //Setpoint Eco
byte setP2 = 200;         //Setpoint Normal
byte setP3 = 220;         //Setpoint Comfort


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
      ucg.print(texthour); 
      ucg.drawBox(start_x+(offset_x*nh) , start_y+(offset_y*nv) , dim_x , dim_y);
      ucg.drawBox(start_x+(offset_x*nh)+dim_x+1, start_y+(offset_y*nv) , dim_x , dim_y);
      Serial.print("ORIZZONTALE1 ");Serial.print(nh);Serial.print("  X ");Serial.print(start_x+(offset_x*nh));Serial.print("  Y ");Serial.println(start_y+(offset_y*nv));
      Serial.print("ORIZZONTALE2 ");Serial.print(nh);Serial.print("  X ");Serial.print(start_x+(offset_x*nh)+dim_x+1);Serial.print("  Y ");Serial.println(start_y+(offset_y*nv));
      texthour++;
    }
  }
  texthour=0; 
}

void setDay(Ucglib_ILI9341_18x240x320_HWSPI ucg){ 
  ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  ucg.setFont(ucg_font_helvB14_hf);
  ucg.setPrintPos(70,235);
  ucg.print("GIORNO:"); 
  changeday=1;
  while(pushed==0){
    if(changeday==1){
      ucg.setColor(0, 0, 255);
      ucg.setPrintPos(160,235);
      ucg.drawBox(155,215,150,20);
      ucg.setColor(255, 255, 255);                                //Bianco     
      ucg.setPrintPos(160,235);
      switch (dDaysel){
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
    changeday=0; 
    }
  delay(1);

  //ENCODER
  //////////////////////////////////////////////////////////////  
  n = digitalRead(encoder0PinA); 
  if ((encoder0PinALast1 == LOW) && (n == HIGH)) { 
       dDaysel++;
       changeday=1;
       }   
  encoder0PinALast1 = n; 

  //MIN-MAX dDaysel
  //////////////////////////////////////////////////////////////  
  if(dDaysel<1){
    dDaysel=7;
  }else if(dDaysel>7){
    dDaysel=1;
  }
    
  //ESCAPE FROM WHILE
  //////////////////////////////////////////////////////////////  
  if(digitalRead(GPIO0)==LOW){
    pushed=1;}
  else{
    pushed=0;}      
  }

  pushed=0;
  delay(500);  
  //Cancello Schermo
  ucg.setColor(0, 0, 0);                                    //Nero
  ucg.drawBox(0, 0, ucg.getWidth(), ucg.getHeight());
  
}

void refreshPointer(Ucglib_ILI9341_18x240x320_HWSPI ucg){
  
}

