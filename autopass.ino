//автоввод пароля в систему Windows
#include "DigiKeyboard.h"
void setup() {
DigiKeyboard.sendKeyStroke(0);
DigiKeyboard.println("");
DigiKeyboard.delay(1000);
DigiKeyboard.println("YOUR PASSWORD");
}
void loop() {
}
