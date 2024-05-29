/**
 * USBCOREREQUESTS USB Core Requests Header File
 * @file usb_core_requests.h
 * @defgroup usb_core_requests USB Core Requests
 * @ingroup usb_core
 * @brief USB Device Core Requests handling.
 * @version USB Device Core Version 1.0.0
 */

/*
    (c) 2021 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip software and any
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party
    license terms applicable to your use of third party software (including open source software) that
    may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
    FOR A PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
    SOFTWARE.
 */


#ifndef USB_CORE_REQUESTS_H
// cppcheck-suppress misra-c2012-2.5
#define	USB_CORE_REQUESTS_H

#include <stdbool.h>
#include <stdint.h>

#include <usb_core_requests_device.h>
#include <usb_core_requests_interface.h>
#include <usb_core_requests_endpoint.h>
#include <usb_protocol_headers.h>
#include <usb_common_elements.h>

/**
 * @ingroup usb_core_requests
 * @brief Setup function for the device requests
 *
 * USB 2.0 Specification Ch 9.4.
 * | bRequest          | wValue            | wIndex     | wLength | Data                |
 * |-------------------|-------------------|------------|---------|---------------------|
 * | CLEAR_FEATURE     | Feature selector  | Zero       | Zero    | None                |
 * | GET_CONFIGURATION | Zero              | Zero       | One     | Config value        |
 * | GET_DESCRIPTOR    | Type and index    | Zero or ID | Length  | Descriptor          |
 * | GET_STATUS        | Zero              | Endpoint   | Two     | Device status       |
 * | SET_ADDRESS       | Device address    | Zero       | Zero    | None                |
 * | SET_CONFIGURATION | Config value      | Zero       | Zero    | None                |
 * | SET_DESCRIPTOR    | Type and index    | Zero or ID | Length  | Descriptor          |
 * | SET_FEATURE       | Feature selector  | Zero       | Zero    | None                |
 *
 * @param setupRequestPtr - Pointer to the setup request and its data
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_SetupProcessDeviceRequest(USB_SETUP_REQUEST_t *setupRequestPtr);

/**
 * @ingroup usb_core_requests
 * @brief Setup function for the endpoint requests
 *
 * USB 2.0 Specification Ch. 9.4.
 * | bRequest      | wValue           | wIndex   | wLength | Data            |
 * |---------------|------------------|----------|---------|-----------------|
 * | CLEAR_FEATURE | Feature selector | Endpoint | Zero    | None            |
 * | GET_STATUS    | Zero             | Endpoint | Two     | Endpoint status |
 * | SET_FEATURE   | Feature selector | Endpoint | Zero    | None            |
 * | SYNCH_FRAME   | Zero             | Endpoint | Two     | Frame number    |
 *
 * @param *setupRequestPtr - Pointer to the request and its data
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_SetupProcessEndpointRequest(USB_SETUP_REQUEST_t *setupRequestPtr);

/**
 * @ingroup usb_core_requests
 * @brief Setup function for the interface requests
 *
 * USB 2.0 Specification Ch 9.4.
 * | bRequest        | wValue            | wIndex    | wLength | Data                |
 * |-----------------|-------------------|-----------|---------|---------------------|
 * | CLEAR_FEATURE   | Feature selector  | Interface | Zero    | None                |
 * | GET_INTERFACE   | Zero              | Interface | One     | Alternate interface |
 * | GET_STATUS      | Zero              | Interface | Two     | Interface           |
 * | SET_FEATURE     | Feature selector  | Interface | Zero    | None                |
 * | SET_INTERFACE   | Alternate setting | Interface | Zero    | None                |
 * | GET_DESCRIPTOR  | Type and index    | Zero      | Length  | Descriptor          |
 *
 * @param setupRequestPtr - Pointer to the setup request and its data
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_SetupProcessInterfaceRequest(USB_SETUP_REQUEST_t *setupRequestPtr);

#endif	/* USB_CORE_REQUESTS_H */

