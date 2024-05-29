/**
 * USBCOREEVENTS USB Core Events Header File
 * @file usb_core_events.h
 * @defgroup usb_core_events USB Core Events
 * @ingroup usb_core
 * @brief Event handling for the USB Core Stack.
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

#ifndef USB_CORE_EVENTS_H
// cppcheck-suppress misra-c2012-2.5
#define USB_CORE_EVENTS_H

#include <stdbool.h>
#include <stdint.h>

#include <usb_common_elements.h>

#include <usb_core_descriptors.h>
#include <usb_core_requests.h>
#include <usb_core_transfer.h>
#include <usb_peripheral.h>
#include <usb_protocol_headers.h>

/**
 * @ingroup usb_core
 * @struct USB_EVENT_HANDLERS_struct
 * @brief Represents the event callbacks, the configuration and the enumeration setups.
 */
typedef struct USB_EVENT_HANDLERS_struct
{
    USB_SETUP_EVENT_CALLBACK_t SetConfiguration;
    USB_SETUP_EVENT_CALLBACK_t SetInterface;
    USB_EVENT_CALLBACK_t InterfaceDisabled;
    USB_SETUP_PROCESS_CALLBACK_t VendorRequest;
    USB_SETUP_PROCESS_CALLBACK_t ClassRequest;
    USB_SETUP_PROCESS_CALLBACK_t OtherRequest;
    USB_EVENT_CALLBACK_t SOFCallback;
    USB_EVENT_CALLBACK_t ResetCallback;
    USB_EVENT_CALLBACK_t SuspendCallback;
    USB_EVENT_CALLBACK_t ResumeCallback;
} USB_EVENT_HANDLERS_t;

extern USB_EVENT_HANDLERS_t event;

/**
 * @ingroup usb_core
 * @brief Handles the different types of events.
 * @param None.
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */

RETURN_CODE_t USB_EventHandler(void);

/**
 * @ingroup usb_core
 * @brief Registers a callback for Set Configuration requests.
 * @param callback - Reference for the callback function
 * @return None.
 */
void USB_SetConfigurationCallbackRegister(USB_SETUP_EVENT_CALLBACK_t callback);

/**
 * @ingroup usb_core
 * @brief Registers a callback for Set Interface requests.
 * @param callback -  Reference for the callback function
 * @return None.
 */
void USB_SetInterfaceCallbackRegister(USB_SETUP_EVENT_CALLBACK_t callback);

/**
 * @ingroup usb_core
 * @brief Registers a callback for disabling interfaces.
 * @param callback - Reference for the callback function
 * @return None.
 */
void USB_InterfaceDisabledCallbackRegister(USB_EVENT_CALLBACK_t callback);

/**
 * @ingroup usb_core
 * @brief Registers a callback for vendor requests.
 * @param callback - Reference for the callback function
 * @return None.
 */
void USB_VendorRequestCallbackRegister(USB_SETUP_PROCESS_CALLBACK_t callback);

/**
 * @ingroup usb_core
 * @brief Registers a callback for class requests.
 * @param callback - Reference for the callback function
 * @return None.
 */
void USB_ClassRequestCallbackRegister(USB_SETUP_PROCESS_CALLBACK_t callback);

/**
 * @ingroup usb_core
 * @brief Registers a callback for other requests.
 * @param callback - Reference for the callback function
 * @return None.
 */
void USB_OtherRequestCallbackRegister(USB_SETUP_PROCESS_CALLBACK_t callback);

/**
 * @ingroup usb_core
 * @brief Registers a callback for Start-Of-Frame (SOF) events.
 * @param callback - Reference for the callback function
 * @return None.
 */
void USB_SOFCallbackRegister(USB_EVENT_CALLBACK_t callback);

/**
 * @ingroup usb_core
 * @brief Registers a callback for Reset events.
 * @param callback - Reference for the callback function
 * @return None.
 */
void USB_ResetCallbackRegister(USB_EVENT_CALLBACK_t callback);

/**
 * @ingroup usb_core
 * @brief Registers a callback for Suspend events.
 * @param callback - Reference for the callback function
 * @return None.
 */
void USB_SuspendCallbackRegister(USB_EVENT_CALLBACK_t callback);

/**
 * @ingroup usb_core
 * @brief Registers a callback for Resume events.
 * @param callback - Reference for the callback function
 * @return None.
 */
void USB_ResumeCallbackRegister(USB_EVENT_CALLBACK_t callback);

#endif /* USB_CORE_EVENTS_H */
