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



#include "gpio.h"
#include <stdio.h>
#include <string2val.h>



/*****************************************************************
 * Function: Gpio
 *
 * Description: Gpio class constructor
 *
 * Inputs:
 *
 * Outputs:
 *
 * Precedences:
 *
 *****************************************************************/
Gpio::Gpio() {

}






/*****************************************************************
 * Function: set_high
 *
 * Description: Gpio class constructor
 *
 * Inputs:
 *
 * Outputs:
 *
 * Precedences:
 *
 *****************************************************************/
char Gpio::set_high(unsigned char pin_index) {
    
    int error;

    //populate hid_report2send
    hid_report_out[0] = 0;      //Windows requires require a byte with the report id.
                                //This is just for keep Windows "happy" it is not part
                                //of the actual command message/report sent to the USB device.
    hid_report_out[1] = 0x01;           //GPIO scope
    hid_report_out[2] = 0x01;           //COMMAND type
    hid_report_out[3] = 0x01;           //WRITE command
    hid_report_out[4] = pin_index;      //GPIO pin index
    hid_report_out[5] = 1;              //High
  
    error = sendHidReport(NULL, hid_report_out, hid_report_in);
    if(error){
        return error;
    }
    
    return 0;

}





/*****************************************************************
 * Function: set_low
 *
 * Description: Gpio class constructor
 *
 * Inputs:
 *
 * Outputs:
 *
 * Precedences:
 *
 *****************************************************************/
char Gpio::set_low(unsigned char pin_index) {

    int error;

    //populate hid_report2send
    hid_report_out[0] = 0;      //Windows requires require a byte with the report id.
                                //This is just for keep Windows "happy" it is not part
                                //of the actual command message/report sent to the USB device.
    hid_report_out[1] = 0x01;           //GPIO scope
    hid_report_out[2] = 0x01;           //COMMAND type
    hid_report_out[3] = 0x01;           //WRITE command
    hid_report_out[4] = pin_index;      //GPIO pin index
    hid_report_out[5] = 0;              //High
  
    error = sendHidReport(NULL, hid_report_out, hid_report_in);
    if(error){
        return error;
    }
    
    return 0;

}




/*****************************************************************
 * Function: read_gpio
 *
 * Description: Gpio class constructor
 *
 * Inputs:
 *
 * Outputs:
 *
 * Precedences:
 *
 *****************************************************************/
unsigned char Gpio::read_gpio(unsigned char pin_index) {

    int error;

    //populate hid_report2send
    hid_report_out[0] = 0;      //Windows requires require a byte with the report id.
                                //This is just for keep Windows "happy" it is not part
                                //of the actual command message/report sent to the USB device.
    hid_report_out[1] = 0x01;           //GPIO scope
    hid_report_out[2] = 0x01;           //COMMAND type
    hid_report_out[3] = 0x02;           //READ command
    hid_report_out[4] = pin_index;      //GPIO pin index
  
    error = sendHidReport(NULL, hid_report_out, hid_report_in);
    if(error){
        return error;
    }
  
    /*
    printf("\nhid_report_in[0]=%x\n",hid_report_in[0]);
    printf("\nhid_report_in[1]=%x\n",hid_report_in[1]);
    printf("\nhid_report_in[2]=%x\n",hid_report_in[2]);
    printf("\nhid_report_in[3]=%x\n",hid_report_in[3]);
    printf("\nhid_report_in[4]=%x\n",hid_report_in[4]);
    printf("\nhid_report_in[5]=%x\n",hid_report_in[5]);
    printf("\nhid_report_in[6]=%x\n",hid_report_in[6]);
    */

    return hid_report_in[4];

}







