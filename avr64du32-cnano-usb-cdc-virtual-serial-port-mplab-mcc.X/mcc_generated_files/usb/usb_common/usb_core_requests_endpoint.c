/**
 * USBCOREREQUESTSENDPOINT USB Core Requests Endpoint Source  File
 * @file usb_core_requests_endpoint.c
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

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include <usb_core_requests.h>
#include <usb_common_elements.h>
#include <usb_protocol_headers.h>
#include <usb_config.h>
#include <usb_peripheral.h>
#include <usb_core.h>
#include <usb_core_transfer.h>

/**
 * @ingroup usb_core_requests
 * @def GET_STATUS_ENDPOINT_STALLED
 * @brief Mask for the endpoint stall status in the first byte of the data stage of the setup request.
 */
#define GET_STATUS_ENDPOINT_STALLED (1u << 0u)

/**
 * @ingroup usb_core_requests
 * @def ENDPOINT_ADDRESS_MASK
 * @brief Mask for the endpoint address in the wIndex field of the setup request.
 */
#define ENDPOINT_ADDRESS_MASK (0x7fu)

/**
 * @ingroup usb_core_requests
 * @def ENDPOINT_DIRECTION_BITPOSITION
 * @brief Bit position for the endpoint direction in the wIndex field of the setup request.
 */
#define ENDPOINT_DIRECTION_BITPOSITION (7u)

USB_PIPE_t EndpointFromRequestGet(uint16_t wIndex)
{
    USB_PIPE_t endpoint;
    endpoint.address = (uint8_t)wIndex & ENDPOINT_ADDRESS_MASK;
    endpoint.direction = (uint8_t)wIndex >> ENDPOINT_DIRECTION_BITPOSITION;

    return endpoint;
}

RETURN_CODE_t SetupEndpointRequestGetStatus(USB_SETUP_REQUEST_t *setupRequestPtr)
{
    // Return IN transaction with ENDPOINT_HALT status (2 bytes)
    USB_PIPE_t endpoint = EndpointFromRequestGet(setupRequestPtr->wIndex);

    uint8_t data[] = {0, 0};
    if (USB_EndpointIsStalled(endpoint) == true)
    {

        data[0] |= GET_STATUS_ENDPOINT_STALLED;
    }

    return USB_ControlTransferDataWriteBuffer(data, sizeof (data));
}

RETURN_CODE_t SetupEndpointRequestClearFeature(USB_SETUP_REQUEST_t *setupRequestPtr)
{
    RETURN_CODE_t status = UNINITIALIZED;

    // Only ENDPOINT_HALT available for endpoints
    if (setupRequestPtr->wValue == USB_ENDPOINT_FEATURE_HALT)
    {
        USB_PIPE_t endpoint = EndpointFromRequestGet(setupRequestPtr->wIndex);

        status = USB_EndpointStallClear(endpoint);
    }
    else
    {
        status = UNSUPPORTED;
    }

    return status;
}

RETURN_CODE_t SetupEndpointRequestSetFeature(USB_SETUP_REQUEST_t *setupRequestPtr)
{
    RETURN_CODE_t status = UNINITIALIZED;

    // Only ENDPOINT_HALT available for endpoints
    if (setupRequestPtr->wValue == USB_ENDPOINT_FEATURE_HALT)
    {
        USB_PIPE_t endpoint = EndpointFromRequestGet(setupRequestPtr->wIndex);

        status = USB_TransferAbort(endpoint);
        if (SUCCESS == status)
        {
            status = USB_EndpointStall(endpoint);
        }
    }
    else
    {
        status = UNSUPPORTED;
    }

    return status;
}

RETURN_CODE_t SetupEndpointRequestSynchFrame(void)
{
    uint16_t framenum = USB_FrameNumberGet();

    return USB_ControlTransferDataWriteBuffer((uint8_t*) & framenum, sizeof (framenum));
}
