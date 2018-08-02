/* sprite.h */

#ifndef SPRITE_H
#define SPRITE_H

#include"gba.h"

/* オブジェクト番号numのスプライトを指すポインタ */
#define SP(num) ((volatile Sprite*)(OAM+num))

enum SPRITE_SIZE{
  Size_8,
  Size_16,
  Size_32,
  Size_64,
};

enum COLOR_MODE{
  Color_16x16,
  Color_256x1,
};

typedef struct SPRITE{
  /* Attribute 0 */
  u16 Y:8;                      // Y座標
  u16 RotationScaling:1;        // 回転/拡縮フラグ
  u16 DoubleSize:1;             // ダブルサイズフラグ
  u16 Mode:2;                   // オブジェクトモード
  u16 Mosaic:1;                 // モザイクフラグ
  u16 ColorMode:1;              // カラーモード
  u16 Shape:2;                  // オブジェクト形状
  /* Attribute 1 */
  u16 X:9;                      // X座標
  u16 NotUsed:3;                // 不使用
  u16 HFlip:1;                  // 水平方向反転フラグ
  u16 VFlip:1;                  // 垂直方向反転フラグ
  u16 Size:2;                   // オブジェクトサイズ
  /* Attribute 2 */
  u16 Character:10;             // キャラクタ番号
  u16 Priority:2;               // 表示優先度
  u16 Palette:4;                // パレット番号
  /* Attribute 3 */
  u16 dummy;                    // 不使用
} ALIGN(4) Sprite;

void SpriteInit();
void SpriteSetCoordinate(u32 num,u32 x,u32 y);
void SpriteSetShape(u32 num,enum SPRITE_SHAPES shape);
void SpriteSetSize(u32 num,enum SPRITE_SIZE size);
void SpriteSetForm(u32 num,enum SPRITE_SIZECODE form);
void SpriteSetCharacter(u32 num,u32 character);
void SpriteSetPalette(u32 num,s32 palette);
u32 SpriteSetUp(u32 character,s32 palette,enum SPRITE_SIZECODE form,u32 x,u32 y);
void SpriteMove(u32 num,s32 dx,s32 dy);
void SpriteHFlip(u32 num);
void SpriteVFlip(u32 num);
u32 SpriteGetWidth(u32 num);
u32 SpriteGetHeight(u32 num);
u32 SpriteIsVisibleX(u32 num);
u32 SpriteIsVisibleY(u32 num);
u32 SpriteIsVisible(u32 num);

#endif
