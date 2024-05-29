/**
 * USB_DEVICE_STACK Generated API Header File
 * 
 * @file usb_device.h
 * 
 * @ingroup usb_device_stack
 * 
 * @brief Header file for the USB device setup.
 *
 * @version USB_DEVICE_STACK Driver Version 1.0.0
*/
/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef USB_DEVICE_H
#define USB_DEVICE_H

#include <usb_common_elements.h>
#include "usb_descriptors.h"

/**
 * @ingroup usb_device_stack
 * @brief Initializes the USB device.
 * @param None.
 * @return None.
 */ 
void USBDevice_Initialize(void);

/**
 * @ingroup usb_device_stack
 * @brief Handles the USB stack events and in progress transfers for the USB stack to function.
 * @param None.
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USBDevice_Handle(void);

/**
 * @ingroup usb_device_stack
 * @brief Returns the status of the USB device.
 * @param None.
 * @return USB status code
 */ 
RETURN_CODE_t USBDevice_StatusGet(void);

#endif // USB_DEVICE_H
/**
 End of File
*/
