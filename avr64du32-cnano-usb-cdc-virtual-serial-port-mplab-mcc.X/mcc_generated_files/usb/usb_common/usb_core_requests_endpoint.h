/**
 * USBCOREREQUESTSENDPOINT USB Core Requests Endpoint Header File
 * @file usb_core_requests_endpoint.h
 * @ingroup usb_core_requests
 * @brief USB Endpoint Core Requests handling.
 * @version USB Device Core Version USB 1.0.0
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


#ifndef USB_CORE_REQUESTS_ENDPOINT_H
// cppcheck-suppress misra-c2012-2.5
#define	USB_CORE_REQUESTS_ENDPOINT_H

#include <stdbool.h>
#include <stdint.h>

#include "usb_protocol_headers.h"
#include "usb_common_elements.h"

/**
 * @ingroup usb_core_requests
 * @brief Gets the endpoint status.
 * @param wIndex - Endpoint address and direction
 * @return A structure with the endpoint status
 */
USB_PIPE_t EndpointFromRequestGet(uint16_t wIndex);

/**
 * @ingroup usb_core_requests
 * @brief Gets the endpoint status.
 * @param *setupRequestPtr - Pointer to the setup request
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t SetupEndpointRequestGetStatus(USB_SETUP_REQUEST_t *setupRequestPtr);

/**
 * @ingroup usb_core_requests
 * @brief Clears the endpoint feature.
 * @param *setupRequestPtr - Pointer to the setup request
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t SetupEndpointRequestClearFeature(USB_SETUP_REQUEST_t *setupRequestPtr);

/**
 * @ingroup usb_core_requests
 * @brief Sets the endpoint feature.
 * @param *setupRequestPtr - Pointer to the setup request
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t SetupEndpointRequestSetFeature(USB_SETUP_REQUEST_t *setupRequestPtr);

/**
 * @ingroup usb_core_requests
 * @brief Gets the current frame number.
 * @param None.
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t SetupEndpointRequestSynchFrame(void);

#endif	/* USB_CORE_REQUESTS_ENDPOINT_H */

