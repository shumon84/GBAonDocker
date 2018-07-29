/* main.c */
#include"gba.h"

/* 更新フレーム */
MODE5_LINE *screen;

void SwitchFrame(){
  /* 描画フレームの切り替え */
  REG_DISPCNT^=BACKBUFFER;
  /* 更新フレームの切り替え */
  screen=(REG_DISPCNT&BACKBUFFER)?MODE5_FB:MODE5_BB;
}

void WaitForVsync(){
  while(REG_VCOUNT>=160);
  while(REG_VCOUNT<160);
  /* 垂直同期と一緒にフレームを切り替える */
  SwitchFrame();
}

void Init(){
  SetMode(MODE_5|BG2_ENABLE);
  /* フレーム0を描画フレームに設定 */
  screen=MODE5_FB;
}

/* line行目をcolで埋める */
void PutLine(u32 line,u16 col){
  u32 vector=col|col<<16;
  u32 *s=(u32*)(screen[line]);
  for(u32 i=0;i<80;i++){
    s[i]=vector;
  }
}

void Draw(){
  static u32 i=0;
  for(u32 j=0;j<128;j++){
    PutLine(j,RGB5(i&0x1f,j&0x1f,0));
  }
  i++;
}

int main(){
  Init();
  while(1){
    Draw();
    WaitForVsync();
  }
}
