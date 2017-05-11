//--IR--command-----codes---
#define UP        0x9F600707
#define DOWN      0x9E610707
#define LEFT      0x9A650707
#define RIGHT     0x9D620707
#define ENTER     0x97680707
#define EXIT      0x
#define BACK      0xA7580707
#define PLAY      0xB8470707
#define PAUSE     0xB54A0707
#define STOP      0xB9460707
#define VOL_UP    0xF8070707
#define VOL_DOWN  0x
#define INFO      0x
#define C_MENU    0x
#define PAGE_UP   0x
#define PAGE_DOWN 0x
#define WATCH     0xE9160707
#define TV        0x936C0707
#define EPG       0x
#define POWER     0x
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
TIMSK=1<<TOIE0; //interrupt Timer/Counter1 Overflow  enable
TrinketHidCombo.begin(); // start the USB device engine and enumerate
}
void loop() {
  if (complete) {
//--------------------------------------
//  TrinketHidCombo.println(keydata,HEX); /*снять ремарку, что бы печатать код клавиш в блокнот*/
//--------------------------------------
if (keydata==UP) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_UP); TrinketHidCombo.pressKey(0, 0);
if (keydata==DOWN) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_DOWN); TrinketHidCombo.pressKey(0, 0);
if (keydata==LEFT) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_LEFT); TrinketHidCombo.pressKey(0, 0);
if (keydata==RIGHT) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_RIGHT); TrinketHidCombo.pressKey(0, 0);
if (keydata==ENTER) TrinketHidCombo.pressKey(0, KEYCODE_ENTER); TrinketHidCombo.pressKey(0, 0);
//if (keydata==EXIT) TrinketHidCombo.pressKey(0, KEYCODE_ESC); TrinketHidCombo.pressKey(0, 0);
if (keydata==BACK) TrinketHidCombo.pressKey(0, KEYCODE_BACKSPACE); TrinketHidCombo.pressKey(0, 0);
if (keydata==PLAY) TrinketHidCombo.pressMultimediaKey(MMKEY_PLAYPAUSE);
if (keydata==PAUSE) TrinketHidCombo.pressMultimediaKey(MMKEY_PLAYPAUSE);
if (keydata==STOP) TrinketHidCombo.pressMultimediaKey(MMKEY_STOP);
if (keydata==VOL_UP) TrinketHidCombo.pressMultimediaKey(MMKEY_VOL_UP);
//if (keydata==VOL_DOWN) TrinketHidCombo.pressMultimediaKey(MMKEY_VOL_DOWN);
//if (keydata==INFO) TrinketHidCombo.pressKey(0, KEYCODE_I); TrinketHidCombo.pressKey(0, 0);
//if (keydata==C_MENU) TrinketHidCombo.pressKey(0, KEYCODE_C); TrinketHidCombo.pressKey(0, 0);
//if (keydata==PAGE_UP) TrinketHidCombo.pressKey(0, KEYCODE_PAGE_UP); TrinketHidCombo.pressKey(0, 0);
//if (keydata==PAGE_DOWN) TrinketHidCombo.pressKey(0, KEYCODE_PAGE_DOWN); TrinketHidCombo.pressKey(0, 0);
if (keydata==WATCH) TrinketHidCombo.pressKey(0, KEYCODE_W); TrinketHidCombo.pressKey(0, 0);
if (keydata==TV) TrinketHidCombo.pressKey(0, KEYCODE_H); TrinketHidCombo.pressKey(0, 0);
//if (keydata==EPG) TrinketHidCombo.pressKey(0, KEYCODE_E); TrinketHidCombo.pressKey(0, 0);
//if (keydata==POWER) TrinketHidCombo.pressSystemCtrlKey(SYSCTRLKEY_POWER);

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
