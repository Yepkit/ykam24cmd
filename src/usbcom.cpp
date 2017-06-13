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


//-------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "stdafx.h"
#include "usbcom.h"


using namespace std;





/**************************************************************************
 * listDevices() - List YKUSH Devices Serial Number
 *-------------------------------------------------------------------------
 *
 * This function prints the iSerial of the
 * attached YKUSH devices.
 *
 **************************************************************************/
int Device::listConnected() {

    	// Enumerate and print the YKUSH devices on the system 
    	struct hid_device_info *devs, *cur_dev;

    	devs = hid_enumerate(0x0, 0x0);
    	if (devs == NULL) {
            if (handle == NULL){
                // No HID devices found
                printf("\nNo HID USB devices connected to this Host\n");
            }
    	}

    	cur_dev = devs;
    	while (cur_dev) {
        	if ((cur_dev->vendor_id == vid) && (cur_dev->product_id == pid)) {
            		printf("YKUSH device found with Serial Number: %ls", cur_dev->serial_number);
            		printf("\n");
            		printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
            		printf("  Product:      %ls\n", cur_dev->product_string);
            		printf("\n");
        	} else if ((cur_dev->vendor_id == vid) && (cur_dev->product_id == pid)) {
                    printf("YKUSH device found with Serial Number: %ls", cur_dev->serial_number);
            		printf("\n");
            		printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
            		printf("  Product:      %ls\n", cur_dev->product_string);
                    printf("  NOTE: This is an old version of the firmware. If you have access to a PIC programmer contact Yepkit to get the latest version of the firmware.");
            		printf("\n");
            }

        	cur_dev = cur_dev->next;
    	}
    	hid_free_enumeration(devs);
    
	return 0;
}






Device::Device() {
    pid = PRODUCT_ID;
    vid = VENDOR_ID;
}




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
int Device::sendHidReport(char *serial, unsigned char *msg, unsigned char *resp_msg) {
	
    const size_t newsize = 100;
	wchar_t cserial[newsize];
    int res;	

    
    if (serial) {
		// Convert to a wchar_t*
		size_t origsize = strlen(serial) + 1;
		size_t convertedChars = 0;

#ifndef LINUX
		mbstowcs_s(&convertedChars, cserial, origsize, serial, _TRUNCATE);
#else
		mbstowcs(cserial, serial, newsize);
#endif
	}

    
    // Open the USB device 
    handle = hid_open(vid, pid, serial ? cserial : NULL);
  
    if (handle == NULL) {
	    printf("\n\nERROR: Unable to open USB device\n");
        return -1;
    }

    // Set the hid_read() function to be blocking (wait for response from the device).
    hid_set_nonblocking(handle, 0);

    
    //send HID report
	res = hid_write(handle, msg, 65);

    if (res < 0) {
	    printf("\n\nERROR: Unable to write HID report to USB device\n");
        return -1;
	}

    //read HID report
    res = hid_read(handle, resp_msg, 65);

    if (res < 0) {
	    printf("\n\nERROR: Unable to read HID report to USB device\n");
        return -1;
	}


   return 0;    //OK 

}










