# Arcade.Touch.Panel
Capacative Touch Panel using custom PCB and Arduino Leo

int pins are mapped to custom PCB in eagle files. 
Buttons are VCClite capacative touch LCD buttons:
https://vcclite.com/product/csms15cic04/

I specifically used White which did not need SMD resistors and run fine off of USB power (though they are VERY bright).

LEDTimer = 100000;  Can be adjusted to set how long until 'latched' buttons auto off their lights. Example: If you press a button and it is set to 'non latching' the light would blink on touch, but then be in 'always off'. If it was 'latched' (such as mute) the light will remain lit once pressed until it is pressed again OR until LEDTimer ms have passed. Any lights in the 'latched' state would return to their state position on the next button touch.

switch (Bindex) defines the 8 buttons. This sends keystrokes to the system as if the Leonardo was a simple keyboard. The sample file is setup with hotkeys that map to the associated AutoHotKey file to perform the designated actions. 

Example of unlatched press (case 0):
    3 keys are pressed in sequence using Keyboard.press(); then all released using Keyboard.releaseAll();. The light is 'blinked' with a pin write HIGH, delay, and pin write LOW. This sends the sequence of keys then blinks the light. No data is retained and everything is ready for the next loop.

Example of a latched press (case 1):
    lastLEDState[Bindex] is verified. If 'unlatched state' is stored for this button number then we perform the keypress and switch the state from 0 to 1. An immediate exit will allow the cycleLEDs() routine to update turn on the LED and return for the next press. If the reverse is true we can pass the same set of keys again, or an alternate set (in this case we're passing Play [CTRL+SHIFT+G], on latch, then Stop [CTRL+SHIFT+D] on unlatch) and changing the state to off.
    
    
This should allow you to perform almost any task! You can even double your buttons with a latching 'shift' button! Just update your .ahk file to match your keystrokes and go nuts.
