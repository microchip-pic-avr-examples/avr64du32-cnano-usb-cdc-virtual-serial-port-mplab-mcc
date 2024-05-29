/**
 * USBCOREREQUESTSINTERFACE USB Core Requests Interface Header File
 * @file usb_core_requests_interface.h
 * @ingroup usb_core_requests
 * @brief USB Interface Core Requests handling.
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


#ifndef USB_CORE_REQUESTS_INTERFACE_H
// cppcheck-suppress misra-c2012-2.5
#define	USB_CORE_REQUESTS_INTERFACE_H

#include <stdbool.h>
#include <stdint.h>

#include "usb_protocol_headers.h"
#include "usb_common_elements.h"

/**
 * @ingroup usb_core_requests
 * @brief Returns status for the specified interface.
 *
 * Get status from interface request according to USB 2.0 specification Ch. 9.4.5.
 * | bRequest   | wValue | wIndex      | wLength | Data      |
 * |------------|--------|-------------|---------|-----------|
 * | GET_STATUS | Zero   |  Interface  | Two     | Interface |
 *
 * @param None.
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_SetupInterfaceRequestGetStatus(void);

/**
 * @ingroup usb_core_requests
 * @brief Returns the alternate setting for the specified interface.
 *
 * Format for GET_INTERFACE request according to USB 2.0 specification Ch 9.4.4.
 * Document: Universal Serial Bus Specification for USB 2.0.
 * | bRequest      | wValue | wIndex    | wLength | Data              |
 * |---------------|--------|-----------|---------|-------------------|
 * | GET_INTERFACE | Zero   | Interface | One     | Alternate setting |
 *
 * @param *setupRequestPtr - Pointer to the request and its data
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_SetupInterfaceRequestGetInterface(USB_SETUP_REQUEST_t *setupRequestPtr);

/**
 * @ingroup usb_core_requests
 * @brief Setup function for the interface request to select the alternate setting.
 *
 * A request to set interface according to USB 2.0 specification Ch. 9.4.10.
 * Document: Universal Serial Bus Specification for USB 2.0
 * | bRequest      | wValue            | wIndex    | wLength | Data |
 * |---------------|-------------------|-----------|---------|------|
 * | SET_INTERFACE | Alternate setting | Interface | Zero    | None |
 *
 * @param *setupRequestPtr - Pointer to the request and its data
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_SetupInterfaceRequestSetInterface(USB_SETUP_REQUEST_t *setupRequestPtr);

/**
 * @ingroup usb_core_requests
 * @brief Setup function for the interface request for class-specific descriptors.
 *
 * | bRequest       | wValue            | wIndex    | wLength | Data       |
 * |----------------|-------------------|-----------|---------|------------|
 * | GET_DESCRIPTOR | Type and index    | Zero      | Length  | Descriptor |
 *
 * @param *setupRequestPtr - Pointer to the request and its data
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_SetupInterfaceRequestGetDescriptor(USB_SETUP_REQUEST_t *setupRequestPtr);

#endif	/* USB_CORE_REQUESTS_INTERFACE_H */

