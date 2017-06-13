/*******************************************************************************
Copyright 2017 Yepkit Lda (www.yepkit.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*******************************************************************************/



#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H




/*****************************************
 *          CONSTANT DEFINITION
 *****************************************/
//General Board Scopes (USB message BYTE 0)
#define SCOPE_BYTE_IO       0x01
#define SCOPE_BYTE_I2C      0x02
#define SCOPE_BYTE_RESET    0x02


//Modules Scopes (USB message BYTE 0)
#define SCOPE_BYTE_YKEMB    0x10
#define SCOPE_BYTE_LCD      0x11
#define SCOPE_BYTE_TS100    0x12
#define SCOPE_BYTE_YKUR     0x13


//Message Types (USB message BYTE 1)
#define MSG_TYPE_COMMAND    0x01
#define MSG_TYPE_RESPONSE   0x02


//YEMB Action (USB message BYTE 2)
#define YKEMB_ACTION_WRITE  0x01
#define YKEMB_ACTION_READ   0x02




/*****************************************
 *              TYPEDEFS
 *****************************************/
enum msgScope {
    GPIO,
    I2C,
    RESET,
    YKEMB,
    LCD,
    TS100,
    YKUR,
};
typedef enum msgScope MessageScope;





int commandParser(int argc, char** argv);


char gpio_command_parser(int argc, char** argv);
void print_help_gpio(void);


int printUsage(char*);

#endif // COMMANDPARSER_H
