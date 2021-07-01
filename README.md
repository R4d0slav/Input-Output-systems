**Mini Piano**

**Introduction**

- This project is a miniturised version of a piano, with a challenge.

- When the challenge is started, we listen to the sounds played and after it finishes, we try and guess the sounds.

**Getting Started**

- First I created a basic mini piano with 8 buttons, and 1 piezo.
- The buttons are connected to one analog pin in the arduino. Between themselves, they are connected with resistors of different values, so we can tell them apart. Based on the value of the resistors we have lowerLimit and upperLimit frequencies for choosing what frequency to play on the piezo.
- We have 8 buttons and 8 resistors connecting them. The first resistor has a value of 2000[Ohm], then the second starts at 200[Ohm] and every next one is doubled. So we got 200, 400, 800, 1600, 3200, 6400,and finally 12800. The purpose of the value of the resistor made in pattern is to make the value in analog inputs go up constantly.

**Adding a challenge**

- Next I added a button that initiates the challenge, and a led that shows when the challenge starts and ends.
- The challenge: 3 random frequencies are played and then you have to guess which ones they were. After you input your 3 frequencies, you "invalid" or "valid" is printed on a LDC.
- For the challenge I created a function that initiates the challenge, where it picks 3 random frequencies, inserts them in an array and plays them. After that, when the user clicks on a button, the frequency for that button is remembered in an array, and when the user plays 3 sounds (clicks 3 buttons) anther function is called. That function checks the frequencies from the challenge array and the user input array and returns the result.

**Connecting 2 arduino boards**

- Finally, I connect 2 arduino boards with I2C (Master, Slave).
- The Master initiates the challenge, makes all the calculations and sends the result to the Slave. 
- The Slave then receives the data transmitted and checks if the received string is true of false and prints the "Correct" or "Incorrect" on a LCD.

**Finall adjustments**

- Because it is very difficult to guess the frequencies by sound alone, I added leds for each button so they will light up when a button is pressed, or when a sound is played by the challenge. There are 8 leds connected to 8 digital pins to the arduino (Master).

