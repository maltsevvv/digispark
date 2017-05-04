//    Команда 0xВАШ КОД
#define UP   0x9F600707
#define DOWN 0x9E610707
#define LEFT 0x9A650707
#define RIGHT 0x9D620707
#define ENTER 0x97680707
#define BACK 0xA7580707
#define EXIT 0x
#define HOME 0x
#define PLAY 0xB8470707
#define PAUSE 0xB54A0707
#define STOP 0xB9460707
#define VOLUME_UP 0xF8070707
#define VOLUME_DOWN 0x
#define MUTE 0x
#define INFO 0x
#define CONTEXT_MENU 0x
#define SPEED_FORWARD 0x
#define SPEED_REWIND 0x
#define PAGE_UP 0x
#define PAGE_DOWN 0x
#define WATCHED_UNWATCHED 0xE9160707
#define LIVETV 0x936C0707
#define EPG 0x
#define KEY_1 0x
#define KEY_2 0x
#define KEY_3 0x
#define KEY_4 0x
#define KEY_5 0x
#define KEY_6 0x
#define KEY_7 0x
#define KEY_8 0x
#define KEY_9 0x
#define KEY_0 0x
#define POWER 0x

volatile uint8_t m=0, complete=0,tcnt=0, startflag=0;
uint32_t irdata=0,keydata=0 ;
#include <avr/delay.h>
#include "TrinketHidCombo.h"
void setup() {
DDRB|=(1<<DDB1);
PORTB|=1<<PB2; 
GIMSK|=1<<INT0;
MCUCR|= 1<<ISC00;
GTCCR|=1<<PSR0; TCCR0A=0;
TCCR0B= (1<<CS02)|(1<<CS00);
TIMSK=1<<TOIE0;
TrinketHidCombo.begin();
}
void loop() {
  if (complete) {

/* Снятие кодов конопок с пульта ДУ. В строке ниже СНЯТЬ РЕМАРКУ (//) */
//  TrinketHidCombo.println(keydata,HEX); /*снять ремарку, что бы печатать код клавиш в блокнот*/

/* 
 * Загрузить скетч в Digispark, открыть блокнот и нажимать кнопки, полученный код вставить в #define КНОПКА 0хВАШ КОД.
if (keydata==UP) ... - активна. Для деактивации кнопки ПОСТАВИТЬ РЕМАРКУ
//if (keydata==EXIT) ... -не активна. Для активации кнопки СНЯТЬ РЕМАРКУ
 * Если в #define КНОПКА 0хВАШ КОД остались кнопки, которые вы не используете, то в строке if (keydata==...) напротив неиспользуемой кнопки ПОСТАВИТЬ РЕМАРКУ, иначе будет ошибка.
*/ 

if (keydata==UP) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_UP); TrinketHidCombo.pressKey(0, 0);
if (keydata==DOWN) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_DOWN); TrinketHidCombo.pressKey(0, 0);
if (keydata==LEFT) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_LEFT); TrinketHidCombo.pressKey(0, 0);
if (keydata==RIGHT) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_RIGHT); TrinketHidCombo.pressKey(0, 0);
if (keydata==ENTER) TrinketHidCombo.pressKey(0, KEYCODE_ENTER); TrinketHidCombo.pressKey(0, 0);
if (keydata==PLAY) TrinketHidCombo.pressKey(0, KEYCODE_P);TrinketHidCombo.pressKey(0, 0);
if (keydata==PAUSE) TrinketHidCombo.pressKey(0, KEYCODE_SPACE);TrinketHidCombo.pressKey(0, 0);
if (keydata==STOP) TrinketHidCombo.pressKey(0, KEYCODE_X); TrinketHidCombo.pressKey(0, 0);
if (keydata==VOLUME_UP) TrinketHidCombo.pressKey(0, KEYCODE_EQUAL); TrinketHidCombo.pressKey(0, 0);
//if (keydata==VOLUME_DOWN) /*volume-*/ TrinketHidCombo.pressKey(0, KEYCODE_MINUS); TrinketHidCombo.pressKey(0, 0);
//if (keydata==MUTE) /*mute*/ TrinketHidCombo.pressKey(0, KEYCODE_F8); TrinketHidCombo.pressKey(0, 0);
if (keydata==BACK) TrinketHidCombo.pressKey(0, KEYCODE_BACKSPACE); TrinketHidCombo.pressKey(0, 0);
//if (keydata==EXIT) TrinketHidCombo.pressKey(0, KEYCODE_ESC); TrinketHidCombo.pressKey(0, 0);
//if (keydata==HOME) TrinketHidCombo.pressKey(0, KEYCODE_HOME); TrinketHidCombo.pressKey(0, 0);
//if (keydata==CONTEXT MENU) TrinketHidCombo.pressKey(0, KEYCODE_C); TrinketHidCombo.pressKey(0, 0);
//if (keydata==INFO) TrinketHidCombo.pressKey(0, KEYCODE_I); TrinketHidCombo.pressKey(0, 0);
//if (keydata==SPEED_FORWARD) TrinketHidCombo.pressKey(0, KEYCODE_F); TrinketHidCombo.pressKey(0, 0);
//if (keydata==SPEED_REWIND) TrinketHidCombo.pressKey(0, KEYCODE_R); TrinketHidCombo.pressKey(0, 0);
//if (keydata==PAGE_UP) TrinketHidCombo.pressKey(0, KEYCODE_PAGE_UP); TrinketHidCombo.pressKey(0, 0);
//if (keydata==PAGE_DOWN) TrinketHidCombo.pressKey(0, KEYCODE_PAGE_DOWN); TrinketHidCombo.pressKey(0, 0);
if (keydata==LIVETV) TrinketHidCombo.pressKey(0, KEYCODE_H); TrinketHidCombo.pressKey(0, 0);
//if (keydata==SUBTITLES) TrinketHidCombo.pressKey(0, KEYCODE_T); TrinketHidCombo.pressKey(0, 0);
if (keydata==WATCHED_UNWATCHED) TrinketHidCombo.pressKey(0, KEYCODE_W); TrinketHidCombo.pressKey(0, 0);
//if (keydata==EPG) TrinketHidCombo.pressKey(0, KEYCODE_E); TrinketHidCombo.pressKey(0, 0);
//if (keydata==KEY_1) TrinketHidCombo.pressKey(0, KEYCODE_1); TrinketHidCombo.pressKey(0, 0);
//if (keydata==KEY_2) TrinketHidCombo.pressKey(0, KEYCODE_2); TrinketHidCombo.pressKey(0, 0);
//if (keydata==KEY_3) TrinketHidCombo.pressKey(0, KEYCODE_3); TrinketHidCombo.pressKey(0, 0);
//if (keydata==KEY_4) TrinketHidCombo.pressKey(0, KEYCODE_4); TrinketHidCombo.pressKey(0, 0);
//if (keydata==KEY_5) TrinketHidCombo.pressKey(0, KEYCODE_5); TrinketHidCombo.pressKey(0, 0);
//if (keydata==KEY_6) TrinketHidCombo.pressKey(0, KEYCODE_6); TrinketHidCombo.pressKey(0, 0);
//if (keydata==KEY_7) TrinketHidCombo.pressKey(0, KEYCODE_7); TrinketHidCombo.pressKey(0, 0);
//if (keydata==KEY_8) TrinketHidCombo.pressKey(0, KEYCODE_8); TrinketHidCombo.pressKey(0, 0);
//if (keydata==KEY_9) TrinketHidCombo.pressKey(0, KEYCODE_9); TrinketHidCombo.pressKey(0, 0);
//if (keydata==KEY_0) TrinketHidCombo.pressKey(0, KEYCODE_0); TrinketHidCombo.pressKey(0, 0);
//if (keydata==POWER) TrinketHidCombo.pressSystemCtrlKey(SYSCTRLKEY_POWER); TrinketHidCombo.pressKey(0, 0);

PORTB |= (1<<1);
ms_delay(30);
PORTB &= ~(1<<1);
complete=0;
 }
  _delay_ms(1);
  TrinketHidCombo.poll();
}
ISR (INT0_vect){
  if (PINB& 1<<2) {
      TCNT0=0;
      }
  else { tcnt=TCNT0;
          if (startflag){ if (30 > tcnt  && tcnt >2) {if (tcnt > 15&&m<32) {irdata|=((uint32_t)1<<m);} 
          m++;
          } } 
          else  startflag=1; 
        }
 }  
ISR (TIMER0_OVF_vect) {
if (m) {complete=1; m=0; startflag=0; keydata=irdata; irdata=0; // если индекс не 0, то создать флаг конца
  } 
}
void ms_delay(uint16_t x){
for (uint16_t m=0; m< (x/10); m++){ _delay_ms(10); TrinketHidCombo.poll(); }
}
