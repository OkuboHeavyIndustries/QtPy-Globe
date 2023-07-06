//6th July 2023
//UnoR4/QtPy ESP32 S2 Globe by Okubo Heavy Industries based on
//3D_Cube for Arduino OLED module by Colin Ord, 9/1/2015

#include <U8g2lib.h>
#include "big_globe_coords.h"


//The following line will need changing depending on your board type!
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R3, /* reset=*/ U8X8_PIN_NONE);

float tx, nx, p;
float ty, ny, py;
float rot, rotx, roty, rotz, rotxx, rotyy, rotzz, rotxxx, rotyyy, rotzzz;
int i; //0 to 360
int fl, scale; //focal length
int wireframe[600][3];
float vector;

int yangle;
int zangle;
float yrot;
float zrot;
int w;

float scalefactor = 0;

int originx = 32;
int originy = 64; //32

int fd = 0; //0=orthographic

void setup(void)
{
 u8g2.begin();

 u8g2.firstPage();
 do {
 } while ( u8g2.nextPage() );
}

void loop(void)
{
//picture loop

 yangle = 270;//270 Can't quite get my head round why these numbers work but they do!
 zangle = 90;//90
 
 for (int angle = 0; angle <= 2080; angle = angle + 1) { //rotate globe 2080˚
  u8g2.firstPage();
  do {
   for (int i = 0; i < globe_cnt; i++) {

     
     rot = angle * 0.0174532; //0.0174532 = one degree
     yrot = yangle * 0.0174532; //0.0174532 = one degree
     zrot = zangle * 0.0174532; //0.0174532 = one degree
     
//rotateY
    rotz = globe_vertices[i][2] * cos(yrot) - globe_vertices[i][0] * sin(yrot);
    rotx = globe_vertices[i][2] * sin(yrot) + globe_vertices[i][0] * cos(yrot);
    roty = globe_vertices[i][1];
//rotateX
    rotyy = roty * cos(rot) - rotz * sin(rot);
    rotzz = roty * sin(rot) + rotz * cos(rot);
    rotxx = rotx;
//rotateZ
    rotxxx = rotxx * cos(zrot) - rotyy * sin(zrot);
    rotyyy = rotxx * sin(zrot) + rotyy * cos(zrot);
    rotzzz = rotzz;

//orthographic projection
    rotxxx = rotxxx * scalefactor + originx;
    rotyyy = rotyyy * scalefactor + originy;

//store new vertices values for wireframe drawing
    wireframe[i][0] = rotxxx;
    wireframe[i][1] = rotyyy;
    wireframe[i][2] = rotzzz;

     draw_vertices();
     
   }
    
    draw_wireframe();
  if (scalefactor < 0.4) scalefactor = scalefactor + 0.005;
   } while (u8g2.nextPage());
 }
 scalefactor = 0;
  clearOLED();
  delay(2000);
  u8g2.clearBuffer();
    u8g2.setDrawColor(1);
    u8g2.drawBox(0,0,64,128);
    u8g2.sendBuffer();
    delay(100);
    u8g2.setDrawColor(0);
    u8g2.clearBuffer();
    u8g2.drawBox(0,0,64,128);
    u8g2.sendBuffer();
    delay(500);
    //cursor flash
    for (int i = 0; i < 3; i++) {
    
    u8g2.setDrawColor(1);
    u8g2.clearBuffer();
    u8g2.drawBox(1,1,3,5);
    u8g2.sendBuffer();
    delay(300);
    
    u8g2.clearBuffer();
    u8g2.setDrawColor(0);
    u8g2.drawBox(1,1,3,5);
    u8g2.sendBuffer();
    delay(300);
    }
   
    u8g2.setDrawColor(1);
    u8g2.clearBuffer();
}

void clearOLED(){
    u8g2.firstPage();  
    do {
    } while( u8g2.nextPage() );

}


void draw_vertices(void)
{
  if (rotzzz > 0){ //only draw the vertices if they are on the side of the Earth facing the screen
 u8g2.drawPixel (rotxxx, rotyyy);
  }
}

