# SDC
![Thumbnail](Thumbnail.jpg)
ATmega 8 based self driving car.

Watch the [YouTube](https://studio.youtube.com/video/CVWcEM45d_U/edit) video to develop some comprehension.

# SETTING UP ATMEGA 8
The ATmega 8 is programmed using an ICSP programmer. In my case, I used an Arduino UNO as an ICSP programmer.
By default, the microcontroller uses the internal 8MHz internal PC oscillator, but we want to use an external 16 MHz oscillator.
So we need to make certain changes to the fuse bits of the ATmega 8. Below are the steps to do so:
1. Download and install AVRDude. AVRDude is the program used by Arduino IDE and PlatformIO to upload your code to an AVR microcontroller.
2. Open up the Arduino IDE, select ```ArduinoISP``` under File/Examples/ and hit upload.
3. Wire up the Arduino and ATmega8 as shown in the [schematic](/Programmer/ATmega8-programmer.pdf): ![ATmega8 programmer](/Programmer/ATmega8-programmer.png)
4. By default, the low fuse of the ATmega8 is set to 0xE1. This must be set to 0xE4 to configure the microcontroller to run at 8MHz. Type ``` avrdude -c stk500v1  -P COM5 -p atmega8 -b 19200 -U lfuse:w:0xe4:m -U hfuse:w:0xd9:m ```. Alternatively, you can use an online [AVR fuse bit calculator](https://www.engbedded.com/fusecalc/) for your selected microcontroller. ![Changing lfuse](/Programmer/Changing-fuse-bits.png)
### Note: 
The ```-P <port>```argument specifies the connection port. In my case, the arduino is connected to ```COM5``` and hence the argument ```-P COM5```. For ```-p <partno>``` either ```-p m8``` or ```-p atmega8``` can be used. Refer this [guide](https://www.ladyada.net/learn/avr/avrdude.html) for more information.

5. That is all. The ATmega8 is now ready to be programmed with PlatformIO using the arduino as an ISP programmer.
