/* main.c */

#include "gba.h"
#include "sprite.h"
#include "spr.h"

void WaitForVsync(){
  while(REG_VCOUNT>=160);
  while(REG_VCOUNT<160);
}

void Init(){
  SetMode(MODE_0|OBJ_ENABLE|OBJ_1D_MAP);

  u16* oam=OBJ_BASE_ADR;        /* キャラクタデータ */
  u16* pal=OBJ_COLORS;          /* パレットデータ */

  /* キャラクタデータの読み込み */
  for(u32 i=0;i<sprTilesLen/2;i++){
    oam[i]=sprTiles[i];
  }

  /* パレットデータの読み込み */
  for(u32 i=0;i<16;i++){
    pal[i]=sprPal[i];
  }

  /* 全てのスプライトを画面外に移動 */
  SpriteInit();
}

void PrintNum(u32 n){
  #define digit 3               /* 表示する桁数 */
  static u32 spr[digit];

  /* 初めてPrintNum()が呼ばれたときの処理 */
  static u32 isInitialized=false;
  if(!isInitialized){
    isInitialized=true;
    u32 x=digit*8;
    /* スプライトの設定 */
    for(u32 i=0;i<digit;i++){
      x-=8;
      spr[i]=SpriteSetUp(0,0,Sprite_8x8,x,0);
    }
  }

  /* スプライトに表示する桁を割り当てる */
  for(u32 i=0;i<digit;i++){
    SpriteSetCharacter(spr[i],n%10);
    n/=10;
  }
  #undef digit
}

int main(void){
  Init();
  /* sprに                      */
  /*   キャラクタ番号 -> 9      */
  /*   パレット番号   -> 0      */
  /*   サイズと形状   -> 16x32  */
  /*   XY座標         -> (0,50) */
  /* を設定する                 */
  u32 spr=SpriteSetUp(9,0,Sprite_16x32,0,50);

  u32 dx=1;
  u32 count=0;
  while(1){
    SpriteMove(spr,dx,0);    /* 左右へ移動 */

    /* sprが画面端に着いたとき */
    if(!SpriteIsVisibleX(spr)){
      dx*=-1;                /* 進行方向を反転 */
      SpriteHFlip(spr);      /* sprを水平方向に反転 */
    }

    /* ループ回数をカウント */
    count++;
    PrintNum(count);

    WaitForVsync();
  }
}
