/**
 * USB_DEVICE_STACK Generated Driver File
 * 
 * @file usb_device.c
 * 
 * @ingroup usb_device_stack
 * 
 * @brief Driver implementation file for the USB device setup.
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

#include <usb_core.h>
#include <usb_cdc_virtual_serial_port.h>
#include "usb_device.h"
#include "usb0.h"

static RETURN_CODE_t usbStatus;
static void USBDevice_TransferHandler(void);
static void USBDevice_EventHandler(void);

void USBDevice_Initialize(void)
{
    USB_DescriptorPointersSet(&descriptorPointers);
    
    USB_CDCVirtualSerialPortInitialize();

    USB0_TrnComplCallbackRegister(USBDevice_TransferHandler);
    USB0_BusEventCallbackRegister(USBDevice_EventHandler);

    usbStatus = USB_Start();
}

RETURN_CODE_t USBDevice_Handle(void)
{
    if (usbStatus == SUCCESS)
    {
        usbStatus = USB_TransferHandler();
    }
    if (usbStatus == SUCCESS)
    {
        usbStatus = USB_EventHandler();
    }
    return usbStatus;
}

RETURN_CODE_t USBDevice_StatusGet(void)
{
    return usbStatus;
}

static void USBDevice_TransferHandler(void)
{
    usbStatus = USB_TransferHandler();
}

static void USBDevice_EventHandler(void)
{
    usbStatus = USB_EventHandler();
}

/**
 End of File
*/