void draw_wireframe(void)
{

 for (w = 0; w < 4; w++){
  if (wireframe[w][2]>0){ //only draw the lines if they are on the side of the Earth facing the screen
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[4][2]>0){
 u8g2.drawLine(wireframe[4][0], wireframe[4][1], wireframe[0][0], wireframe[0][1]);//Greenland
 }

 for (w = 5; w < 8; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 
 if (wireframe[8][2]>0){
 u8g2.drawLine(wireframe[8][0], wireframe[8][1], wireframe[5][0], wireframe[5][1]);//Iceland
 }

 for (w = 9; w < 14; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[14][2]>0){
 u8g2.drawLine(wireframe[14][0], wireframe[14][1], wireframe[9][0], wireframe[9][1]);//Ireland
 }

 for (w = 15; w < 32; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[32][2]>0){
 u8g2.drawLine(wireframe[32][0], wireframe[32][1], wireframe[15][0], wireframe[15][1]);//Britain
 }

 for (w = 33; w < 97; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[97][2]>0){
 u8g2.drawLine(wireframe[97][0], wireframe[97][1], wireframe[99][0], wireframe[99][1]);//Europe, Asia, Africa
 }

  
 for (w = 99; w < 131; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[132][2]>0){
 u8g2.drawLine(wireframe[131][0], wireframe[131][1], wireframe[33][0], wireframe[33][1]);//Europe, Asia, Africa
 }

 for (w = 132; w < 242; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[242][2]>0){
 u8g2.drawLine(wireframe[242][0], wireframe[242][1], wireframe[132][0], wireframe[132][1]);//Americas
}

 for (w = 243; w < 247; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[247][2]>0){
 u8g2.drawLine(wireframe[247][0], wireframe[247][1], wireframe[243][0], wireframe[243][1]);//Madagascar
 }

 for (w = 248; w < 268; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[268][2]>0){
 u8g2.drawLine(wireframe[268][0], wireframe[268][1], wireframe[248][0], wireframe[248][1]);//Australia
 }

 for (w = 269; w < 271; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[271][2]>0){
 u8g2.drawLine(wireframe[271][0], wireframe[271][1], wireframe[269][0], wireframe[269][1]);//New Zealand North
 }

 for (w = 272; w < 276; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[276][2]>0){
 u8g2.drawLine(wireframe[276][0], wireframe[276][1], wireframe[272][0], wireframe[272][1]);//New Zealand South 
 }

 for (w = 277; w < 284; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[284][2]>0){
 u8g2.drawLine(wireframe[284][0], wireframe[284][1], wireframe[277][0], wireframe[277][1]);//Japan Hokkaido
 }

 for (w = 285; w < 295; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[295][2]>0){
 u8g2.drawLine(wireframe[295][0], wireframe[295][1], wireframe[285][0], wireframe[285][1]);//Japan Honshu
 }

 for (w = 296; w < 300; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[300][2]>0){
 u8g2.drawLine(wireframe[300][0], wireframe[300][1], wireframe[296][0], wireframe[296][1]);//Sahkalin
 }

 for (w = 301; w < 304; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[304][2]>0){
 u8g2.drawLine(wireframe[304][0], wireframe[304][1], wireframe[301][0], wireframe[301][1]);//Taiwan
 }

 for (w = 305; w < 308; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[308][2]>0){
 u8g2.drawLine(wireframe[308][0], wireframe[308][1], wireframe[305][0], wireframe[305][1]);//Phillipines
 }

 for (w = 309; w < 311; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[311][2]>0){
 u8g2.drawLine(wireframe[311][0], wireframe[311][1], wireframe[309][0], wireframe[309][1]);//Phillipines South
 }

 for (w = 312; w < 320; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[320][2]>0){
 u8g2.drawLine(wireframe[320][0], wireframe[320][1], wireframe[312][0], wireframe[312][1]);//Borneo
 }

 for (w = 321; w < 324; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[324][2]>0){
 u8g2.drawLine(wireframe[324][0], wireframe[324][1], wireframe[321][0], wireframe[321][1]);//Indonesia
 }

  for (w = 325; w < 327; w++){
    if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
    }
 }
 if (wireframe[327][2]>0){
 u8g2.drawLine(wireframe[327][0], wireframe[327][1], wireframe[325][0], wireframe[325][1]);//Indonesia - South
 }

 for (w = 328; w < 334; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[334][2]>0){
 u8g2.drawLine(wireframe[334][0], wireframe[334][1], wireframe[328][0], wireframe[328][1]);//Papua New Guinea
 }

 for (w = 335; w < 337; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[337][2]>0){
 u8g2.drawLine(wireframe[337][0], wireframe[337][1], wireframe[335][0], wireframe[335][1]);//Sri Lanka
 }

 for (w = 338; w < 344; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[344][2]>0){
 u8g2.drawLine(wireframe[344][0], wireframe[344][1], wireframe[338][0], wireframe[338][1]);//Cuba
 }

 for (w = 345; w < 348; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[348][2]>0){
 u8g2.drawLine(wireframe[348][0], wireframe[348][1], wireframe[345][0], wireframe[345][1]);//Dominica
 }

 for (w = 349; w < 366; w++){
  if (wireframe[w][2]>0){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
  }
 }
 if (wireframe[366][2]>0){
 u8g2.drawLine(wireframe[366][0], wireframe[366][1], wireframe[349][0], wireframe[349][1]);//Antarctica
 }

 

 u8g2.drawCircle(originx,originy,64*scalefactor);
    u8g2.setFont(u8g2_font_u8glib_4_tr);
    u8g2.drawFrame(0, 0, 64,128);  //setup fixed screen info and borders
    u8g2.drawLine(0, 9, 64,9);
    u8g2.drawStr(3, 7, "PLANET EARTH");
    
    u8g2.drawLine(0, 108, 64,108);
    u8g2.drawStr(6, 116, "OKUBO HEAVY");
    u8g2.drawStr(10, 124, "INDUSTRIES");
  
} 
