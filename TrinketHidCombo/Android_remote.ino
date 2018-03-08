// ANDROID TV
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

if (keydata==0x9F600707) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_UP);     TrinketHidCombo.pressKey(0, 0); // (up)
if (keydata==0x9E610707) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_DOWN);   TrinketHidCombo.pressKey(0, 0); // (Down)
if (keydata==0x9A650707) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_LEFT);   TrinketHidCombo.pressKey(0, 0); // (Left)
if (keydata==0x9D620707) TrinketHidCombo.pressKey(0, KEYCODE_ARROW_RIGHT);  TrinketHidCombo.pressKey(0, 0); // (Right)
if (keydata==0x97680707) TrinketHidCombo.pressKey(0, KEYCODE_ENTER);        TrinketHidCombo.pressKey(0, 0); // (Ok)
if (keydata==0xD22D0707) TrinketHidCombo.pressKey(0, KEYCODE_ESC);          TrinketHidCombo.pressKey(0, 0); // (Exit)
if (keydata==0x936C0707) TrinketHidCombo.pressKey(0, KEYCODE_F1);           TrinketHidCombo.pressKey(0, 0); // (Red)
if (keydata==0xEB140707) TrinketHidCombo.pressKey(0, KEYCODE_F2);           TrinketHidCombo.pressKey(0, 0); // (Green)
if (keydata==0x750A8383) TrinketHidCombo.pressKey(0, KEYCODE_F3);           TrinketHidCombo.pressKey(0, 0); // (Yelow)
if (keydata==0xE9160707) TrinketHidCombo.pressKey(0, KEYCODE_F4);           TrinketHidCombo.pressKey(0, 0); // (Blue)
if (keydata==0x6C930707) TrinketHidCombo.pressKey(0, KEYCODE_F5);           TrinketHidCombo.pressKey(0, 0); // (Apps)
if (keydata==0xA7580707) TrinketHidCombo.pressKey(0, KEYCODE_F10);          TrinketHidCombo.pressKey(0, 0); // (Resize)
if (keydata==0xB8470707) TrinketHidCombo.pressMultimediaKey(MMKEY_PLAYPAUSE);  // (Play)
if (keydata==0xB54A0707) TrinketHidCombo.pressMultimediaKey(MMKEY_PLAYPAUSE);  // (Pause)
if (keydata==0x5CA20707) TrinketHidCombo.pressMultimediaKey(MMKEY_STOP);       // (Stop)
if (keydata==0xF8070707) TrinketHidCombo.pressMultimediaKey(MMKEY_VOL_UP);     // (Volume up)
if (keydata==0xF40B0707) TrinketHidCombo.pressMultimediaKey(MMKEY_VOL_DOWN);   // (Volume down)
if (keydata==0xFD020707) TrinketHidCombo.pressSystemCtrlKey(SYSCTRLKEY_POWER); // (power)
if (keydata==0xFB040707) TrinketHidCombo.pressKey(0, KEYCODE_1);            TrinketHidCombo.pressKey(0, 0); // (1)
if (keydata==0xFA050707) TrinketHidCombo.pressKey(0, KEYCODE_2);            TrinketHidCombo.pressKey(0, 0); // (2)
if (keydata==0xF9060707) TrinketHidCombo.pressKey(0, KEYCODE_3);            TrinketHidCombo.pressKey(0, 0); // (3)
if (keydata==0xF7080707) TrinketHidCombo.pressKey(0, KEYCODE_4);            TrinketHidCombo.pressKey(0, 0); // (4)
if (keydata==0xF6090707) TrinketHidCombo.pressKey(0, KEYCODE_5);            TrinketHidCombo.pressKey(0, 0); // (5)
if (keydata==0xF50A0707) TrinketHidCombo.pressKey(0, KEYCODE_6);            TrinketHidCombo.pressKey(0, 0); // (6)
if (keydata==0xF30C0707) TrinketHidCombo.pressKey(0, KEYCODE_7);            TrinketHidCombo.pressKey(0, 0); // (7)
if (keydata==0xF20D0707) TrinketHidCombo.pressKey(0, KEYCODE_8);            TrinketHidCombo.pressKey(0, 0); // (8)
if (keydata==0xF10E0707) TrinketHidCombo.pressKey(0, KEYCODE_9);            TrinketHidCombo.pressKey(0, 0); // (9)
if (keydata==0xEE110707) TrinketHidCombo.pressKey(0, KEYCODE_0);            TrinketHidCombo.pressKey(0, 0); // (0)


ms_delay(1);// во избежание слишком частого повтора ввода клавиш
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
  
