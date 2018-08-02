/* input.c */

#include<gba.h>
#include"input.h"

u16 PreviousInput; /* 前回のキー入力 */
u16 CurrentInput;  /* 今回のキー入力 */

/**
 * @brief キー入力を更新する
 * 必ず毎ループの最初で呼び出す
 */
void UpdateKeyInput(){
  /* 前回のキー入力を更新 */
  PreviousInput=CurrentInput;

  /* 今回のキー入力を更新 */
  CurrentInput=REG_KEYINPUT;
}

/**
 * @brief 指定したキーのステートを返す
 * @input[in] key   状態を確認したいキー
 * @return keyState keyのキーステート
 */
KEYSTATE GetKeyState(KEYPAD_BITS key){
  u16 pre=IS_PRESSED(PreviousInput,key);
  u16 cur=IS_PRESSED(CurrentInput,key);
  KEYSTATE keyState;
  if(pre){
    if(cur){
      keyState=REPEAT;
    }
    else{
      keyState=RELEASED;
    }
  }
  else{
    if(cur){
      keyState=PRESSED;
    }
    else{
      keyState=NOT_PUSHED;
    }
  }
  return keyState;
}

/**
 * @brief 指定したキーを押していないか
 * @input[in] key 状態を確認したいキー
 */
u32 IsKeyNotPushed(KEYPAD_BITS key){
  return GetKeyState(key)==NOT_PUSHED;
}

/**
 * @brief 指定したキーを押したか
 * @input[in] key 状態を確認したいキー
 */
u32 IsKeyPressed(KEYPAD_BITS key){
  return GetKeyState(key)==PRESSED;
}

/**
 * @brief 指定したキーを放したか
 * @input[in] key 状態を確認したいキー
 */
u32 IsKeyReleased(KEYPAD_BITS key){
  return GetKeyState(key)==RELEASED;
}

/**
 * @brief 指定したキーを押しているか
 * @input[in] key 状態を確認したいキー
 */
u32 IsKeyRepeat(KEYPAD_BITS key){
  return GetKeyState(key)==REPEAT;
}

/**
 * @brief 十字キーの方向を返す
 * @return dir 現在入力されている方向
 */
DIRECTION GetDirection(){
  DIRECTION dir;
  switch(IS_PRESSED(CurrentInput,DPAD)){
  case KEY_UP             : dir=DIR_N;   break;
  case KEY_UP|KEY_LEFT    : dir=DIR_NW;  break;
  case KEY_LEFT           : dir=DIR_W;   break;
  case KEY_DOWN|KEY_LEFT  : dir=DIR_SW;  break;
  case KEY_DOWN           : dir=DIR_S;   break;
  case KEY_DOWN|KEY_RIGHT : dir=DIR_SE;  break;
  case KEY_RIGHT          : dir=DIR_E;   break;
  case KEY_UP|KEY_RIGHT   : dir=DIR_NE;  break;
  default                 : dir=NEUTRAL; break;
  }
  return dir;
}
