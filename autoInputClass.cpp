#include <iostream>
#include <string>
#include <fstream>
#include <winuser.h> // https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
#include <windows.h>

#include "autoInputClass.h"

// constructor with a config/setting file
// read the config .txt file
autoInput::autoInput(ifstream& configFile)
{
    string parameter = "";
    
    // check the 5 line of the config file to change the coresponding variables
    for(unsigned short i=0; i<4; i++) {
        //get the text in between the ' : ' and the ' , '
        getline(configFile, parameter);
        size_t beginFind = parameter.find(':');
        size_t endFind = parameter.find(',');

        string value = parameter.substr(beginFind+2, (endFind-beginFind)-2);
        
        //check if the substring text is valid and change the settings value
        switch(i) {
            case 0:
                if(value == "QWERTY") { keyboardType = qwerty; }
                else if(value == "AZERTY") { keyboardType = azerty; }
                else { std::cerr << "invalid keyboard type" << std::endl;}
                break;
            case 1:
                beginDelay = stoi(value);
                break;
            case 2:
                charDelay = stoi(value);
                break;
            case 3:
                enterDelay = stoi(value);
                break;
        }
    }
    
    // INPUT variable initialisation
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
}

//constructor without a config file
autoInput::autoInput(config kbT, unsigned long db, unsigned int cd, unsigned int ed)
{
    // settings variables initialisation
    keyboardType = kbT;
    beginDelay = db;
    charDelay = cd;
    enterDelay = ed;

    // INPUT variable initialisation
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
}

//set the class config for sending input
void autoInput::setConfig(keyboard_type Keyboard_Type, long begin_Delay, unsigned int char_Delay, unsigned int enter_Delay, bool auto_Enter)
{
    keyboardType = Keyboard_Type;
    beginDelay = begin_Delay;
    charDelay = char_Delay;
    enterDelay = enter_Delay;
}

//countdown
void autoInput::startBeginDelay()
{
    cout << "Begin in: " << beginDelay << " milliseconds" << endl;
    for(unsigned long i=1; i<=beginDelay; i+=1000) {
        cout << "..." << i/1000;
        Sleep(1000);
    }
    cout << endl;
}

// ASCII character to microsoft virtual key code convertor
int autoInput::asciiToVKC(int asciiVal, keyboard_type kbType)
{
    if(asciiVal >= 0x48 && asciiVal <= 0x5A) { //capitalize character in ASCII
        return asciiVal;
    }
    else if(asciiVal >= 0x30 && asciiVal <= 0x39) { //number
        return asciiVal + 48;
    }
    else if(asciiVal >= 0x61 && asciiVal <= 0x7A) { //non-capitalize character in ASCII
        return asciiVal -32;
    }
    else if(kbType == azerty){ //special character in azerty layout that need convertion
        switch(asciiVal) { //warning: some of the return need another key to be pressed ex: ' # ' or ' . '
            case 0x21: // !
                return 0xDF; break;
            case 0x22: // "
                return 0x33; break;
            case 0x23: // # need alt-gr
                return 0x33; break;
            case 0x24: // $
                return 0xBA; break;
            case 0x25: // % need shift
                return 0xC0; break;
            case 0x26: // &
                return 0x31; break;
            case 0x27: // '
                return 0x34; break;
            case 0x28: // (
                return 0x35; break;
            case 0x29: // )
                return 0xDB; break;
            case 0x2A: // *
                return 0x6A; break;
            case 0x2B: // +
                return 0x6B; break;
            case 0x2C: // ,
                return 0xBC; break;
            case 0x2D: // -
                return 0x6D; break;
            case 0x2E: // .
                return 0x6E; break;
            case 0x2F: // / need shift
                return 0xBF; break;
            case 0x3A: // :
                return 0xBF; break;
            case 0x3B: // ;
                return 0xBE; break;
            case 0x3C: // <
                return 0xE2; break;
            case 0x3D: // =
                return 0xBB; break;
            case 0x3E: // > need shift
                return 0xE2; break;
            case 0x3F: // ? need shift
                return 0xBC; break;
            case 0x40: // @ need alt-gr
                return 0x30; break;
            case 0x5B: // [ need alt-gr
                return 0x35; break;
            case 0x5C: // anti-slash need alt-gr
                return 0x38; break;
            case 0x5D: // ] need alt-gr
                return 0xDB; break;
            case 0x5E: // ^ need lat-gr
                return 0x39; break;
            case 0x5F: // _
                return 0x38; break;
            case 0x7B: // { need alt-gr
                return 0x34; break;
            case 0x7C: // | need alt-gr
                return 0x36; break;
            case 0x7D: // } need alt-gr
                return 0xBB; break;
            default: // can be space-bar or other
                return asciiVal;
                break;
        }
    }
    else if(kbType == qwerty) { //special character in qwerty layout that need convertion
        switch(asciiVal) { //warning: some of the return need another key to be pressed ex: ' # ' or ' ! '
            case 0x21: // ! need shift
                return 0x31; break; 
            case 0x22: // " need shift
                return 0xDE; break;
            case 0x23: // # need shift
                return 0x33; break;
            case 0x24: // $ need shift
                return 0x34; break;
            case 0x25: // % need shift
                return 0x35; break;
            case 0x26: // & need shift
                return 0x37; break;
            case 0x27: // '
                return 0xDE; break;
            case 0x28: // ( need shift
                return 0x39; break;
            case 0x29: // ) need shift
                return 0x30; break;
            case 0x2A: // *
                return 0x6A; break;
            case 0x2B: // +
                return 0x6B; break;
            case 0x2C: // ,
                return 0xBC; break;
            case 0x2D: // -
                return 0x6D; break;
            case 0x2E: // .
                return 0x6E; break;
            case 0x2F: // / need shift
                return 0xBF; break;
            case 0x3A: // : need shift
                return 0xBA; break;
            case 0x3B: // ;
                return 0xBA; break;
            case 0x3C: // < need shift
                return 0xBC; break;
            case 0x3D: // =
                return 0xBB; break;
            case 0x3E: // > need shift
                return 0xBE; break;
            case 0x3F: // ? need shift
                return 0xBF; break;
            case 0x40: // @ need shift
                return 0x32; break;
            case 0x5B: // [
                return 0xDB; break;
            case 0x5C: // anti-slash
                return 0xDC; break;
            case 0x5D: // ]
                return 0xDD; break;
            case 0x5E: // ^ need shift
                return 0x36; break;
            case 0x5F: // _ need shift
                return 0xBD; break;
            case 0x7B: // { need shift
                return 0xDB; break;
            case 0x7C: // | need shift
                return 0xDC; break;
            case 0x7D: // } need shift
                return 0xDD; break;
            default: // can be space-bar or other
                return asciiVal;
                break;
        }
    }
    else { //undefine keyboard type
        return asciiVal;
    }
}

