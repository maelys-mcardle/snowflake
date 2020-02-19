# Microprocessor Trainer
This project is to make a calculator-sized device that's somewhere between a microprocesser trainer like the [KIM-1][1] and a 1980's pocket computer like the [Sharp PC-1500][2].

This project is a collaboration between Jamie and Maëlys.

# Hardware
This is the hardware used on this project:
* Microcontroller compatible with Arduino IDE
* [Quimat IIC/I2C/TWI Serial 2004 20x4 LCD Module][3]
* [RobotDyn 16 button keypad module][4]

# Software
A high-level programming language called [Snowflake][5] was developed to allow for programming the device using its numeric keypad. An [interpreter][6] has been developed to simulate programming on the device locally.

# To-Do
* Add null value to parameter value; to distinguish between INT BANK and INT BANK 0. What about STR BANK and STR BANK "" ? 

[1]: https://en.wikipedia.org/wiki/KIM-1
[2]: https://en.wikipedia.org/wiki/Sharp_PC-1500
[3]: https://www.amazon.ca/Quimat-Serial-Module-Shield-Arduino/dp/B0719R3JP7/
[4]: https://www.amazon.ca/RobotDyn-module-Compatible-Raspberry-Assembled/dp/B071KB7RZ5/
[5]: docs/snowflake/
[6]: interpreter/
