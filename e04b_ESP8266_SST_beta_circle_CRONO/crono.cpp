#include <Arduino.h>
#include "Ucglib.h"
#include "t_constants.h"



//GENERAL
///////////////////////////////////////////////////////////
bool pushed=0;
bool changeday=0;
bool changebox=0;
bool delday=0;
byte daySelected=0;
byte boxSelected=0;
byte boxPointer=0;
byte boxPointerView=0;
byte hourSel_Box1=0;
byte hourSel_Box2=0;
int encoder0PinBLast1 = 0;
bool n = 0;
bool np = 0;


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
byte dim_y_set = 12;      //Box Dimension in Y (pixel)
byte texthour = 0;        //Text to be write (hour index)
byte spacing = 1;         //Spacing between columns (pixel)
byte spacing1 = 0;


//SELECTION
///////////////////////////////////////////////////////////
byte dDaysel = 1;         //Day Selected
byte lastDaysel=0;
byte lastBoxsel=0;
byte line=0;
byte dHourSel[7][48]={0};
/*{{1,2,3,4,5,6,7},{1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3}
                                      };     //Array Matrix
                                      */
byte setP1 = 180;         //Setpoint Eco
byte setP2 = 200;         //Setpoint Normal
byte setP3 = 220;         //Setpoint Comfort


