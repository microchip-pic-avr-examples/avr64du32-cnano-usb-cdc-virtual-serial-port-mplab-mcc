/**
 * USBCORE CORE Header File
 * @file usb_core.h
 * @defgroup usb_core USB Core Layer
 * @brief Core functionality for the USB stack.
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

#ifndef USB_CORE_H
// cppcheck-suppress misra-c2012-2.5
#define USB_CORE_H

#include <stdbool.h>
#include <stdint.h>

#include <usb_common_elements.h>
#include <usb_core_events.h>
#include <usb_core_transfer.h>
#include <usb_protocol_headers.h>

/**
 * @ingroup usb_core
 * @brief Setup function for the Standard Device Request USB 2.0 Specification Ch 9.4.
 * | bRequest          | wValue                                | wIndex                  | wLength           | Data                                |
 * |-------------------|---------------------------------------|-------------------------|-------------------|-------------------------------------|
 * | CLEAR_FEATURE     | Feature Selector                      | Zero                    | None              |                                     |
 * | CLEAR_FEATURE     | Feature Selector                      | Interface               | None              |                                     |
 * | CLEAR_FEATURE     | Feature Selector                      | Endpoint                | None              |                                     |
 * | GET_CONFIGURATION | Zero                                  | Zero                    | One               | Configuration Value                 |
 * | GET_DESCRIPTOR    | Descriptor type and  Descriptor index | Zero or  Language ID    | Descriptor Length | Descriptor                          |
 * | GET_INTERFACE     | Zero                                  | Interface               | One               | Alternate Interface                 |
 * | GET_STATUS        | Zero                                  | Zero Interface Endpoint | Two               | Device status                       |
 * | GET_STATUS        | Zero                                  | Interface               | Two               | Interface  Status                   |
 * | GET_STATUS        | Zero                                  | Endpoint                | Two               | Endpoint Status                     |
 * | SET_ADDRESS       | Device Address                        | Zero                    | Zero              | None                                |
 * | SET_CONFIGURATION | Configuration Value                   | Zero                    | Zero              | None                                |
 * | SET_DESCRIPTOR    | Descriptor type and  Descriptor index | Zero or Language ID     | Descriptor Length | Descriptor                          |
 * | SET_FEATURE       | Feature Selector                      | Zero Interface Endpoint | Zero              | None                                |
 * | SET_FEATURE       | Feature Selector                      | Interface               | Zero              |                                     |
 * | SET_FEATURE       | Feature Selector                      | Endpoint                | Zero              |                                     |
 * | SET_INTERFACE     | Alternate Setting                     | Interface               | Zero              | None                                |
 * | SYNCH_FRAME       | Zero                                  | Endpoint                | Two               | Frame Number                        |
 * @param *setupRequestPtr - Pointer to the setup request and its data
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_SetupProcess(USB_SETUP_REQUEST_t *setupRequestPtr);

/**
 * @ingroup usb_core
 * @brief Starts the USB peripheral, configures the callbacks and attaches it to the bus.
 * @param None.
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_Start(void);

/**
 * @ingroup usb_core
 * @brief Stops the USB peripheral and detaches it from the bus.
 * @param None.
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_Stop(void);

/**
 * @ingroup usb_core
 * @brief Resets the USB peripheral.
 * @param None.
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_Reset(void);

#endif /* USB_CORE_H */
