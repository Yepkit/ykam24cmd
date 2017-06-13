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

#include "ykemb.h"
#include <string2val.h>
#include <stdio.h>





/*****************************************************************
 * Function: ykemb_command_parser
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
int ykemb_command_parser(int argc, char** argv) {
    
    unsigned char i2c_ykemb_addr[3];
    unsigned char ykemb_mem_addrH[2];
    unsigned char ykemb_mem_addrL[2];
    unsigned char mem_addrH, mem_addrL;
    unsigned char ykemb_byte[2];
    unsigned char byte;

    Ykemb *ykemb = new Ykemb();

    if(argc < 6) {
        ykemb->print_help();
        return 0;
    }

    if((argv[2][0] == '-') && (argv[2][1] == 'w')) {    //WRITE command

//WRITE Command        

        if(argc <=6) {
            ykemb->print_help();
            return 0;
        }


        //get I2C ykemb device address
        i2c_ykemb_addr[0]=char2int(argv[3][0]);
        i2c_ykemb_addr[1]=char2int(argv[3][1]);
        i2c_ykemb_addr[2]=char2int(argv[3][2]); 

        if((argv[4][0]=='0') && (argv[4][1]=='x') && (argv[5][0]=='0') && (argv[5][1]=='x') && (argv[6][0]=='0') && (argv[6][1]=='x')) {
         
            //get memory address
            ykemb_mem_addrH[0]=argv[4][2];
            ykemb_mem_addrH[1]=argv[4][3];
            ykemb_mem_addrL[0]=argv[5][2];
            ykemb_mem_addrL[1]=argv[5][3];

            
            //get byte to be stored
            ykemb_byte[0]=argv[6][2];
            ykemb_byte[1]=argv[6][3];

            //convert mem_addr from string to hexadecimal
            hex2bin(ykemb_mem_addrH, &mem_addrH, 2);
            hex2bin(ykemb_mem_addrL, &mem_addrL, 2);

            //convert byte to be written
            hex2bin(ykemb_byte, &byte, 2);


            printf("\nWrite Command");
            printf("\n--------------------------------------------");
            printf("\n\nI2C YKEMB address: 0b%d%d%d\n", i2c_ykemb_addr[0], i2c_ykemb_addr[1], i2c_ykemb_addr[2]);
            printf("\nMemory address H: 0x%x\tMemory address L: 0x%x\n", mem_addrH, mem_addrL);
            printf("\nByte to be written: 0x%x\n", byte);

            //write byte to ykemb
            ykemb->ykemb_write_command(i2c_ykemb_addr, mem_addrH, mem_addrL, byte);

        } else {
            //action = PRINT_HELP_YKEMB;
        }

    } else if((argv[2][0] == '-') && (argv[2][1] == 'r')) { //READ Command
        
//READ Command 

        if(argc < 6) {
            ykemb->print_help();
            return 0;
        }

        //get I2C ykemb device address
        i2c_ykemb_addr[0]=char2int(argv[3][0]);
        i2c_ykemb_addr[1]=char2int(argv[3][1]);
        i2c_ykemb_addr[2]=char2int(argv[3][2]); 
       
        if((argv[4][0]=='0') && (argv[4][1]=='x') && (argv[5][0]=='0') && (argv[5][1]=='x')) {
         
            //get memory address
            ykemb_mem_addrH[0]=argv[4][2];
            ykemb_mem_addrH[1]=argv[4][3];
            ykemb_mem_addrL[0]=argv[5][2];
            ykemb_mem_addrL[1]=argv[5][3];

            
            //convert mem_addr from string to hexadecimal
            hex2bin(ykemb_mem_addrH, &mem_addrH, 2);
            hex2bin(ykemb_mem_addrL, &mem_addrL, 2);


            printf("\nREAD Command");
            printf("\n--------------------------------------------");
            printf("\n\nI2C YKEMB address: 0b%d%d%d\n", i2c_ykemb_addr[0], i2c_ykemb_addr[1], i2c_ykemb_addr[2]);
            printf("\nMemory address H: 0x%x\tMemory address L: 0x%x\n", mem_addrH, mem_addrL);

            //read byte from ykemb
            byte = ykemb->ykemb_read_command(i2c_ykemb_addr, mem_addrH, mem_addrL);


            printf("\nByte read: 0x%x\n", byte);


        } else {
            //action = PRINT_HELP_YKEMB;
        }




            

    } else {
        //action = PRINT_HELP;
    }
}  





/*****************************************************************
 * Function: ykemb_write_command
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
int Ykemb::ykemb_write_command(unsigned char *i2c_ykemb_addr, unsigned char mem_addrH, unsigned char mem_addrL, unsigned char byte) {


    int error;



    //convert I2C address from char array to a byte
    char i2c = 4*i2c_ykemb_addr[2] + 2*i2c_ykemb_addr[1] + i2c_ykemb_addr[0];


    //populate hid_report2send
    hid_report_out[0] = 0;      //Windows requires require a byte with the report id.
                                //This is just for keep Windows "happy" it is not part
                                //of the actual command message/report sent to the USB device.
    hid_report_out[1] = 0x10;           //YKEMB scope
    hid_report_out[2] = 0x01;           //COMMAND type
    hid_report_out[3] = 0x01;           //WRITE command
    hid_report_out[4] = i2c;            //I2C device address
    hid_report_out[5] = mem_addrH;      //Memory address High byte
    hid_report_out[6] = mem_addrL;      //Memory address Low byte
    hid_report_out[7] = byte;           //Memory address Low byte

    //printf("\n\ni2c=%x\n\n",i2c); 

    error = sendHidReport(NULL, hid_report_out, hid_report_in);
    if(error){
        return error;
    }

    
    return 0;
}

 


Ykemb::Ykemb() {

}


/*****************************************************************
 * Function: ykemb_read_command
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
unsigned char Ykemb::ykemb_read_command(unsigned char *i2c_ykemb_addr, unsigned char mem_addrH, unsigned char mem_addrL) {
   
    int error;


    //convert I2C address from char array to a byte
    char i2c = 4*i2c_ykemb_addr[2] + 2*i2c_ykemb_addr[1] + i2c_ykemb_addr[0];


    //populate hid_report2send
    hid_report_out[0] = 0;      //Windows requires require a byte with the report id.
                                //This is just for keep Windows "happy" it is not part
                                //of the actual command message/report sent to the USB device.
    hid_report_out[1] = 0x10;           //YKEMB scope
    hid_report_out[2] = 0x01;           //COMMAND type
    hid_report_out[3] = 0x02;           //READ command
    hid_report_out[4] = i2c;            //I2C device address
    hid_report_out[5] = mem_addrH;      //Memory address High byte
    hid_report_out[6] = mem_addrL;      //Memory address Low byte


    error = sendHidReport(NULL, hid_report_out, hid_report_in);
    if(error){
        return error;
    }

    //process the response HID report with the read from the YKEMB
    /* 
    printf("\n\nhid_report_in[0]=0x%x\n",hid_report_in[0]);
    printf("hid_report_in[1]=0x%x\n",hid_report_in[1]);
    printf("hid_report_in[2]=0x%x\n",hid_report_in[2]);
    printf("hid_report_in[3]=0x%x\n",hid_report_in[3]);
    printf("hid_report_in[4]=0x%x\n",hid_report_in[4]);
    printf("hid_report_in[5]=0x%x\n",hid_report_in[5]);
    printf("hid_report_in[6]=0x%x\n\n",hid_report_in[6]);
    */

    return hid_report_in[6];    //return the byte read

}





/*****************************************************************
 * Function: ykemb_print_help
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
void Ykemb::print_help() {

    printf("\n\nYKEMB Command Structure:\n");
    printf("\nykam24cmd ykemb -<command_option> <i2c_device_address> 0x<mem_addr_H> 0x<mem_addr_L> 0x<byte_value>\n");
    printf("\nWhere:\n");
    printf("\ncommand_option\t: w -> write command; r -> read command\n");
    printf("\ni2c_device_address\t: YKEMB device I2C address in binary format (ex., 101)\n");
    printf("\nmem_addr_H\t: High byte of the memory address to be writen/read in hexadecimal format (ex., A2)\n");
    printf("\nmem_addr_L\t: Low byte of the memory address to be writen/read in hexadecimal format (ex., A2)\n");
    printf("\nbyte_value\t: Byte to be writen into memory in hexadecimal format. This option should only be used in Write commands\n");



}
   



