/* sprite.c */

#include"gba.h"
#include"sprite.h"

/**
 * @brief スプライトの初期化
 * 全てのスプライトを画面外に移動させるだけで
 * その他のフラグは初期化されない
 */
void SpriteInit(){
  for(u32 i=0;i<128;i++){
    SpriteSetCoordinate(i,SCREEN_WIDTH,SCREEN_HEIGHT);
  }
}

/**
 * @brief スプライトの座標を設定する
 * @param[in] num オブジェクト番号
 * @param[in] x   X軸の絶対座標
 * @param[in] y   Y軸の絶対座標
 */
void SpriteSetCoordinate(u32 num,u32 x,u32 y){
  SP(num)->X=x;
  SP(num)->Y=y;
}

/**
 * @brief スプライトの形状を設定
 * @param[in] num   オブジェクト番号
 * @param[in] shape 設定する形状
 */
void SpriteSetShape(u32 num,enum SPRITE_SHAPES shape){
  SP(num)->Shape=shape;
}

/**
 * @brief スプライトのサイズを設定
 * @param[in] num  オブジェクト番号
 * @param[in] size 設定するサイズ
 */
void SpriteSetSize(u32 num,enum SPRITE_SIZE size){
  SP(num)->Size=size;
}

/**
 * @brief スプライトのサイズと形状を設定
 * @param[in] num  オブジェクト番号
 * @param[in] form 設定するサイズと形状
 */
void SpriteSetForm(u32 num,enum SPRITE_SIZECODE form){
  SpriteSetShape(num,form>>2);
  SpriteSetSize(num,form&0x03);
}

/**
 * @brief スプライトにキャラクタを設定
 * @param[in] num       オブジェクト番号
 * @param[in] character 設定するキャラクタ番号
 */
void SpriteSetCharacter(u32 num,u32 character){
  SP(num)->Character=character;
}

/**
 * @brief スプライトのカラーパレットを設定
 * @param[in] num     オブジェクト番号
 * @param[in] palette 設定するパレット番号
 * paletteが負のとき、256色/1パレットモードを設定する
 */
void SpriteSetPalette(u32 num,s32 palette){
  if(palette<0){
    /* paletteが負のとき */
    SP(num)->ColorMode=Color_256x1;
  }
  else{
    /* paletteが正のとき */
    SP(num)->ColorMode=Color_16x16;
    SP(num)->Palette=palette;
  }
}

/**
 * @brief オブジェクトをセットアップ
 * @param[in] character 設定するキャラクタ番号
 * @param[in] palette   設定するパレット番号
 * @param[in] form      設定するサイズと形状
 * @param[in] x         設定するX軸の絶対座標
 * @param[in] y         設定するY軸の絶対座標
 * @return セットアップしたオブジェクトのオブジェクト番号
 */
u32 SpriteSetUp(u32 character,s32 palette,enum SPRITE_SIZECODE form,u32 x,u32 y){
  static u32 numOfSprites=0;
  SpriteSetCharacter(numOfSprites,character);
  SpriteSetPalette(numOfSprites,palette);
  SpriteSetForm(numOfSprites,form);
  SpriteSetCoordinate(numOfSprites,x,y);
  return numOfSprites++;
}

/**
 * @brief スプライトを移動させる
 * @param[in] num オブジェクト番号
 * @param[in] dx  X軸の変化量
 * @param[in] dy  Y軸の変化量
 */
void SpriteMove(u32 num,s32 dx,s32 dy){
  SP(num)->X+=dx;
  SP(num)->Y+=dy;
}

/**
 * @brief スプライトを水平方向に反転
 * @param[in] num オブジェクト番号
 */
void SpriteHFlip(u32 num){
  SP(num)->HFlip^=1;            /* HFlipのビットを反転 */
}

/**
 * @brief スプライトを垂直方向に反転
 * @param[in] num オブジェクト番号
 */
void SpriteVFlip(u32 num){
  SP(num)->VFlip^=1;            /* VFlipのビットを反転 */
}

/**
 * @brief スプライトの幅を取得
 * @param[in] num オブジェクト番号
 * @return オブジェクトnumの横幅
 */
u32 SpriteGetWidth(u32 num){
  enum SPRITE_SIZECODE form=SP(num)->Shape<<2|SP(num)->Size;
  u32 width=0;

  switch(form){
    case Sprite_8x8   :
    case Sprite_8x16  :
    case Sprite_8x32  : width=8; break;
    case Sprite_16x8  :
    case Sprite_16x16 :
    case Sprite_16x32 : width=16; break;
    case Sprite_32x8  :
    case Sprite_32x16 :
    case Sprite_32x32 :
    case Sprite_32x64 : width=32; break;
    case Sprite_64x32 :
    case Sprite_64x64 : width=64; break;
  }

  return width;
}

/**
 * @brief スプライトの高さを取得
 * @param[in] num オブジェクト番号
 * @return オブジェクトnumの横幅
 */
u32 SpriteGetHeight(u32 num){
  enum SPRITE_SIZECODE form=SP(num)->Shape<<2|SP(num)->Size;
  u32 height=0;

  switch(form){
    case Sprite_8x8   :
    case Sprite_16x8  :
    case Sprite_32x8  : height=8; break;
    case Sprite_8x16  :
    case Sprite_16x16 :
    case Sprite_32x16 : height=16; break;
    case Sprite_8x32  :
    case Sprite_16x32 :
    case Sprite_32x32 :
    case Sprite_64x32 : height=32; break;
    case Sprite_32x64 :
    case Sprite_64x64 : height=64; break;
  }

  return height;
}

/**
 * @brief X軸方向に画面に写っているか
 * @param[in] num オブジェクト番号
 * @return X軸方向に画面に写っているか
 */
u32 SpriteIsVisibleX(u32 num){
  return SP(num)->X<SCREEN_WIDTH-SpriteGetWidth(num);
}

/**
 * @brief Y軸方向に画面に写っているか
 * @param[in] num オブジェクト番号
 * @return Y軸方向に画面に写っているか
 */
u32 SpriteIsVisibleY(u32 num){
  return SP(num)->Y<SCREEN_HEIGHT-SpriteGetHeight(num);
}

/**
 * @brief 画面に写っているか
 * @param[in] num オブジェクト番号
 * @return 画面に写っているか
 */
u32 SpriteIsVisible(u32 num){
  return SpriteIsVisibleX(num)&&SpriteIsVisibleY(num);
}
