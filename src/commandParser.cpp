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


// INCLUDES ---------------------------------------------------------------

#include <cstdlib>
#include <iostream>
#include <stdio.h>

#include "stdafx.h"
#include "commandParser.h"
#include "usbcom.h"

#include <ykemb.h>
#include <gpio.h>



using namespace std;


enum actions {
    LIST_DEVICES,
    PRINT_HELP,
    LIST_MODULES,
    PRINT_HELP_YKEMB,
    PROCESS_COMMAND,
    RUN_YKEMB,
    RUN_GPIO,
};



bool bySerial = false;



int commandParser(int argc, char** argv) {

	MessageScope scope;
    YkembAction ykemb_action;
    enum actions action;

    unsigned char i2c_ykemb_addr[3];
    unsigned char ykemb_mem_addrH[2];
    unsigned char ykemb_mem_addrL[2];
    unsigned char ykemb_byte[2];

  	char choice;
  	char cmd = 0x00;
	char *iSerial=NULL;
    char response;
    char port = 0;

  	if( argc <= 1) {
		printUsage(argv[0]);
		return 0;
    }



  	//Parse input options and define action
    if(argc >= 2) {
        if((argv[1][0]=='-') && (argv[1][1]=='l')) {
			action = LIST_DEVICES;
		} else if((argv[1][0]=='-') && (argv[1][1]=='m')) {
            action = LIST_MODULES;
        } else if((argv[1][0] == 'y') && (argv[1][1]=='k') && (argv[1][2]=='e') && (argv[1][3]=='m') && (argv[1][4]=='b')) {
            action = RUN_YKEMB;
        } else if((argv[1][0] == 'g') && (argv[1][1]=='p') && (argv[1][2]=='i') && (argv[1][3]=='o')) {
            action = RUN_GPIO;
	    } else {
		    action = PRINT_HELP;
        }


    } else {
        action = PRINT_HELP;
    }


	

//Process action
//
    switch (action) {

        case RUN_YKEMB:
            ykemb_command_parser(argc, argv);
            break;

        case RUN_GPIO:
            gpio_command_parser(argc, argv);
            break;

        default:
            printUsage(argv[0]);
            break;
    }





    return 0;
}



int printUsage(char* execName){

    printf("\n-------------------");
    printf("\n\tRun:\n");
    printf("-------------------\n");
    printf("\n%s gpio \t\tTo see option for GPIO control\n", execName);
    printf("\n%s ykemb \t\tTo see option for YKEMB interface\n\n\n", execName);
    
    return 0;
}






/*****************************************************************
 * Function: gpio_command_parser
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Precedences:
 *
 *****************************************************************/
char gpio_command_parser(int argc, char** argv) {
    unsigned char index=0;
    unsigned char value=0;
    Gpio *gpio = new Gpio();

    if(argc < 4) {
        print_help_gpio();
        return 0;
    }

    

    //get pin index
    if ((argv[3][0]=='R') && (argv[3][1]=='A')) {
        if(argv[3][2]=='0') {
            index = 11; 
        } else if(argv[3][2]=='1') {
            index = 5;
        } else if(argv[3][2]=='2') {
            index = 12;
        } else if(argv[3][2]=='3') {
            index = 13;
        } else if(argv[3][2]=='4') {
            index = 14;
        } 

    } else if((argv[3][0]=='R') && (argv[3][1]=='B')) {
        if((argv[3][2]=='1') && (argv[3][3]=='5')) {
            index = 1;
        } else if((argv[3][2]=='1') && (argv[3][3]=='4')) {
            index = 2;
        } else if((argv[3][2]=='1') && (argv[3][3]=='3')) {
            index = 3;
        } else if(argv[3][2]=='1') {
            index = 10;
        } else if(argv[3][2]=='2') {
            index = 15;
        } else if(argv[3][2]=='3') {
            index = 4;
        } else if(argv[3][2]=='4') {
            index = 9;
        } else if(argv[3][2]=='7') {
            index = 8;
        } else if(argv[3][2]=='8') {
            index = 7;
        } else if(argv[3][2]=='9') {
            index = 6;
        }

    } else {
        print_help_gpio();
    }     


    //parse command options
    if((argv[2][0] == '-') && (argv[2][1] == 'w')) {

        if((index!=14)&&(index!=9)) {
            //check if high or low
            if(argv[4][0] == '0') {
                gpio->set_low(index); 
            } else if(argv[4][0] == '1') {
                gpio->set_high(index);
            } else {
                print_help_gpio();
            }
        } else {
            printf("\n\nPins RB4 and RA4 are INPUT only. Only READ commands are permited.\n\n");
        }
    } else if((argv[2][0] == '-') && (argv[2][1] == 'r')) {
        value = gpio->read_gpio(index);
        printf("\n\nValue read: 0x%x\n\n", value);

    } else {
        print_help_gpio();
    }
       
}




/*****************************************************************
 * Function: print_help_gpio
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Precedences:
 *
 *****************************************************************/
void print_help_gpio(void) {

    printf("\n\nGPIO Command Structure:\n");
    printf("\nykam24cmd gpio -<command_option> <gpio_pin> <value>\n");
    printf("\nWhere:\n");
    printf("\ncommand_option\t: w -> write command; r -> read command\n");
    printf("\ngpio_pin\t: YKAMELEAN24 pin name as printed in board ex., RB9. This option is case sensitive.\n");
    printf("\nvalue\t: 0 or 1 value to be writen to GPIO. 1 is High and 0 is Low.\n\n");

}





