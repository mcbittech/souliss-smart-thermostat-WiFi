#include <Arduino.h>
#include "Ucglib.h"
#include "t_constants.h"


//GENERAL
///////////////////////////////////////////////////////////
bool pushed=0;
bool changeday=0;
bool delday=0;
byte daySelected=0;
byte boxSelected=0;
byte boxPointer=0;
byte hourSel_Box1=0;
byte hourSel_Box2=0;
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
byte dim_x_set = 10;      //Box Dimension in X (pixel)
byte dim_y_set = 12;       //Box Dimension in Y (pixel)
byte texthour = 0;        //Text to be write (hour index)


//SELECTION
///////////////////////////////////////////////////////////
byte dDaysel = 1;         //Day Selected
byte lastDaysel=0;
byte dHourSel[7][48]={{1,2,3,4,5,6,7},{1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,}};     //Array Matrix
byte setP1 = 180;         //Setpoint Eco
byte setP2 = 200;         //Setpoint Normal
byte setP3 = 220;         //Setpoint Comfort


//drawCrono
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void drawCrono(Ucglib_ILI9341_18x240x320_HWSPI ucg){ 
  //CANCELLO SCHERMO
  //Serial.println("          Cancello Schermo");
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
    //Serial.print("VERTICALE ");Serial.println(nv);
    for(byte nh=0;nh<12;nh++){
      ucg.setPrintPos(start_x+(offset_x*nh)+2,(start_y+(offset_y*nv))+offset_text);
      ucg.print(texthour); 
      ucg.drawBox(start_x+(offset_x*nh) , start_y+(offset_y*nv) , dim_x , dim_y);
      ucg.drawBox(start_x+(offset_x*nh)+dim_x+1 , start_y+(offset_y*nv) , dim_x , dim_y);
      //Serial.print("ORIZZONTALE1 ");Serial.print(nh);Serial.print("  X ");Serial.print(start_x+(offset_x*nh));Serial.print("  Y ");Serial.println(start_y+(offset_y*nv));
      //Serial.print("ORIZZONTALE2 ");Serial.print(nh);Serial.print("  X ");Serial.print(start_x+(offset_x*nh)+dim_x+1);Serial.print("  Y ");Serial.println(start_y+(offset_y*nv));
      texthour++;
    }
  }
  texthour=0; 
}


//setDay
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setDay(Ucglib_ILI9341_18x240x320_HWSPI ucg){ 
  ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  ucg.setFont(ucg_font_helvB14_hf);
  ucg.setPrintPos(70,235);
  ucg.print("GIORNO:"); 
  changeday=1;
  while(pushed==0){
    if(changeday==1){
      ucg.setColor(0, 0, 255);          //Blu
      ucg.setPrintPos(160,235);
      ucg.drawBox(155,215,150,20);
      ucg.setColor(255, 255, 255);      //Bianco     
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

  //OnChange
  //////////////////////////////////////////////////////////////  
  if(dDaysel!=lastDaysel){
    changeday=1;}
  lastDaysel=dDaysel;  
//////////////////////////////////////////////////////////////////////////////////////
  
  }//endwhile

  pushed=0;
  daySelected=dDaysel;
  delay(250);  
}


//drawBoxes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void drawBoxes(Ucglib_ILI9341_18x240x320_HWSPI ucg){
  for(byte nv=0;nv<2;nv++){
    //Serial.print("VERTICALE ");Serial.println(nv);
    for(byte nh=0;nh<12;nh++){
      //Take data from array matrix
      hourSel_Box1=dHourSel[daySelected][boxPointer];       //[C1]
      hourSel_Box2=dHourSel[daySelected][boxPointer+1];     //[C2]
      
      //Prima Colonna [C1] 
      if(hourSel_Box1>0){
        //Box C1:nh:1 
        ucg.setColor(255, 0, 0);                               //Rosso
        ucg.drawBox(start_x+(offset_x*nh) , (start_y-dim_y-2)+(offset_y*nv), dim_x_set , dim_y_set);
        if(hourSel_Box1>1){
          //Box C1:nh:2 
          ucg.drawBox(start_x+(offset_x*nh) , (start_y-dim_y-2-dim_y_set)+(offset_y*nv) , dim_x_set , dim_y_set);
          if(hourSel_Box1>2){
            //Box C1:nh:3 
            ucg.drawBox(start_x+(offset_x*nh) , (start_y-dim_y-2-(dim_y_set*2))+(offset_y*nv) , dim_x_set , dim_y_set);
            }else{
              ucg.setColor(0, 0, 255);          //Blu
              ucg.drawBox(start_x+(offset_x*nh) , (start_y-dim_y-2-(dim_y_set*2))+(offset_y*nv) , dim_x_set , dim_y_set);  
              }
          }else{
            ucg.setColor(0, 0, 255);          //Blu
            ucg.drawBox(start_x+(offset_x*nh) , (start_y-dim_y-2-dim_y_set)+(offset_y*nv) , dim_x_set , dim_y_set);
            }
        }else{
          ucg.setColor(0, 0, 255);          //Blu
          ucg.drawBox(start_x+(offset_x*nh) , (start_y-dim_y-2) , dim_x_set , dim_y_set);
          }
          
        //Seconda Colonna [C2]  
        if(hourSel_Box2>0){    
          //Box C2:nh:1
          ucg.setColor(255, 0, 0);                               //Rosso
          ucg.drawBox(start_x+(offset_x*nh)+dim_x+1 , (start_y-dim_y-2)+(offset_y*nv), dim_x_set , dim_y_set);     
          if(hourSel_Box2>1){
            //Box C2:nh:2
            ucg.drawBox(start_x+(offset_x*nh)+dim_x+1 , (start_y-dim_y-2-dim_y_set)+(offset_y*nv) , dim_x_set , dim_y_set);  
            if(hourSel_Box2>2){    
              //Box C2:nh:3
              ucg.drawBox(start_x+(offset_x*nh)+dim_x+1 , (start_y-dim_y-2-(dim_y_set*2))+(offset_y*nv) , dim_x_set , dim_y_set);
            }else{
              ucg.setColor(0, 0, 255);          //Blu
              ucg.drawBox(start_x+(offset_x*nh)+dim_x+1 , (start_y-dim_y-2-(dim_y_set*2))+(offset_y*nv) , dim_x_set , dim_y_set);               
              }
          }else{
            ucg.setColor(0, 0, 255);          //Blu
            ucg.drawBox(start_x+(offset_x*nh)+dim_x+1 , (start_y-dim_y-2-dim_y_set)+(offset_y*nv) , dim_x_set , dim_y_set);            
            }
        }else{
          ucg.setColor(0, 0, 255);          //Blu
          ucg.drawBox(start_x+(offset_x*nh)+dim_x+1 , (start_y-dim_y-2) , dim_x_set , dim_y_set);
          }
    boxPointer=boxPointer+2;      
    }
  }
  boxPointer=0;
}



//clearScreen
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void clearScreen(Ucglib_ILI9341_18x240x320_HWSPI ucg){
  delay(1000);
  ucg.setColor(0, 0, 0);                                 //Nero
  ucg.drawBox(0, 0, ucg.getWidth(), ucg.getHeight());
}


//refreshPointer
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void refreshPointer(Ucglib_ILI9341_18x240x320_HWSPI ucg){
  
}

