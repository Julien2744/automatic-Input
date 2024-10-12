# Automatic Input
## About it
A simplified version of the `winuser.h` library

The repo include an exemple of the **config/setting file syntax** and a fast output text from .txt file exemple

# doc
## public objects
enumaration that is needed for class method
`enum keyboard_type {qwerty, azerty}`
`enum config {KeyBoardType, timeBeforeBegin, timePerChar, timePerEnter, autoEnterKey}`
## private objects
**These are the main object that is needed for the class configuration**
`char keyboardType` keyboard layout *(ex. qwerty)* variable that use `keyboard_type` enum object
`unsigned long beginDelay` interger that it's use for a cooldown method *(time in ms)*
`unsigned int charDelay` integer that it's use for a delay inbetween every sended input to slowdown the program *(time in ms)*
`unsigned int enterDelay` integer that it's use for a delay for every *enter key* input sended, if needed *(time in ms)*
`bool autoEnter` boolean value if the user want to send an *enter key* after the end of an char array or string

**These are other needed object that don't interfear with the class config**
`INPUT ip` `winuser.h` class main object
`bool caps` boolean value to know if a *shift key* need to be pressed
## Constrcutors
### autoInput(ifstream& configFile)
Main constructor using a **config/setting file**, you can look at ***config.txt*** file as an exemple of it's syntax

### autoInput(unsigned long begin_Delay, unsigned int char_Delay, unsigned int enter_Delay, bool auto_Enter)
Other contsructor that dosen't use external file
## class methods
### void setConfig(keyboard_type Keyboard_Type, long begin_Delay, unsigned int char_Delay, unsigned int enter_Delay, bool auto_Enter)
Class config method if need to change it later
### void startBeginDelay()
Cooldown method that `cout` time left before next line of code *(use the `unsigned long beginDelay` integet)*
### int asciiToVKC(int asciiVal, keyboard_type kbType);
Convert an ASCII value to return it as it's *microsoft keyboard virtual-key-codes* variant, **warning the returned value of the key may need another key to be pressed**
### void sendInputRaw(int keyValue, bool releaseKey = 1)
Simplified version of the `winuser.h` class `SendInput()` method
if the `releaseKey` boolean value is at 0 the sended key will still be pressed
### void sendInput(char character, bool releaseKey = 1)
Main class method that it's use for sending the *microsoft keyboard virtual-key-codes* equivalent of the given ASCII value *(use the class config/setting variables)*
if the `releaseKey` boolean value is at 0 the sended key will still be pressed
### void sendInput(char character[])
Send the char array as an input *(use `sendInput` method)*
### void sendInput(string text)
Send the string as an input *(use `sendInput` method)*
### string getConfig(config) const
Return the given `config`