//send input without any modification
void autoInput::sendInputRaw(int keyValue, bool releaseKey)
{
    //std::cout << "input 0d" << keyValue << " -> (char)" << (char)keyValue << endl;

    ip.ki.wVk = keyValue;
    ip.ki.dwFlags = 0; //hold the key
    SendInput(1, &ip, sizeof(INPUT));
    
    if(releaseKey) {
        Sleep(charDelay);
        ip.ki.dwFlags = KEYEVENTF_KEYUP; //realease the key
        SendInput(1, &ip, sizeof(INPUT));
    }

    Sleep(charDelay);
}

//main send input for an ASCII char
void autoInput::sendInput(char character, bool releaseKey)
{
    //std::cout << "input " << character  << " => 0d" << (int)character << std::endl;
    
    bool shift = false;
    
    if(character >= 0x48 && character <= 0x5A) { //capitalize character in ASCII
        // keep the shift key pressed
        ip.ki.wVk = 0x10; //shift key
        ip.ki.dwFlags = 0; //hold the key
        SendInput(1, &ip, sizeof(INPUT));
        shift = true; // remind the methode to un-shift later

        Sleep(charDelay); // Sleep in case if the output device isn't fast enought

        // send the character
        ip.ki.wVk = character;
        ip.ki.dwFlags = 0;
        SendInput(1, &ip, sizeof(INPUT));
    }
    else if(character >= 0x30 && character <= 0x39) { //number
        character += 48; // ASCII to VK converstion

        ip.ki.wVk = character;
        ip.ki.dwFlags = 0;
        SendInput(1, &ip, sizeof(INPUT));
    }
    else if(character >= 0x61 && character <= 0x7A) { //non-capitalized character in ASCII
        character -= 32; // ASCII to VK converstion
        ip.ki.wVk = character;
        ip.ki.dwFlags = 0;
        SendInput(1, &ip, sizeof(INPUT));
    }
    else {
        if(keyboardType == qwerty) {
            //check if the special character need shift
            if( character == 0x21 ||
                character == 0x22 ||
                character == 0x23 ||
                character == 0x24 ||
                character == 0x25 ||
                character == 0x26 ||
                character == 0x28 ||
                character == 0x29 ||
                character == 0x2F ||
                character == 0x3A ||
                character == 0x3C ||
                character == 0x3E ||
                character == 0x3F ||
                character == 0x5E ||
                character == 0x5F ||
                character == 0x7B ||
                character == 0x7C ||
                character == 0x7D )
            {
                // keep the shift key pressed
                ip.ki.wVk = 0x10; //shift key
                ip.ki.dwFlags = 0; //hold the key
                SendInput(1, &ip, sizeof(INPUT));
                shift = true; // remind the methode to un-shift later

                Sleep(charDelay); // Sleep in case if the output device isn't fast enought

                ip.ki.wVk = asciiToVKC(character, qwerty);
                ip.ki.dwFlags = 0;
                SendInput(1, &ip, sizeof(INPUT));
            }
            else { //the special character didn't need shift
                ip.ki.wVk = asciiToVKC(character, qwerty);
                ip.ki.dwFlags = 0;
                SendInput(1, &ip, sizeof(INPUT));
            }
        }
        else if(keyboardType == azerty) {
            //check if the special character need shift
            if( character == 0x25 ||
                character == 0x2F ||
                character == 0x3E ||
                character == 0x3F )
            {
                // keep the shift key pressed
                ip.ki.wVk = 0x10; //shift key
                ip.ki.dwFlags = 0; //hold the key
                SendInput(1, &ip, sizeof(INPUT));
                shift = true; // remind the methode to un-shift later

                Sleep(charDelay); // Sleep in case if the output device isn't fast enought

                ip.ki.wVk = asciiToVKC(character, azerty);
                ip.ki.dwFlags = 0;
                SendInput(1, &ip, sizeof(INPUT));
            } //check if the special character need right-alt / alt-gr
            else if( character == 0x23 ||
                     character == 0x40 ||
                     character == 0x5B ||
                     character == 0x5C ||
                     character == 0x5D ||
                     character == 0x5E ||
                     character == 0x7B ||
                     character == 0x7C ||
                     character == 0x7D )
            {
                // keep the right-alt pressed
                ip.ki.wVk = 0xA5; //right-alt / alt-gr key
                ip.ki.dwFlags = 0; //hold the key
                SendInput(1, &ip, sizeof(INPUT));

                Sleep(charDelay); // Sleep in case if the output device isn't fast enought

                ip.ki.wVk = asciiToVKC(character, azerty);
                ip.ki.dwFlags = 0;
                SendInput(1, &ip, sizeof(INPUT));

                Sleep(charDelay);

                // release the right-alt key
                ip.ki.wVk = 0xA5; //alt-gr key or right alt
                ip.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &ip, sizeof(INPUT));
            }
            else { //no other key need to be pressed
                ip.ki.wVk = asciiToVKC(character, azerty);
                ip.ki.dwFlags = 0;
                SendInput(1, &ip, sizeof(INPUT));
            }
        }
    }

    if(releaseKey) {
        Sleep(charDelay);
        ip.ki.dwFlags = KEYEVENTF_KEYUP; //release the key for the other char to be sended
        SendInput(1, &ip, sizeof(INPUT));
    }
    
    if(shift) { //caps lock off
        Sleep(charDelay);
        
        ip.ki.wVk = 0x10; 
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
        caps = false;
    }
    
    if(character == 0x0D) {
        Sleep(enterDelay);
    }
    else {
        Sleep(charDelay);
    }
    
}

