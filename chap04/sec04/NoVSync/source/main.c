/* main.c */

#include"gba.h"

void PrintLine(u32 i, u16 col){
  static u16 *screen=(u16 *)VRAM;
  for(u32 j=0;j<160;j++)
    screen[i+j*SCREEN_WIDTH]=col;
}

int main(){
  u32 i=0;
  SetMode(MODE_3|BG2_ENABLE);
  while(1){
    i%=240;
    PrintLine(i++,0x0000);
    PrintLine(i,0x001f);
  }
}
