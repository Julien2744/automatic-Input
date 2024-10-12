# Automatic Input
## About it
A simplified version of the `winuser.h` library

This repositorie incule an exemple of the **config/setting file syntax** and an uses-case exemple

# doc
## public objects
enumarations that are needed for class method
 - `enum keyboard_type {qwerty, azerty}`
 - `enum config {KeyBoardType, timeBeforeBegin, timePerChar, timePerEnter, autoEnterKey}`
## private variables
**Variables that are needed in the class configuration/settings**
- `char keyboardType` : keyboard layout *(ex. qwerty)* variable that use `keyboard_type` enum object
- `unsigned long beginDelay` : interger that it's use for a cooldown method *(time in ms)*
- `unsigned int charDelay` : integer that it's use for a delay inbetween every sended input to slowdown the program *(time in ms)*
- `unsigned int enterDelay` : integer that it's use for a delay for every *enter key* input sended, if needed *(time in ms)*
- `bool autoEnter` : boolean value if the user want to send an *enter key* after the end of an char array or string

**Variables that are used in the `winuser.h` library**
 - `INPUT ip` : `winuser.h` class main object
 - `bool caps` : boolean value to know if a *shift key* need to be pressed
## Constrcutors
- ### `autoInput(ifstream& configFile)`
Main constructor using a **config/setting file**, the file ***config.txt*** is an exemple of it's syntax

- ### `autoInput(unsigned long begin_Delay, unsigned int char_Delay, unsigned int enter_Delay, bool auto_Enter)`
Other contsructor that dosen't use external file
## class methods
- ### `void setConfig(keyboard_type Keyboard_Type, long begin_Delay, unsigned int char_Delay, unsigned int enter_Delay, bool auto_Enter)`
method that change the class config
- ### `void startBeginDelay()`
Sleep the program for a given amount of time in the config/settings and print(`cout`) time left
- ### `int asciiToVKC(int asciiVal, keyboard_type kbType)`
Convert the `ASCII value` to return it to it's `Microsoft virtual key code` equivalent, **warning the return key value may require pressing another key**.
- ### `void sendInputRaw(int keyValue, bool releaseKey = 1)`
Simplified version of the `winuser.h` class `SendInput()` method

if `releaseKey` is equal to 0 the sended key will not be release
- ### `void sendInput(char character, bool releaseKey = 1)`
Send input with `character` as an `ASCII` instead of an `Microsoft virtual key code` value

if `releaseKey` is equal to 0 the sended key will not be release
- ### `void sendInput(char character[])`
Send the given char array as an input *(use `sendInput` method)*
- ### `void sendInput(string text)`
Send the given string as an input *(use `sendInput` method)*
- ### `string getConfig(config) const`
Return the given `config` value as a string
