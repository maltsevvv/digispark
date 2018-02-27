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
//  TrinketHidCombo.println(keydata,HEX); //снять ремарку ниже что бы печатать код клавиш    
// ниже пример управления ANDROID TV
if (keydata==0x10A87EE) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_UP);     TrinketHidCombo.pressKey(0, 0); // (up)
if (keydata==0x10C87EE) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_DOWN);   TrinketHidCombo.pressKey(0, 0); // (Down)
if (keydata==0x10987EE) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_LEFT);   TrinketHidCombo.pressKey(0, 0); // (Left)
if (keydata==0x10687EE) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_RIGHT);  TrinketHidCombo.pressKey(0, 0); // (Right)
if (keydata==0x15C87EE) TrinketHidCombo.pressKey(0, KEYCODE_ENTER);        TrinketHidCombo.pressKey(0, 0); // (Ok)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_ESC);          TrinketHidCombo.pressKey(0, 0); // (Exit)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_PAGE_UP);      TrinketHidCombo.pressKey(0, 0); // (Page up)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_PAGE_DOWN);    TrinketHidCombo.pressKey(0, 0); // (Page down)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_F1);           TrinketHidCombo.pressKey(0, 0); //
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_F2);           TrinketHidCombo.pressKey(0, 0); //
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_F3);           TrinketHidCombo.pressKey(0, 0); //
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_F4);           TrinketHidCombo.pressKey(0, 0); //
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_1);            TrinketHidCombo.pressKey(0, 0); // (1)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_2);            TrinketHidCombo.pressKey(0, 0); // (2)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_3);            TrinketHidCombo.pressKey(0, 0); // (3)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_4);            TrinketHidCombo.pressKey(0, 0); // (4)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_5);            TrinketHidCombo.pressKey(0, 0); // (5)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_6);            TrinketHidCombo.pressKey(0, 0); // (6)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_7);            TrinketHidCombo.pressKey(0, 0); // (7)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_8);            TrinketHidCombo.pressKey(0, 0); // (8)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_9);            TrinketHidCombo.pressKey(0, 0); // (9)
if (keydata==0x10387EE) TrinketHidCombo.pressKey(0, KEYCODE_0);            TrinketHidCombo.pressKey(0, 0); // (0)
if (keydata==0x15F87EE) TrinketHidCombo.pressMultimediaKey(MMKEY_PLAYPAUSE);  // (Play)
if (keydata==0x15F87EE) TrinketHidCombo.pressMultimediaKey(MMKEY_PLAYPAUSE);  // (Pause)
if (keydata==0x15F87EE) TrinketHidCombo.pressMultimediaKey(MMKEY_STOP);       // (Stop)
if (keydata==0x15F87EE) TrinketHidCombo.pressMultimediaKey(MMKEY_VOL_UP);     // (Volume up)
if (keydata==0x15F87EE) TrinketHidCombo.pressMultimediaKey(MMKEY_VOL_DOWN);   // (Volume down)
if (keydata==0x12345RR) TrinketHidCombo.pressSystemCtrlKey(SYSCTRLKEY_POWER); // (power)

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
  
