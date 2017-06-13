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


#ifndef _GPIO_H_
#define _GPIO_H_


#include <usbcom.h>

/********************************************************
 *
 *                      DEFINES
 *
 ********************************************************/ 
// Pin <-> Index mapping
#define RB15    1
#define RB14    2
#define RB13    3
#define RB3     4
#define RA1     5
#define RB9     6
#define RB8     7
#define RB7     8
#define RB4     9
#define RB1     10
#define RA0     11
#define RA2     12
#define RA3     13
#define RA4     14




/********************************************************
 *
 *                      CLASSES
 *
 ********************************************************/ 

class Gpio : protected Device {
    
    public:

        Gpio();   //constructor

        
        char set_high(unsigned char pin_index);
        
        char set_low(unsigned char pin_index);

        unsigned char read_gpio(unsigned char pin_index);
        


    protected:

        unsigned char hid_report_out[65];
        unsigned char hid_report_in[65];

};




#endif
