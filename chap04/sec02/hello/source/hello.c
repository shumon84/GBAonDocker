/* hello.c */
#include"gba.h"

typedef struct{
  u32 x;
  u32 y;
  u16 col;
}Pixel;

void PrintPixel(Pixel pixel){
  static u16 *screen=(u16 *)VRAM;
  screen[pixel.x+pixel.y*SCREEN_WIDTH]=pixel.col;
}

int main(){
  Pixel pixels[3]=
    {
     {120,80,RGB5(31,0,0)},
     {136,80,RGB5(0,31,0)},
     {120,96,RGB5(0,0,31)},
    };

  SetMode(MODE_3|BG2_ENABLE);

  for(int i=0;i<3;i++){
    PrintPixel(pixels[i]);
  }

  while(1);
}
