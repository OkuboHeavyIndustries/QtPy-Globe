#include <U8g2lib.h>
#include "ArduinoLowPower.h"
#include "lat_and_lon.h"
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
void circle();

void setup() {
  // put your setup code here, to run once:
u8g2.begin();
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
do {
    u8g2.firstPage();

    //circle();
    //circle1();
    //sphere();
    globe();
    
    } while ( u8g2.nextPage() );
}

void circle(){
  int x, y;
  int radius = 32;
  float theta = 0.0;
  float theta_stepsize = 0.3;
  while (theta < 2* PI){
    x = radius * cos (theta);
    
    y = radius * sin (theta);
    Serial.print(x);
    Serial.print(", ");
    Serial.println(y);
    u8g2.drawPixel(x+64,y+32);
    theta += theta_stepsize;
  }
}

void circle1(){
  int x, y, z;
  int radius = 15;
  float theta = 0.0;
  float theta_rot = 0.0;
  float theta_stepsize = 24;
  for (theta = 0; theta < 360; theta+=theta_stepsize){
    theta_rot = theta * 0.0174532; //0.0174532 = one degree
    x = radius * cos (theta_rot);
  
    //y = radius * sin (theta_rot);
    y = 31;
    z = radius * sin (theta_rot);
    Serial.print("{");
    Serial.print(x);
    Serial.print(", ");
    Serial.print(y);
    Serial.print(", ");
    Serial.print(z);
    Serial.println("},");
    u8g2.drawPixel(x+64,z+32);
    
  }
  Serial.println("End of sphere");
  Serial.println(" ");
}

void sphere(){
  int x, y, z;
  int radius = 64;
  float theta = 0.0;
  float phi = 0.0;
  float theta_stepsize = 36;
  float phi_stepsize = 36;
  float theta_rot;
  float phi_rot;
  for (theta = 0; theta < 360; theta+=theta_stepsize){
    theta_rot = theta * 0.0174532; //0.0174532 = one degree
    for (phi = 0; phi < 180; phi+=phi_stepsize){
      phi_rot = phi * 0.0174532; //0.0174532 = one degree
    x = radius * cos (theta_rot) * sin(phi_rot);
    y = radius * sin (theta_rot) * sin(phi_rot);
    z = radius * cos (phi_rot);
    Serial.print("{");
    Serial.print(x);
    Serial.print(", ");
    Serial.print(y);
    Serial.print(", ");
    Serial.print(z);
    Serial.println("},");
    
    }
   
    
  }
  Serial.println("End of sphere");
  Serial.println(" ");
}
//converts latitude and longitude to cartesian coordinates
void globe(){
  int x, y, z;
  int radius = 64;
 
  for (int i = 0; i < globe_cnt; i++){
    
    x = radius * cos (globe_vertices[i][0]*PI/180) * cos(globe_vertices[i][1]*PI/180);
    y = radius * cos (globe_vertices[i][0]*PI/180) * sin(globe_vertices[i][1]*PI/180);
    z = radius * sin (globe_vertices[i][0]*PI/180);
    Serial.print("{");
    Serial.print(x);
    Serial.print(", ");
    Serial.print(y);
    Serial.print(", ");
    Serial.print(z);
    Serial.println("},");
    
    }
    Serial.println("End of globe");
  Serial.println(" ");
  }
  
