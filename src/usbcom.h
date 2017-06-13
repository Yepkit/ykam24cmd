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


#ifndef USBCOM_H
#define USBCOM_H



#ifndef LINUX
	#include <hidapi.h>
#else
	#include <hidapi.h>
#endif





//-------------------------------------------------------------------------
// DEFINES
//-------------------------------------------------------------------------
#define VERSION "0.1.0"
#define VENDOR_ID 0x04D8
#define PRODUCT_ID 0xF25C           //YKAMELEAN24




/**********************************************************
 *
 *                  CLASSES
 *
 **********************************************************/
class Device {

    public:

        Device();

        int sendHidReport(char *serial, unsigned char *msg, unsigned char *resp_msg);

        int listConnected();    //List connected devices


    private:

        unsigned short vid;       
        unsigned short pid;      //Ykamelean24 product id

        hid_device *handle;

};



/*****************************************************************
 * Function: 
 *
 *  send_usb_msg
 *
 *
 * Description:
 *
 *  Sends HID report with the data provided in the input buffer
 *  "msg". 
 *
 *
 * Inputs:
 *
 *      serial      -   target usb device serial number string
 *
 *      msg         -   message (HID report) to be sent
 *
 *      resp_msg    -   response message (HID report) received
 *
 *
 * Outputs:
 *
 *  The function returns the following value.
 *      0   -   No error
 *      -1  -   Error
 *
 *  In the case of error, a message is printed into the standard
 *  output.
 *
 *
 * Precedences: 
 *
 *  Requires that VENDOR_ID and PRODUCT_ID constants are defined.
 *
 *
 *****************************************************************/
int send_usb_msg(char *serial, char *msg, char *resp_msg); 




char commands(char *cmd, char *resp, int num);
char command(char cmd);

char commandsBySerial(char *iSerial, char *cmd, char *resp, int num);
char commandBySerial(char *iSerial, char cmd);

int listDevices();


#endif // USBCOM_H
