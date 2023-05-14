#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cryptageV2(char* message, short decalage, char* newc) {
    unsigned int i = 0;
    short rang;
    if(strlen(message) % 2 == 0) {
        decalage += 3;
    }
    while(message[i] != '\0') {
        if((message[i] >= 'a') && (message[i] <= 'z')) {
            rang = (message[i] - 'a' + decalage) % 26;
            if(rang < 0) rang += 26;
            newc[i] = 'a' + rang;
        }
        else if((message[i] >= 'A') && (message[i] <= 'Z')) {
            rang = (message[i] - 'A' + decalage) % 26;
            if(rang < 0) rang += 26;
            newc[i] = 'A' + rang;
        }
        else if(message[i] == ' ') {
            newc[i] = '^';
        }
        else if(message[i] == '&') {
            newc[i] = ' ';
        }
        else if(message[i] == '\'') {
            newc[i] = ')';
        }
        else if(message[i] == '-') {
            newc[i] = '(';
        }
        else if(message[i] == '_') {
            newc[i] = '-';
        }
        else if(message[i] == '@') {
            newc[i] = '[';
        }
        else if(message[i] == '$') {
            newc[i] = '@';
        }
        else if(message[i] == '*') {
            newc[i] = '$';
        }
        else if(message[i] == '!') {
            newc[i] = '*';
        }
        else if(message[i] == '%') {
            newc[i] = '!';
        }
        else if(message[i] == '#') {
            newc[i] = '%';
        }
        else {
            newc[i] = message[i];
        }
        i++;
    }
    newc[i] = '\0';
}
