/**
 * USBCOREREQUESTSDEVICE USB Core Requests Device Header File
 * @file usb_core_requests_device.h
 * @ingroup usb_core_requests
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

#ifndef USB_CORE_REQUESTS_DEVICE_H
// cppcheck-suppress misra-c2012-2.5
#define	USB_CORE_REQUESTS_DEVICE_H

#include <stdbool.h>
#include <stdint.h>

#include "usb_protocol_headers.h"
#include "usb_common_elements.h"

/**
 * @ingroup usb_core_requests
 * @brief Returns the status of the device features.
 * @param None.
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t SetupDeviceRequestGetStatus(void);

/**
 * @ingroup usb_core_requests
 * @brief Clears the device feature.
 * @param *setupRequestPtr - Pointer to the setup request
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t SetupDeviceRequestClearFeature(USB_SETUP_REQUEST_t *setupRequestPtr);

/**
 * @ingroup usb_core_requests
 * @brief Sets the device feature.
 * @param *setupRequestPtr - Pointer to the setup request
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t SetupDeviceRequestSetFeature(USB_SETUP_REQUEST_t *setupRequestPtr);

/**
 * @ingroup usb_core_requests
 * @brief Sets the device address.
 * @param address - Address to be set
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t SetupDeviceRequestSetAddress(uint8_t address);

/**
 * @ingroup usb_core_requests
 * @brief Callback function for the address.
 * @param None.
 * @return None.
 */
void SetupDeviceAddressCallback(void);

/**
 * @ingroup usb_core_requests
 * @brief Gets the device descriptor.
 * @param *setupRequestPtr - Pointer to the setup request
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t SetupDeviceRequestGetDescriptor(USB_SETUP_REQUEST_t *setupRequestPtr);

/**
 * @ingroup usb_core_requests
 * @brief Gets the device configuration.
 * @param None.
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t SetupDeviceRequestGetConfiguration(void);

/**
 * @ingroup usb_core_requests
 * @brief Sets the device configuration.
 * @param configurationValue - Configuration value to be set
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t SetupDeviceRequestSetConfiguration(uint8_t configurationValue);

#endif	/* USB_CORE_REQUESTS_DEVICE_H */

