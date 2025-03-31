/**
 * USB_DEVICE_STACK Generated API Header File
 * 
 * @file usb_descriptors.h
 * 
 * @ingroup usb_device_stack
 * 
 * @brief Header file for example application descriptors.
 *
 * @version USB_DEVICE_STACK Driver Version 1.0.0
*/
/*
© [2025] Microchip Technology Inc. and its subsidiaries.

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

#ifndef USB_DESCRIPTORS_H
#define USB_DESCRIPTORS_H

#include <stddef.h>
#include <usb_protocol_headers.h>
#include "usb_config.h"

#include <usb_protocol_cdc.h>

/**
 * @ingroup usb_device_stack
 * @def LANG_EN_US
 * @brief Language ID String Descriptor, for English (US).
 */
#define LANG_EN_US 0x0409U

/**
 * @ingroup usb_device_stack
 * @def STRING_MANUFACTURER
 * @brief Manufacturer String descriptor.
 */
#define STRING_MANUFACTURER L"Microchip Technology Inc."

/**
 * @ingroup usb_device_stack
 * @def STRING_PRODUCT
 * @brief Product String descriptor.
 */
#define STRING_PRODUCT      L"CDC Class Demo"

/**
 * @ingroup usb_device_stack
 * @def STRING_SERIAL
 * @brief Serial Number String descriptor.
 */
#define STRING_SERIAL       L"1"

/**
 * @ingroup usb_device_stack
 * @struct USB_APPLICATION_CONFIGURATION1_struct
 * @brief USB Configuration, Interface and Endpoint descriptors for Config1.
 */
typedef struct USB_APPLICATION_CONFIGURATION1_struct
{
    USB_CONFIGURATION_DESCRIPTOR_t Configuration;
    USB_INTERFACE_DESCRIPTOR_t CDC_Communication_Interface;
    USB_CDC_HEADER_FUNCTIONAL_DESCRIPTOR_t CDC_Communication_Interface_Header;
    USB_CDC_ACM_FUNCTIONAL_DESCRIPTOR_t CDC_Communication_Interface_ACM;
    USB_CDC_UNION_FUNCTIONAL_DESCRIPTOR_t CDC_Communication_Interface_Union;
    USB_ENDPOINT_DESCRIPTOR_t CDC_Communication_Interface_Endpoint1IN;
    USB_INTERFACE_DESCRIPTOR_t CDC_Data_Interface;
    USB_ENDPOINT_DESCRIPTOR_t CDC_Data_Interface_Endpoint2IN;
    USB_ENDPOINT_DESCRIPTOR_t CDC_Data_Interface_Endpoint2OUT;
} USB_APPLICATION_CONFIGURATION1_t;

/**
 * @ingroup usb_device_stack
 * @struct USB_APPLICATION_CONFIGURATION_struct
 * @brief USB Configuration, Interface and Endpoint descriptors.
 */
typedef struct USB_APPLICATION_CONFIGURATION_struct
{
    USB_APPLICATION_CONFIGURATION1_t Config1;
} USB_APPLICATION_CONFIGURATION_t;

/**
 * @ingroup usb_device_stack
 * @struct USB_APPLICATION_STRING_DESCRIPTORS_struct
 * @brief USB String descriptors.
 */
typedef struct USB_APPLICATION_STRING_DESCRIPTORS_struct
{
    USB_DESCRIPTOR_HEADER_t manufacturer_header;
    wchar_t manufacturer[DESCRIPTOR_STRING_LENGTH(STRING_MANUFACTURER)];
    USB_DESCRIPTOR_HEADER_t product_header;
    wchar_t product[DESCRIPTOR_STRING_LENGTH(STRING_PRODUCT)];
    USB_DESCRIPTOR_HEADER_t serial_header;
    wchar_t serial[DESCRIPTOR_STRING_LENGTH(STRING_SERIAL)]; 
} USB_APPLICATION_STRING_DESCRIPTORS_t;

/**
 * @ingroup usb_device_stack
 * @struct descriptorPointers
 * @brief Pointers to the standard USB descriptors.
 */
extern USB_DESCRIPTOR_POINTERS_t descriptorPointers;


#endif // USB_DESCRIPTORS_H
/**
 End of File
*/
