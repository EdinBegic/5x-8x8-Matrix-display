# 5x-8x8-Matrix-display
An application that enables to drive five 8x8 matrix displays using the MAX7219 driver.

In order to implement the code, use the Mbed C/C++ IDE

Tested on the LPC1114FN28 microcontroller

The MAX7219.h class enables multiple modes of displaying text on the displays:
1. Only one character on all five displays
2. String is displayed character by character on the displays (5 characters at once)
3. String is displayed in the scroll mode (the text shifts from right to left)
4. Simulation of a typewriter
5. Displaying the localtime inherited from the RTC of the microcontroller
6. Decreasing the light brightness of the diodes
7. Increasing the light brightness of the diodes
