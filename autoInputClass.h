#include <iostream>
#include <winuser.h> // https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
#include <fstream>

#ifndef autoInputClass
#define autoInputClass

using namespace std;

class autoInput {

    public :
        //settings name for other uses-case
        enum keyboard_type {qwerty, azerty};
        enum config {KeyBoardType, timeBeforeBegin, timePerChar, timePerEnter};

    private:
       
        //settings
        char keyboardType = azerty;
        unsigned long beginDelay = 3000;
        unsigned int charDelay = 5;
        unsigned int enterDelay = 5;

        //needed var
        INPUT ip;
        bool caps = false;

    public:
        // constructor using a .txt config/setting file
        autoInput(ifstream& configFile);
        // constructor without a config/setting file
        autoInput(config keyboard_type, unsigned long begin_Delay, unsigned int char_Delay, unsigned int enter_Delay);

        // set class config for sending input
        void setConfig(keyboard_type Keyboard_Type, long begin_Delay, unsigned int char_Delay, unsigned int enter_Delay, bool auto_Enter);

        // countdown
        void startBeginDelay();

        // ASCII character to microsoft virtual key code convertor
        int asciiToVKC(int asciiVal, keyboard_type kbType);
        
        //send input without any modification
        void sendInputRaw(int keyValue, bool releaseKey = 1);
       
        //main send input for an ascii char
        void sendInput(char character, bool releaseKey = 1);
        //send text using a char array
        void sendInput(char character[], bool autoEnter = 1);
        //send text using a string text
        void sendInput(string text, bool autoEnter = true);

        //config getter
        string getConfig(config) const;
};

#endif