//drawCrono
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void drawCrono(Ucglib_ILI9341_18x240x320_HWSPI ucg){ 
  //CANCELLO SCHERMO
  //Serial.println("          Cancello Schermo");
  ucg.setColor(0, 0, 0);                                      //Nero
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
      ucg.setPrintPos(start_x+(offset_x*nh)+(spacing*2),(start_y+(offset_y*nv))+offset_text);
      ucg.print(texthour); 
      for(byte nc=0;nc<2;nc++){
        ucg.drawBox(start_x+(offset_x*nh)+(dim_x*nc)+(spacing*nc) , start_y+(offset_y*nv) , dim_x , dim_y);
      }            
      //ucg.drawHLine(start_x-3, start_y-(offset_y*nv)-(dim_y_set*1) , 302);
      //ucg.drawHLine(start_x-3, start_y-(offset_y*nv)-(dim_y_set*2) , 302);
      //ucg.drawHLine(start_x-3, start_y-(offset_y*nv)-(dim_y_set*3) , 302);
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
  Serial.print("MENU' setDay ");
  ucg.setColor(102, 255, 0);           // Verde Chiaro
  ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  ucg.setFont(ucg_font_helvB14_hf);
  ucg.setPrintPos(70,235);
  ucg.print("GIORNO:"); 
  changeday=1;
  while(pushed==0){
    if(changeday==1){
      Serial.print("dDaysel ");Serial.println(dDaysel);
      ucg.setColor(0, 0, 0);            //Nero
      ucg.setPrintPos(160,235);
      ucg.drawBox(155,220,150,20);
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
  n = digitalRead(encoder0PinB); 
  if ((encoder0PinBLast1 == LOW) && (n == HIGH)) { 
       dDaysel++;
       delay(50);   
       }   
  encoder0PinBLast1 = n; 

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
  ucg.setColor(255, 255, 255);                                //Bianco
  ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  ucg.setFont(ucg_font_helvB14_hf);
  ucg.setPrintPos(70,235);
  ucg.print("GIORNO:"); 
  pushed=0;
  daySelected=dDaysel;
  Serial.print("daySelected=");Serial.println(daySelected);
  delay(250);  
}


//drawBoxes from array
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void drawBoxes(Ucglib_ILI9341_18x240x320_HWSPI ucg){
  Serial.println("MENU' drawBoxes ");
  for(byte nv=0;nv<2;nv++){
    //Serial.print("VERTICALE ");Serial.println(nv);
    for(byte nh=0;nh<12;nh++){
        for(byte nc=0;nc<2;nc++){
          //Take data from array matrix
          hourSel_Box1=dHourSel[daySelected][boxPointer]; 
          Serial.print("daySelected+boxPointer=");Serial.print(daySelected);Serial.print("  ");Serial.println(boxPointer);         
          if(hourSel_Box1>0){
            //Box C1:nh:1 
            ucg.setColor(102, 255, 0);           // Verde Chiaro
            ucg.drawBox(start_x+(offset_x*nh)+(dim_x*nc)+(spacing*nc) , (start_y-dim_y-(dim_y*2))+(offset_y*nv) , dim_x_set , dim_y_set);
            if(hourSel_Box1>1){
              //Box C1:nh:2 
              ucg.drawBox(start_x+(offset_x*nh)+(dim_x*nc)+(spacing*nc) , (start_y-dim_y-(dim_y*2)-dim_y_set)+(offset_y*nv) , dim_x_set , dim_y_set);
              if(hourSel_Box1>2){
              //Box C1:nh:3 
              ucg.drawBox(start_x+(offset_x*nh)+(dim_x*nc)+(spacing*nc) , (start_y-dim_y-(dim_y*2)-(dim_y_set*2))+(offset_y*nv) , dim_x_set , dim_y_set);
              }else{
              ucg.setColor(0, 0, 0);            //Nero
              ucg.drawBox(start_x+(offset_x*nh)+(dim_x*nc)+(spacing*nc) , (start_y-dim_y-(dim_y*2)-(dim_y_set*2))+(offset_y*nv) , dim_x_set , dim_y_set);
              }
            }else{
            ucg.setColor(0, 0, 0);            //Nero
            ucg.drawBox(start_x+(offset_x*nh)+(dim_x*nc)+(spacing*nc) , (start_y-dim_y-(dim_y*2)-dim_y_set)+(offset_y*nv) , dim_x_set , dim_y_set);
            ucg.drawBox(start_x+(offset_x*nh)+(dim_x*nc)+(spacing*nc) , (start_y-dim_y-(dim_y*2)-(dim_y_set*2))+(offset_y*nv) , dim_x_set , dim_y_set);
            }
          }else{
          ucg.setColor(0, 0, 0);            //Nero
          ucg.drawBox(start_x+(offset_x*nh)+(dim_x*nc)+(spacing*nc) , (start_y-dim_y-(dim_y*2))+(offset_y*nv) , dim_x_set , dim_y_set);
          ucg.drawBox(start_x+(offset_x*nh)+(dim_x*nc)+(spacing*nc) , (start_y-dim_y-(dim_y*2)-dim_y_set)+(offset_y*nv) , dim_x_set , dim_y_set);
          ucg.drawBox(start_x+(offset_x*nh)+(dim_x*nc)+(spacing*nc) , (start_y-dim_y-(dim_y*2)-(dim_y_set*2))+(offset_y*nv) , dim_x_set , dim_y_set);
          }          
        boxPointer++; 
        }
     }   
  }
  boxPointer=0;
  boxPointerView=0;
  spacing1=0;
  line=0;
  delay(250);
}


//setBoxes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setBoxes(Ucglib_ILI9341_18x240x320_HWSPI ucg){
  Serial.println("MENU' setBoxes ");
  while(pushed==0){
    if(changebox==1){
      ucg.setColor(102, 255, 0);           // Verde Chiaro
      ucg.drawBox(start_x+(offset_x*(boxPointerView/2))+spacing1 , start_y+(offset_y*line) , dim_x , dim_y);
      Serial.print("boxSelected ");Serial.println(boxSelected);
      Serial.print("boxPointer ");Serial.println(boxPointer); 
      switch (boxSelected){ 
        case 0:
          dHourSel[daySelected][boxPointer]=0;
          ucg.setColor(0, 0, 0);            //Nero
          //P1
          ucg.drawBox(start_x+(offset_x*(boxPointerView/2))+spacing1 , (start_y-dim_y-(dim_y*2))+(offset_y*line), dim_x_set , dim_y_set);          
          //P2
          ucg.drawBox(start_x+(offset_x*(boxPointerView/2))+spacing1 , (start_y-dim_y-(dim_y*2)-dim_y_set)+(offset_y*line) , dim_x_set , dim_y_set);
          //P3
          ucg.drawBox(start_x+(offset_x*(boxPointerView/2))+spacing1 , (start_y-dim_y-(dim_y*2)-(dim_y_set*2))+(offset_y*line) , dim_x_set , dim_y_set);
          break;
        case 1:
          dHourSel[daySelected][boxPointer]=1;                 
          ucg.setColor(102, 255, 0);           // Verde Chiaro
          //P1
          ucg.drawBox(start_x+(offset_x*(boxPointerView/2))+spacing1 , (start_y-dim_y-(dim_y*2))+(offset_y*line), dim_x_set , dim_y_set);        
          ucg.setColor(0, 0, 0);            //Nero
          //P2
          ucg.drawBox(start_x+(offset_x*(boxPointerView/2))+spacing1 , (start_y-dim_y-(dim_y*2)-dim_y_set)+(offset_y*line) , dim_x_set , dim_y_set);          
          //P3
          ucg.drawBox(start_x+(offset_x*(boxPointerView/2))+spacing1 , (start_y-dim_y-(dim_y*2)-(dim_y_set*2))+(offset_y*line) , dim_x_set , dim_y_set);         
          break;
        case 2:
          dHourSel[daySelected][boxPointer]=2;
          ucg.setColor(102, 255, 0);           // Verde Chiaro
          //P1
          ucg.drawBox(start_x+(offset_x*(boxPointerView/2))+spacing1 , (start_y-dim_y-(dim_y*2))+(offset_y*line), dim_x_set , dim_y_set);
          //P2
          ucg.drawBox(start_x+(offset_x*(boxPointerView/2))+spacing1 , (start_y-dim_y-(dim_y*2)-dim_y_set)+(offset_y*line) , dim_x_set , dim_y_set);     
          ucg.setColor(0, 0, 0);            //Nero   
          //P3
          ucg.drawBox(start_x+(offset_x*(boxPointerView/2))+spacing1 , (start_y-dim_y-(dim_y*2)-(dim_y_set*2))+(offset_y*line) , dim_x_set , dim_y_set);
          break;
        case 3:
          dHourSel[daySelected][boxPointer]=3;          
          ucg.setColor(102, 255, 0);           // Verde Chiaro
          //P1
          ucg.drawBox(start_x+(offset_x*(boxPointerView/2))+spacing1 , (start_y-dim_y-(dim_y*2))+(offset_y*line), dim_x_set , dim_y_set);
          //P2
          ucg.drawBox(start_x+(offset_x*(boxPointerView/2))+spacing1 , (start_y-dim_y-(dim_y*2)-dim_y_set)+(offset_y*line) , dim_x_set , dim_y_set);
          //P3
          ucg.drawBox(start_x+(offset_x*(boxPointerView/2))+spacing1 , (start_y-dim_y-(dim_y*2)-(dim_y_set*2))+(offset_y*line) , dim_x_set , dim_y_set);
          break;
        default: 
        break;
      }
      changebox=0;     
    }
     

  //ENCODER
  //////////////////////////////////////////////////////////////  
  n = digitalRead(encoder0PinB); 
  if ((encoder0PinBLast1 == LOW) && (n == HIGH)) { 
       boxSelected++;
       delay(250);   
       }   
  encoder0PinBLast1 = n; 

  //MIN-MAX dDaysel
  //////////////////////////////////////////////////////////////  
  if(boxSelected<0){
    boxSelected=3;
  }else if(boxSelected>3){
    boxSelected=0;
  }
    
  //Adding boxPointer
  //////////////////////////////////////////////////////////////  
  if(digitalRead(GPIO0)==LOW && (np == HIGH)){
    ucg.setColor(255, 255, 255);      //Bianco     
    ucg.drawBox(start_x+(offset_x*(boxPointerView/2))+spacing1 , start_y+(offset_y*line) , dim_x , dim_y);
    boxPointer++;
    boxPointerView++;
    if(spacing1==0){
      spacing1=dim_x+spacing;
      }else{
      spacing1=0;
      }
    if(boxPointerView>23){
      boxPointerView=0;}
    if(boxPointer>23){
      line=1; }
    if(boxPointer>47){
      boxPointer=0;
      line=0; }
    Serial.print("boxPointer= ");Serial.println(boxPointer);
    Serial.print("boxPointerView= ");Serial.println(boxPointerView);
    Serial.print("spacing1= ");Serial.println(spacing1); 
    Serial.print("line= ");Serial.println(line);  
    changebox=1;}  
    
  np = digitalRead(GPIO0); 

  
  //ESCAPE FROM WHILE with longpress
  //////////////////////////////////////////////////////////////  
  int longpress;
  if(np==LOW){
    longpress++;
    }else{
    longpress=0;
    }

  if(longpress >= 2000){
    Serial.println("longpress ");
    pushed=1;}
    else{
    pushed=0;}
    

  //OnChange
  //////////////////////////////////////////////////////////////  
  if(boxSelected!=lastBoxsel){
    changebox=1;}
  lastBoxsel=boxSelected; 
////////////////////////////////////////////////////////////////////////////////////////////////////////
delay(1); 
}
ucg.setColor(255, 255, 255);      //Bianco     
ucg.drawBox(start_x+(offset_x*(boxPointerView/2))+spacing1 , start_y+(offset_y*line) , dim_x , dim_y);
boxPointer=0;
boxPointerView=0;
pushed=0;
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

