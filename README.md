# 24C-EEPROM-Check

Serial EEPROMs (Electrically Erasable Programmable Read-Only Memory) are non-volatile memory devices. This means that the data is retained even if the chip is not being powered.

These types of EEPROMs can be written more than 1 million times and behave like tiny hard drives, making them ideal for data and program storage.

Enough of theory, but first, let me explain why I decided to develop such a project. Around April 2013, one of the Arduinos I own, a Nano 3.0 to be more specific, had a faulty voltage regulator. This flaw put the 12V from the power supply directly into the 5V line, causing permanent damage to the uC (ATmega328P). Also, as I had attached a 24C32 EEPROM to the circuit, I needed to make sure if it was dead or not.

So, I wrote a few lines of code that would help me confirm any memory bank flaws on the 24C EEPROM series. However, even though serial EEPROMs can be written more than 1 million times, do not run it for too long. The software will run indefinitely until it finds a flaw.

The circuit is extremely simple. You just need the following materials:
- Arduino Nano 3.0
- 24C series EEPROM
- Breadboard and wires

![alt text](resources/24C-EEPROM-Check_bb.png?raw=true)

Upload the [code](_24C_EEPROM_Check.ino) to the board, open the Serial Monitor, and let it run for a while. The first number represents the byte position that will be tested. The second number is the random value that will be written into that byte. If the read value (third number) equals the written value, an "OK" message will pop up. Else, a "NOK" message will be thrown, and the program stops.

![alt text](resources/SerialMonitor.jpg?raw=true)

I really hope that your EEPROM is fully functional 🙂

As homework, you can try to change this code into a more effective and simpler one. My idea is to write in each byte the following bits: 0b10101010. And on the next run, write its invert: 0b01010101. With a code like this, you can check the entire EEPROM with only two write/read cycles.