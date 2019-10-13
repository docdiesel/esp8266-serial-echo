# esp8266-serial-echo

This is a simple sketch that uses a software serial on an ESP8266
to read data from the serial line and then echo it back. I used it
as counter part when I was working on some serial client and needed
to check if the basic communication was working.

## Attention
I noticed that software serial on ESP8266 is not that reliable. I
would not recommend to use it in production. Use an ESP32 instead;
it comes with three hardware serial.

