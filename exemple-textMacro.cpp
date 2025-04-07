#include <iostream>
#include <string>
#include <fstream>
#include <winuser.h>
#include <windows.h>

#include "autoInputClass.h"

using namespace std;


void setConfig(ifstream& configFile, autoInput& auto_input)
{
    string parameter = "";
    
    autoInput::keyboard_type keyboardType = autoInput::keyboard_type::qwerty;
    unsigned int charDelay = 5;
    unsigned int enterDelay = 5;

    // check the 5 line of the config file to change the coresponding variables
    for(unsigned short i=0; i<3; i++) {
        //get the text in between the ' : ' and the ' , '
        getline(configFile, parameter);
        size_t beginFind = parameter.find(':');
        size_t endFind = parameter.find(',');

        string value = parameter.substr(beginFind+2, (endFind-beginFind)-2);

        //check if the substring text is valid and change the settings value
        switch(i) {
            case 0:
                if(value == "QWERTY") { keyboardType = autoInput::keyboard_type::qwerty; }
                else if(value == "AZERTY") { keyboardType = autoInput::keyboard_type::azerty; }
                else { std::cerr << "invalid keyboard type" << std::endl;}
                break;
            case 1:
                charDelay = stoi(value);
                break;
            case 2:
                enterDelay = stoi(value);
                break;
        }
    }

    auto_input.setConfig(keyboardType, charDelay, enterDelay, true);
}

int hexCharToInt(char hex) 
{
    if(hex >= 48 && hex <= 57) {
        return hex - 48;
    }
    else if(hex >= 65 && hex <= 70) {
        return hex - 55;
    }
    return 0;
}

int main()
{
    ifstream inputFile("inputText.txt");
    ifstream confFile("config.txt");

    autoInput autoInput(autoInput::keyboard_type::qwerty, 5, 5); //class initialisation via a config file
    setConfig(confFile, autoInput);

    unsigned long sleep = 1000;
    cout << "wait before begin: ";
    cin >> sleep;
    Sleep(sleep);

    string text = "";

    //for every line of the txt file send it via the class method
    while(!inputFile.eof()) {
        getline(inputFile, text);
        
        text += 0x0D; //enter key
    
        //for each char in the string send it
        bool controlInput = false;
        string controlText = "";
        for(unsigned int i = 0; i < text.length(); i++) {
            bool skip = false;
            char character = text.at(i);
            //cout << "text.at(" << i << "): " <<  character << " ; ";

            if(character == '`') {
                //if we reach the next `
                if(controlInput == true) {
                    controlText = ""; //only reset the crontrolText when we reach the other `
                    skip = true;
                }
                controlInput = !controlInput;
                //cout << endl << "controlInput is on: " << controlInput << endl;
            }
            else if(controlText != "") {
                //cout << "   controlText: " << controlText << endl;
                char controlChar = 0x0D; //enterkey

                if(controlText == "r0x") { //release key
                    controlChar = (hexCharToInt(text.at(i+1))*16) + hexCharToInt(text.at(i+2));
                    autoInput.sendInputRaw(controlChar, true); 
                }
                else if(controlText == "p0x") { //toggle key press
                    controlChar = (hexCharToInt(text.at(i+1))*16) + hexCharToInt(text.at(i+2)); 
                    autoInput.sendInputRaw(controlChar, false); 
                }
            }

            if(controlInput) {
                controlText += text.at(i+1);
            }
            else if(skip == false){
                autoInput.sendInput(character); //main sendInput
            }
        }
    }

    return 0;
}
