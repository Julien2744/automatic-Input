# Automatic Input
## About it
A simplified version of the `winuser.h` library

This repository also incule an exemple of the library.

> [!WARNING]
> I only made this to exercice myself, and decided to publish this publicly.
> 
> The class and example are not supposed to be practically used !

# doc
## public objects
enumarations that are needed for class method
 - `enum keyboard_type {qwerty, azerty}`
 - `enum config {KeyBoardType, timePerChar, timePerEnter}`
## private variables
**Variables that are needed in the class configuration/settings**
- `char keyboardType` : keyboard layout *(ex. qwerty)* variable that use `keyboard_type` enum object
- `unsigned int charDelay` : integer that it's use for a delay inbetween every sended input to slowdown the program *(time in ms)*
- `unsigned int enterDelay` : integer that it's use for a delay for every *enter key* input sended, if needed *(time in ms)*

**Variables that are used in the `winuser.h` library**
 - `INPUT ip` : `winuser.h` class main object
 - `bool caps` : boolean value to know if a *shift key* need to be pressed
## Constrcutors
- ### `autoInput(keyboard_type keyboard_type, unsigned int char_Delay, unsigned int enter_Delay)`
Main contsructor
## class methods
- ### `void setConfig(keyboard_type Keyboard_Type, unsigned int char_Delay, unsigned int enter_Delay, bool auto_Enter)`
method that change the class config
- ### `int asciiToVKC(int asciiVal, keyboard_type kbType)`
Convert the `ASCII value` to return it to it's `Microsoft virtual key code` equivalent, **warning the return key value may require pressing another key**.
- ### `void sendInputRaw(int keyValue, bool releaseKey = 1)`
Simplified version of the `winuser.h` class `SendInput()` method 

if `releaseKey` is equal to 0 the sended key will not be release
- ### `void sendInput(char character, bool releaseKey = 1)`
Send input with `character` as an `ASCII` instead of an `Microsoft virtual key code` value 

if `releaseKey` is equal to 0 the sended key will not be release
- ### `void sendInput(char character[], bool autoEnter = 1)`
Send the given char array as an input *(use `sendInput` method)*
- ### `void sendInput(string text, bool autoEnter = true)`
Send the given string as an input *(use `sendInput` method)*
- ### `string getConfig(config) const`
Return the given `config` value as a string
