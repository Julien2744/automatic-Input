#include <iostream>
#include <string>

#include "autoInputClass.h"

using namespace std;

int hexCharToInt(char hex) 
{
    if(hex >= 48 && hex <= 57) {
        return hex - 48;
    }
    else if(hex >= 65 && hex <= 70) {
        return hex - 55;
    }
    else {
        return 0;
    }

}

int main()
{
    ifstream inputFile("inputText.txt");
    ifstream confFile("config.txt");
    
    autoInput autoInput(confFile); //class initialisation via a config file

    autoInput.startBeginDelay();

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