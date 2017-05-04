Ж # Digispark-ir-remote
Управление ПК при помощи пульта от ТВ. Без всякого сторонего софта.
Отлично подходит для управления HTPC. А самое главное, это цена!!!
В данном примере реализованно управление для KODI медиаплеер.

# Что понадобится
1. DIGISPARK attiny85 aliexpress.com цена 1шт. от 1.17$.
2. TSOP4838 38kHz aliexpress.com цена 2шт. от 0.94$.
3. Библиотека Adafruit-Trinket-USB-master
4. Скетч для управления, взять отсуда SKETCH_KODI.
Оригинал от создателя 
http://arduino.ru/forum/proekty/ik-distantsionnoe-upravlenie-kompom-cherez-digispark

![prototype scheme](https://github.com/maltsevvv/Digispark-ir-remote/blob/master/Digispark%2BTSOP.png)

5. Софт для работы с Digispark: https://digistump.com/wiki/digispark/tutorials/connecting (делать все как на картинках)
6. Скачать библиотеку Adafruit-Trinket-USB-master:
https://github.com/maltsevvv/Digispark-ir-remote/raw/master/TrinketHidCombo.zip
7. Подключить библиотеку:
Скетч/Подключить библиотеку/Добавить .ZIP библиотеку/выбрать загруженный файл.
8. Открыть загруженный файлу SKETCH_KODI.ino
В ардуино выбрать: Загрузить
После появления надписи Plug in device now... (will timeout in 60 second)
Подключить Digispark.
# 
Я задейстовал кнопки на пульте, неиспользуемые для управления ТВ. 
В своем роде получилось HDMI-CEC, один пульт управляет двумя устройствами. Только цена гораздо ниже.
Протестировал на пультах, что попались (LG AKB74915325, SAMSUNG AA59-00741A, SAMSUNG BN59-00685A, MYSTERY MTV-2622LW

# Пока есть одна пробломка. 
После перезагрузки необходимо физически передергивать USB кабель.
