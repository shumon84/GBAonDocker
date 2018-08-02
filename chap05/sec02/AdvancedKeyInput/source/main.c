/* main.c */

#include "gba.h"
#include "BG0Map.h"
#include "BackGround.h"
#include "input.h"

void WaitForVsync(){
  while(REG_VCOUNT>=160);
  while(REG_VCOUNT<160);
}

void Init(){
  u32 charBase=1;
  u32 screenBase=0;

  SetMode(MODE_0|BG0_ON);
  REG_BG0CNT=
    BG_PRIORITY(0)|
    CHAR_BASE(charBase)|
    BG_256_COLOR|
    SCREEN_BASE(screenBase)|
    TEXTBG_SIZE_512x256;

  vu16* oam=CHAR_BASE_BLOCK(charBase);     /* キャラクタデータ */
  vu16* pal=BG_COLORS;                     /* パレットデータ */
  vu16* map=SCREEN_BASE_BLOCK(screenBase); /* マップデータ */

  /* キャラクタデータの読み込み */
  for(u32 i=0;i<BackGroundTilesLen/2;i++){
    oam[i]=BackGroundTiles[i];
  }

  /* パレットデータの読み込み */
  for(u32 i=0;i<256;i++){
    pal[i]=BackGroundPal[i];
  }

  /* マップデータの読み込み */
  for(u32 i=0;i<BG0MapLen/2;i++){
    map[i]=BG0Map[i];
  }
}

int main(void){
  Init();
  u32 x=0;
  u32 y=0;
  u32 lock=0;
  while(1){
    UpdateKeyInput();

    /* lockをかける/解除する */
    if(IsKeyReleased(KEY_A)) lock=!lock;
    /* 初期位置に戻す */
    if(IsKeyReleased(KEY_B)) x=y=0;

    /* lockを無視して左右に移動 */
    if(IsKeyRepeat(KEY_R)) x++;
    if(IsKeyRepeat(KEY_L)) x--;

    if(lock){
      /* lockがかかってないとき */
      switch(GetDirection()){
      case DIR_N:
        y--;
        break;
      case DIR_NE:
        y--;
        x++;
        break;
      case DIR_E:
        x++;
        break;
      case DIR_SE:
        x++;
        y++;
        break;
      case DIR_S:
        y++;
        break;
      case DIR_SW:
        x--;
        y++;
        break;
      case DIR_W:
        x--;
        break;
      case DIR_NW:
        x--;
        y--;
        break;
      }
    }

    REG_BG0HOFS=x;
    REG_BG0VOFS=y;
    WaitForVsync();
  }
}
