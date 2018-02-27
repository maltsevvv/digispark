// Скетч дистанционного управления для DigiSpark и V-USB библиотеки TrinketHidCombo for DigispArk
// ****TSOP подключен к порту PB2****////// 
volatile uint8_t m=0, complete=0,tcnt=0, startflag=0;
uint32_t irdata=0,keydata=0 ;
#include <avr/delay.h>
#include "TrinketHidCombo.h"
void setup() {
DDRB|=(1<<DDB1); //P1 (LED) OUT в скетче не использован
PORTB|=1<<PB2; // подтяжка PB2 не помешает.
GIMSK|=1<<INT0; //interrupt int0 enable
MCUCR|= 1<<ISC00; //Any logical change on INT0 generates an interrupt request
GTCCR|=1<<PSR0; TCCR0A=0;
TCCR0B= (1<<CS02)|(1<<CS00); // divider /1024 
TIMSK=1<<TOIE0;//interrupt Timer/Counter1 Overflow  enable
TrinketHidCombo.begin(); // start the USB device engine and enumerate
}
void loop() {

  if (complete) { // если был принят код
//  TrinketHidCombo.println(keydata,HEX); //снять ремарку, что бы печатать код клавиш. После получения и записи кода вернуть ремарку обратно!  
// Управление KODI (XBMC)
if (keydata==0x10A87EE) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_UP);     TrinketHidCombo.pressKey(0, 0); // (Up)
if (keydata==0x10C87EE) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_DOWN);   TrinketHidCombo.pressKey(0, 0); // (Down)
if (keydata==0x10687EE) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_RIGHT);  TrinketHidCombo.pressKey(0, 0); // (Right)
if (keydata==0x10987EE) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_LEFT);   TrinketHidCombo.pressKey(0, 0); // (Left)
if (keydata==0x15C87EE) TrinketHidCombo.pressKey(0, KEYCODE_ENTER);        TrinketHidCombo.pressKey(0, 0); // (Ok)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_ESC);          TrinketHidCombo.pressKey(0, 0); // (Exit)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_BACKSPACE);    TrinketHidCombo.pressKey(0, 0); // (Back)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_C);            TrinketHidCombo.pressKey(0, 0); // (Contextual menu)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_I);            TrinketHidCombo.pressKey(0, 0); // (Info)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_M);            TrinketHidCombo.pressKey(0, 0); // (Menu)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_HOME);         TrinketHidCombo.pressKey(0, 0); // (Home)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_F8);           TrinketHidCombo.pressKey(0, 0); // (Mute)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_EQUAL);        TrinketHidCombo.pressKey(0, 0); // (Volume up)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_MINUS);        TrinketHidCombo.pressKey(0, 0); // (Volume down)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_PAGE_UP);      TrinketHidCombo.pressKey(0, 0); // (Page up)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_PAGE_DOWN);    TrinketHidCombo.pressKey(0, 0); // (Page down)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_X);            TrinketHidCombo.pressKey(0, 0); // (Stop)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_P);            TrinketHidCombo.pressKey(0, 0); // (Play)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_SPACE);        TrinketHidCombo.pressKey(0, 0); // (Pause)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_E);            TrinketHidCombo.pressKey(0, 0); // (Live TV EPG/TV guide)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_W);            TrinketHidCombo.pressKey(0, 0); // (Marked as watched / unwatched)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_T);            TrinketHidCombo.pressKey(0, 0); // (Toggle subtitles on and off)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_Z);            TrinketHidCombo.pressKey(0, 0); // (Zoom/aspect ratio)
if (keydata==0х12345EE) TrinketHidCombo.pressSystemCtrlKey(SYSCTRLKEY_POWER); // (Power)

ms_delay(200);// во избежание слишком частого повтора ввода клавиш
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
  
