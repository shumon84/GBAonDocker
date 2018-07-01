/* main.cb */

#include"gba.h"
#include"gradation.h"

void PrintImage(const u16 *image,const u32 length){
  static u16 *screen=(u16 *)VRAM;
  for(u32 i=0;i<length;i++){
    screen[i]=image[i];
  }
}

int main(){
  SetMode(MODE_3|BG2_ENABLE);
  PrintImage(gradationBitmap,gradationBitmapLen/2);
  while(1);
}
