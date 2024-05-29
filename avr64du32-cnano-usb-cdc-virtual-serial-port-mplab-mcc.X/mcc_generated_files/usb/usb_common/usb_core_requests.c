/**
 * USBCOREREQUESTS USB Core Requests Source File
 * @file usb_core_requests.c
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

RETURN_CODE_t USB_SetupProcessDeviceRequest(USB_SETUP_REQUEST_t *setupRequestPtr)
{
    RETURN_CODE_t status = UNINITIALIZED;

    switch (setupRequestPtr->bRequest)
    {
    case USB_REQUEST_GET_STATUS:
    {
        status = SetupDeviceRequestGetStatus();
        break;
    }
    case USB_REQUEST_CLEAR_FEATURE:
    {
        status = SetupDeviceRequestClearFeature(setupRequestPtr);
        break;
    }
    case USB_REQUEST_SET_FEATURE:
    {
        status = SetupDeviceRequestSetFeature(setupRequestPtr);
        break;
    }
    case USB_REQUEST_SET_ADDRESS:
    {
        status = SetupDeviceRequestSetAddress((uint8_t)setupRequestPtr->wValue & 0xffu);
        break;
    }
    case USB_REQUEST_GET_DESCRIPTOR:
    {
        status = SetupDeviceRequestGetDescriptor(setupRequestPtr);
        break;
    }
    case USB_REQUEST_SET_DESCRIPTOR:
    {
        // Set Descriptor not supported, please STALL
        status = UNSUPPORTED;
        break;
    }
    case USB_REQUEST_GET_CONFIGURATION:
    {
        status = SetupDeviceRequestGetConfiguration();
        break;
    }
    case USB_REQUEST_SET_CONFIGURATION:
    {
        status = SetupDeviceRequestSetConfiguration((uint8_t)(setupRequestPtr->wValue & 0xffu));
        break;
    }
    default:
        // Invalid request, please STALL
        status = UNSUPPORTED;
        break;
    }

    return status;
}

RETURN_CODE_t USB_SetupProcessEndpointRequest(USB_SETUP_REQUEST_t *setupRequestPtr)
{
    RETURN_CODE_t status = UNINITIALIZED;

    // Gets the requested endpoint, endpoint address and its direction
    USB_PIPE_t endpoint = EndpointFromRequestGet(setupRequestPtr->wIndex);

    // Checks if the request is for a valid endpoint
    if (endpoint.address >= (uint8_t)USB_EP_NUM)
    {
        status = ENDPOINT_ADDRESS_ERROR;
    }
    else
    {
        // Handles the actual endpoint requests
        switch (setupRequestPtr->bRequest)
        {
        case USB_REQUEST_GET_STATUS:
        {
            status = SetupEndpointRequestGetStatus(setupRequestPtr);
            break;
        }
        case USB_REQUEST_CLEAR_FEATURE:
        {
            status = SetupEndpointRequestClearFeature(setupRequestPtr);
            break;
        }
        case USB_REQUEST_SET_FEATURE:
        {
            status = SetupEndpointRequestSetFeature(setupRequestPtr);
            break;
        }
        case USB_REQUEST_SYNCH_FRAME:
        {
            status = SetupEndpointRequestSynchFrame();
            break;
        }
        default:
            // Invalid request, please STALL
            status = UNSUPPORTED;
            break;
        }
    }

    return status;
}

RETURN_CODE_t USB_SetupProcessInterfaceRequest(USB_SETUP_REQUEST_t *setupRequestPtr)
{
    RETURN_CODE_t status = UNINITIALIZED;

    // Gets the requested interface number
    // Handles the actual interface requests
    switch (setupRequestPtr->bRequest)
    {
    case USB_REQUEST_GET_STATUS:
    {
        status = USB_SetupInterfaceRequestGetStatus();
        break;
    }
    case USB_REQUEST_CLEAR_FEATURE:
    {
        // Features are not specified for USB 2 interfaces, please STALL
        status = UNSUPPORTED;
        break;
    }
    case USB_REQUEST_SET_FEATURE:
    {
        // Features are not specified for USB 2 interfaces, please STALL
        status = UNSUPPORTED;
        break;
    }
    case USB_REQUEST_GET_INTERFACE:
    {
        status = USB_SetupInterfaceRequestGetInterface(setupRequestPtr);
        break;
    }
    case USB_REQUEST_SET_INTERFACE:
    {
        status = USB_SetupInterfaceRequestSetInterface(setupRequestPtr);
        break;
    }
    case USB_REQUEST_GET_DESCRIPTOR:
    {
        status = USB_SetupInterfaceRequestGetDescriptor(setupRequestPtr);
        break;
    }
    default:
        // Invalid request, please STALL
        status = UNSUPPORTED;
        break;
    }

    return status;
}
