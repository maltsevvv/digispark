//#############################
//IR--command----------codes---
#define UP           0x11111111
#define DOWN         0xBE41FB04
#define LEFT         0xF807FB04
#define RIGHT        0xF906FB04
#define ENTER        0x97680707
#define EXIT         0xA45BFB04
#define BACK         0xA7580707
#define PLAY         0x4FB0FB04
#define PAUSE        0x45BAFB04
#define STOP         0x4EB1FB04
#define VOLUME_UP    0xFD02FB04
#define VOLUME_DOWN  0xFC03FB04
#define MUTE         0xBB44FB04
#define INFO         0xD728FB04
#define CONTEXT_MENU 0xBC43FB04
#define PAGE_UP      0xFF00FB04
#define PAGE_DOWN    0xFE01FB04
#define SUBTITLES    0xFE010707
#define TV           0x12345678
#define EPG          0xF10EFB04
#define POWER        0xF708FB04
#define KEY_1        0xDC23F608
#define KEY_2        0xED12FB04
#define KEY_3        0xD827F609
#define KEY_4        0xEB14FB04
#define KEY_5        0xEA15FB04
#define KEY_6        0xE916FB04
#define KEY_7        0xE817FB04
#define KEY_8        0xE718FB04
#define KEY_9        0xE619FB04
#define KEY_0        0xEF10FB04
//#############################
//--------------------------
volatile uint8_t m=0, complete=0,tcnt=0, startflag=0;
uint32_t irdata=0,keydata=0 ;
#include <avr/delay.h>
#include "TrinketHidCombo.h"
void setup() {
DDRB|=(1<<DDB1); //P1 (LED) OUT в скетче не использован
PORTB|=1<<PB2; // подтяжка PB2 не помешает.
GIMSK|=1<<INT0;
MCUCR|= 1<<ISC00; //Any logical change on INT0 generates an interrupt request
GTCCR|=1<<PSR0; TCCR0A=0;
TCCR0B= (1<<CS02)|(1<<CS00); // divider /1024 
TIMSK=1<<TOIE0; //interrupt Timer/Counter1 Overflow  enable
TrinketHidCombo.begin(); // start the USB device engine and enumerate
}
void loop() {
  if (complete) {
// ###########################################################################################################
// Для печати кода кнопки в блокноте, удалить ремарку (//) в строке ниже. После записи кодов вернуть ремарку.//
//  TrinketHidCombo.println(keydata,HEX);

//############################################################################################################
if (keydata==UP) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_UP); TrinketHidCombo.pressKey(0, 0);
if (keydata==DOWN) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_DOWN); TrinketHidCombo.pressKey(0, 0);
if (keydata==LEFT) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_LEFT); TrinketHidCombo.pressKey(0, 0);
if (keydata==RIGHT) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_RIGHT); TrinketHidCombo.pressKey(0, 0);
if (keydata==ENTER) TrinketHidCombo.pressKey(0, KEYCODE_ENTER); TrinketHidCombo.pressKey(0, 0);
if (keydata==EXIT) TrinketHidCombo.pressKey(0, KEYCODE_ESC); TrinketHidCombo.pressKey(0, 0);
if (keydata==BACK) TrinketHidCombo.pressKey(0, KEYCODE_BACKSPACE); TrinketHidCombo.pressKey(0, 0);
if (keydata==PLAY) TrinketHidCombo.pressMultimediaKey(MMKEY_PLAYPAUSE);
if (keydata==PAUSE) TrinketHidCombo.pressMultimediaKey(MMKEY_PLAYPAUSE);
if (keydata==STOP) TrinketHidCombo.pressMultimediaKey(MMKEY_STOP);
if (keydata==VOLUME_UP) TrinketHidCombo.pressKey(0, KEYCODE_F10); TrinketHidCombo.pressKey(0, 0);
if (keydata==VOLUME_DOWN) TrinketHidCombo.pressKey(0, KEYCODE_F9); TrinketHidCombo.pressKey(0, 0);
if (keydata==MUTE) TrinketHidCombo.pressKey(0, KEYCODE_F8); TrinketHidCombo.pressKey(0, 0);
if (keydata==INFO) TrinketHidCombo.pressKey(0, KEYCODE_I); TrinketHidCombo.pressKey(0, 0);
if (keydata==CONTEXT_MENU) TrinketHidCombo.pressKey(0, KEYCODE_C); TrinketHidCombo.pressKey(0, 0);
if (keydata==PAGE_UP) TrinketHidCombo.pressKey(0, KEYCODE_PAGE_UP); TrinketHidCombo.pressKey(0, 0);
if (keydata==PAGE_DOWN) TrinketHidCombo.pressKey(0, KEYCODE_PAGE_DOWN); TrinketHidCombo.pressKey(0, 0);
if (keydata==SUBTITLES) TrinketHidCombo.pressKey(0, KEYCODE_L); TrinketHidCombo.pressKey(0, 0);
if (keydata==TV) TrinketHidCombo.pressKey(0, KEYCODE_H); TrinketHidCombo.pressKey(0, 0);
if (keydata==EPG) TrinketHidCombo.pressKey(0, KEYCODE_E); TrinketHidCombo.pressKey(0, 0);
if (keydata==POWER) TrinketHidCombo.pressKey(0, KEYCODE_S); TrinketHidCombo.pressKey(0, 0);
if (keydata==KEY_1) TrinketHidCombo.pressKey(0, KEYCODE_1); TrinketHidCombo.pressKey(0, 0);
if (keydata==KEY_2) TrinketHidCombo.pressKey(0, KEYCODE_2); TrinketHidCombo.pressKey(0, 0);
if (keydata==KEY_3) TrinketHidCombo.pressKey(0, KEYCODE_3); TrinketHidCombo.pressKey(0, 0);
if (keydata==KEY_4) TrinketHidCombo.pressKey(0, KEYCODE_4); TrinketHidCombo.pressKey(0, 0);
if (keydata==KEY_5) TrinketHidCombo.pressKey(0, KEYCODE_5); TrinketHidCombo.pressKey(0, 0);
if (keydata==KEY_6) TrinketHidCombo.pressKey(0, KEYCODE_6); TrinketHidCombo.pressKey(0, 0);
if (keydata==KEY_7) TrinketHidCombo.pressKey(0, KEYCODE_7); TrinketHidCombo.pressKey(0, 0);
if (keydata==KEY_8) TrinketHidCombo.pressKey(0, KEYCODE_8); TrinketHidCombo.pressKey(0, 0);
if (keydata==KEY_9) TrinketHidCombo.pressKey(0, KEYCODE_9); TrinketHidCombo.pressKey(0, 0);
if (keydata==KEY_0) TrinketHidCombo.pressKey(0, KEYCODE_0); TrinketHidCombo.pressKey(0, 0);
//############################################################################################

PORTB |= (1<<1);
ms_delay(200);// во избежание слишком частого повтора ввода клавиш
PORTB &= ~(1<<1);
complete=0;
 }
  _delay_ms(1);//сдерживать поллинг USB на пустых циклах
  TrinketHidCombo.poll(); // check if USB needs anything done
  
}

ISR (INT0_vect){
  if (PINB& 1<<2) {   // Если лог1
      TCNT0=0;
      }
  else { tcnt=TCNT0; // если лог 0
          if (startflag){ if (30 > tcnt  && tcnt >2) {if (tcnt > 15&&m<32) {irdata|=((uint32_t)1<<m);} 
          m++;
          } } 
          else  startflag=1; 
        }
 }  
ISR (TIMER0_OVF_vect) {
 //если сработало это прерывание, значит конец посылки
if (m) {complete=1; m=0; startflag=0; keydata=irdata; irdata=0; // если индекс не 0, то создать флаг конца
  } 
}

void ms_delay(uint16_t x){ // функция задержки с USB поллом
for (uint16_t m=0; m< (x/10); m++){ _delay_ms(10); TrinketHidCombo.poll(); }
}