//send text using a char array
void autoInput::sendInput(char character[], bool autoEnter)
{
    unsigned int i = 0;
    //for each char in the array send it
    while(character[i] != '\0') {
        sendInput(character[i]);
        i++;
    }

    // send an enter at the end of the array
    if(autoEnter) {
        ip.ki.wVk = 0x0D; //enter key
        ip.ki.dwFlags = 0; //hold the key
        SendInput(1, &ip, sizeof(INPUT));

        Sleep(charDelay); // Sleep in case if the output device isn't fast enought

        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
    }
}

//send text using a string text
void autoInput::sendInput(string text, bool autoEnter)
{
    // send an enter at the end of the string
    if(autoEnter) {
        text += 0x0D;
    }
    
    //for each char in the string send it
    for(unsigned int i = 0; i < text.length(); i++) {
        int character = text.at(i);
        sendInput(character);
    }
}

//config getter
string autoInput::getConfig(config value) const
{
    switch (value) {
        case KeyBoardType:
            if(keyboardType == qwerty) {return "qwerty";}
            else if(keyboardType == azerty) {return "azerty";}
            else {return "undefine";}
            break;
        case timeBeforeBegin:
            return to_string(beginDelay);
            break;
        case timePerChar:
            return to_string(charDelay);
            break;
        case timePerEnter:
            return to_string(enterDelay);
            break;
    }
}