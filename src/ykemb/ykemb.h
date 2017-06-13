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


#ifndef _YKEMB_H_
#define _YKEMB_H_

#include <usbcom.h>


/********************************************************
 *
 *                      CLASSES
 *
 ********************************************************/ 

class Ykemb : protected Device {
    
    public:

        Ykemb();   //constructor

        int ykemb_write_command(unsigned char *i2c_ykemb_addr, unsigned char mem_addrH, unsigned char mem_addrL, unsigned char byte);
        
        unsigned char ykemb_read_command(unsigned char *i2c_ykemb_addr, unsigned char mem_addrH, unsigned char mem_addrL);

        void print_help();


    protected:

        unsigned char hid_report_out[65];
        unsigned char hid_report_in[65];

};










enum ykembCmdAction {
    WRITE,
    READ,
  };
typedef enum ykembCmdAction YkembAction;



int ykemb_command_parser(int argc, char** argv);

int ykemb_command_processor(YkembAction action);






#endif






