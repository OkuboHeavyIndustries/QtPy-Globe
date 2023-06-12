//12th June 2023
//QtPy Globe by Okubo Heavy Industries based on
//3D_Cube for Arduino OLED module by Colin Ord, 9/1/2015

#include <U8g2lib.h>
#include "globe_coords.h"
#include "ArduinoLowPower.h"

//The following line will need changing depending on your board type!
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

float tx, nx, p;
float ty, ny, py;
float rot, rotx, roty, rotz, rotxx, rotyy, rotzz, rotxxx, rotyyy, rotzzz;
int i; //0 to 360
int fl, scale; //focal length
int wireframe[200][2];
float vector;

int yangle;
int zangle;
float yrot;
float zrot;
int w;

float scalefactor = 0;

int originx = 64;
int originy = 32; //32

int fd = 0; //0=orthographic

void setup(void)
{
 u8g2.begin();

 u8g2.firstPage();
 do {
 } while ( u8g2.nextPage() );
}

void draw_vertices(void)
{
 u8g2.drawPixel (rotxxx, rotyyy);
}

void draw_wireframe(void)
{
 
 u8g2.drawLine(wireframe[0][0], wireframe[0][1], wireframe[1][0], wireframe[1][1]);
 u8g2.drawLine(wireframe[1][0], wireframe[1][1], wireframe[2][0], wireframe[2][1]);
 u8g2.drawLine(wireframe[2][0], wireframe[2][1], wireframe[3][0], wireframe[3][1]);
 u8g2.drawLine(wireframe[3][0], wireframe[3][1], wireframe[0][0], wireframe[0][1]);//greenland
 u8g2.drawLine(wireframe[4][0], wireframe[4][1], wireframe[5][0], wireframe[5][1]); 
 u8g2.drawLine(wireframe[5][0], wireframe[5][1], wireframe[6][0], wireframe[6][1]); 
 u8g2.drawLine(wireframe[6][0], wireframe[6][1], wireframe[4][0], wireframe[4][1]);//iceland
 u8g2.drawLine(wireframe[7][0], wireframe[7][1], wireframe[8][0], wireframe[8][1]);
 u8g2.drawLine(wireframe[8][0], wireframe[8][1], wireframe[9][0], wireframe[9][1]);
 u8g2.drawLine(wireframe[9][0], wireframe[9][1], wireframe[10][0], wireframe[10][1]);
 u8g2.drawLine(wireframe[10][0], wireframe[10][1], wireframe[11][0], wireframe[11][1]);
 u8g2.drawLine(wireframe[11][0], wireframe[11][1], wireframe[12][0], wireframe[12][1]);
 u8g2.drawLine(wireframe[12][0], wireframe[12][1], wireframe[13][0], wireframe[13][1]);
 u8g2.drawLine(wireframe[13][0], wireframe[13][1], wireframe[14][0], wireframe[14][1]);
 u8g2.drawLine(wireframe[14][0], wireframe[14][1], wireframe[15][0], wireframe[15][1]);
 u8g2.drawLine(wireframe[15][0], wireframe[15][1], wireframe[16][0], wireframe[16][1]);
 u8g2.drawLine(wireframe[16][0], wireframe[16][1], wireframe[17][0], wireframe[17][1]);
 u8g2.drawLine(wireframe[17][0], wireframe[17][1], wireframe[18][0], wireframe[18][1]);
 u8g2.drawLine(wireframe[18][0], wireframe[18][1], wireframe[19][0], wireframe[19][1]);
 u8g2.drawLine(wireframe[19][0], wireframe[19][1], wireframe[20][0], wireframe[20][1]);
 u8g2.drawLine(wireframe[20][0], wireframe[20][1], wireframe[21][0], wireframe[21][1]);
 u8g2.drawLine(wireframe[21][0], wireframe[21][1], wireframe[7][0], wireframe[7][1]);//Britain
 u8g2.drawLine(wireframe[22][0], wireframe[22][1], wireframe[23][0], wireframe[23][1]);
 u8g2.drawLine(wireframe[23][0], wireframe[23][1], wireframe[24][0], wireframe[24][1]);
 u8g2.drawLine(wireframe[24][0], wireframe[24][1], wireframe[25][0], wireframe[25][1]);
 u8g2.drawLine(wireframe[25][0], wireframe[25][1], wireframe[26][0], wireframe[26][1]);
 u8g2.drawLine(wireframe[26][0], wireframe[26][1], wireframe[22][0], wireframe[22][1]);//Ireland

 for (w = 27; w < 84; w++){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
 }
 u8g2.drawLine(wireframe[84][0], wireframe[84][1], wireframe[37][0], wireframe[27][1]);//Europe, Asia, Africa

 for (w = 85; w < 117; w++){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
 }
 u8g2.drawLine(wireframe[117][0], wireframe[117][1], wireframe[85][0], wireframe[85][1]);//Americas

 for (w = 118; w < 125; w++){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
 }
 u8g2.drawLine(wireframe[125][0], wireframe[125][1], wireframe[118][0], wireframe[118][1]);//Australia

 for (w = 126; w < 128; w++){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
 }
 u8g2.drawLine(wireframe[128][0], wireframe[128][1], wireframe[126][0], wireframe[126][1]);//Madagascar

 for (w = 129; w < 133; w++){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
 }
 u8g2.drawLine(wireframe[133][0], wireframe[133][1], wireframe[129][0], wireframe[129][1]);//Japan

 for (w = 134; w < 136; w++){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
 }
 u8g2.drawLine(wireframe[136][0], wireframe[136][1], wireframe[134][0], wireframe[134][1]);//Borneo

 for (w = 137; w < 140; w++){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
 }
 u8g2.drawLine(wireframe[140][0], wireframe[140][1], wireframe[137][0], wireframe[137][1]);//New Zealand

 for (w = 141; w < 152; w++){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
 }
 u8g2.drawLine(wireframe[152][0], wireframe[152][1], wireframe[141][0], wireframe[141][1]);//Antarctica

 for (w = 154; w < 156; w++){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
 }
 u8g2.drawLine(wireframe[156][0], wireframe[156][1], wireframe[154][0], wireframe[154][1]);//Cuba

 for (w = 157; w < 159; w++){
  u8g2.drawLine(wireframe[w][0], wireframe[w][1], wireframe[w+1][0], wireframe[w+1][1]);
 }
 u8g2.drawLine(wireframe[159][0], wireframe[159][1], wireframe[157][0], wireframe[157][1]);//Dominica 

u8g2.drawCircle(64,32,64*scalefactor);

}

void loop(void)
{
//picture loop

 yangle = 270;
 zangle = 90;
 
 for (int angle = 0; angle <= 1080; angle = angle + 3) {
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
  if (scalefactor < 0.5) scalefactor = scalefactor + 0.01;
 // u8g2.drawFrame(28,0,72,64);
   } while (u8g2.nextPage());
 }
 scalefactor = 0;
  clearOLED();
  delay(2000);
  u8g2.clearBuffer();
    u8g2.setDrawColor(1);
    u8g2.drawBox(0,0,128,64);
    u8g2.sendBuffer();
    delay(100);
    u8g2.setDrawColor(0);
    u8g2.clearBuffer();
    u8g2.drawBox(0,0,128,64);
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
