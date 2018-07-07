/* main.c */
#include"gba.h"

/* フレーム0,1の先頭アドレスをマクロ宣言 */
#define FRAME_0 (u8 *)0x06000000
#define FRAME_1 (u8 *)0x0600A000

/* 更新フレーム */
u8 *screen;

void SwitchFrame(){
  /* 描画フレームの切り替え */
  REG_DISPCNT^=BACKBUFFER;
  /* 更新フレームの切り替え */
  screen=(REG_DISPCNT&BACKBUFFER)?FRAME_0:FRAME_1;
}

void WaitForVsync(){
  while(REG_VCOUNT>=160);
  while(REG_VCOUNT<160);
  /* 垂直同期と一緒にフレームを切り替える */
  SwitchFrame();
}

void PaletteInit(){
  /* 256色使えるカラーパレットを、        */
  /* 赤、青、黄、白のグラデーションに設定 */
  for(u32 i=0;i<32;i++){
    BG_PALETTE[i]=RGB5(31,31-i,31-i);
  }
  for(u32 i=0;i<32;i++){
    BG_PALETTE[32+i]=RGB5(31-i,i,0);
  }
  for(u32 i=0;i<32;i++){
    BG_PALETTE[64+i]=RGB5(0,31,i);
  }
  for(u32 i=0;i<32;i++){
    BG_PALETTE[96+i]=RGB5(0,31-i,31);
  }
  for(u32 i=0;i<32;i++){
    BG_PALETTE[128+i]=RGB5(i,0,31);
  }
  for(u32 i=0;i<32;i++){
    BG_PALETTE[160+i]=RGB5(31,0,31-i);
  }
  for(u32 i=0;i<32;i++){
    BG_PALETTE[192+i]=RGB5(31,i,0);
  }
  for(u32 i=0;i<32;i++){
    BG_PALETTE[224+i]=RGB5(31,31,i);
  }
}

void Init(){
  SetMode(MODE_4|BG2_ENABLE);
  /* フレーム0を描画フレームに設定 */
  screen=FRAME_0;
  /* カラーパレットを初期化 */
  PaletteInit();
}

/* line行目をBG_PALETTE[index]の色で埋める */
void PutLine(u32 line,u8 index){
  /* ベクトル化して一度に8ドット代入できるようにする */
  /* (ある程度最適化しないとFPSが確保できない)       */
  u32 vector=index|index<<8|index<<16|index<<24;
  u32 *s=(u32*)(screen+line*SCREEN_WIDTH);
  for(u32 i=0;i<60;i++){
    s[i]=vector;
  }
}

void Draw(){
  static u32 i=0;
  for(u32 j=0;j<160;j++){
    /* 1行ごとにパレット番号を変える */
    PutLine(j,(i+j)&0xff);
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
