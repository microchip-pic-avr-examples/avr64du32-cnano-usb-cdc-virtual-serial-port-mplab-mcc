/**
 * USBCOREREQUESTSINTERFACE USB Core Requests Interface Source File
 * @file usb_core_requests_interface.c
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

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include <usb_core_requests_interface.h>
#include <usb_common_elements.h>
#include <usb_protocol_headers.h>
#include <usb_config.h>
#include <usb_peripheral.h>
#include <usb_core.h>
#include <usb_core_events.h>

/**
 * @ingroup usb_core_requests
 * @def GET_INTERFACE_REQUEST_NUMBER_MASK
 * @brief Mask for the interface number in the wIndex field of the setup request.
 */
#define GET_INTERFACE_REQUEST_NUMBER_MASK (0xffu)

/**
 * @ingroup usb_core_requests
 * @def GET_INTERFACE_REQUEST_WVALUE
 * @brief Value for the wValue field of the setup request.
 */
#define GET_INTERFACE_REQUEST_WVALUE 0u

/**
 * @ingroup usb_core_requests
 * @def GET_INTERFACE_RESPONSE_SIZE
 * @brief Size of the response to the Get Interface request.
 */
#define GET_INTERFACE_RESPONSE_SIZE 1u

RETURN_CODE_t USB_SetupInterfaceRequestGetStatus(void)
{
    uint8_t data[] = {0, 0};

    return USB_ControlTransferDataWriteBuffer(data, sizeof (data));
}

RETURN_CODE_t USB_SetupInterfaceRequestGetInterface(USB_SETUP_REQUEST_t *setupRequestPtr)
{
    RETURN_CODE_t status = UNINITIALIZED;

    if ((GET_INTERFACE_REQUEST_WVALUE == setupRequestPtr->wValue) && (GET_INTERFACE_RESPONSE_SIZE == setupRequestPtr->wLength))
    {
        uint8_t alternateSetting;
        status = ActiveAlternateSettingGet((GET_INTERFACE_REQUEST_NUMBER_MASK & setupRequestPtr->wIndex), &alternateSetting);
        if (SUCCESS == status)
        {
            status = USB_ControlTransferDataWriteBuffer(&alternateSetting, sizeof(alternateSetting));
        }
    }
    else
    {
        status = INTERFACE_GET_ERROR;
    }

    return status;
}

RETURN_CODE_t USB_SetupInterfaceRequestSetInterface(USB_SETUP_REQUEST_t *setupRequestPtr)
{
    RETURN_CODE_t status = USB_DescriptorInterfaceConfigure(setupRequestPtr->wIndex, setupRequestPtr->wValue, true);
    if (SUCCESS == status)
    {
        if (NULL != event.SetInterface)
        {
            event.SetInterface(setupRequestPtr);
        }
    }

    return status;
}

RETURN_CODE_t USB_SetupInterfaceRequestGetDescriptor(USB_SETUP_REQUEST_t *setupRequestPtr)
{
    RETURN_CODE_t status = UNINITIALIZED;

    uint8_t descriptorType = (uint8_t)(setupRequestPtr->wValue >> 8u);

    if (USB_DESCRIPTOR_TYPE_VENDOR <= (USB_DESCRIPTOR_TYPE_t)descriptorType)
    {
        // Vendor Get_Descriptor Requests handled by VendorRequest callback
        if (NULL != event.VendorRequest)
        {
            status = event.VendorRequest(setupRequestPtr);
        }
        else
        {
            status = UNSUPPORTED;
        }
    }
    else if (USB_DESCRIPTOR_TYPE_CLASS <= (USB_DESCRIPTOR_TYPE_t)descriptorType)
    {
        // Class Get_Descriptor Requests handled by ClassRequest callback
        if (NULL != event.ClassRequest)
        {
            status = event.ClassRequest(setupRequestPtr);
        }
        else
        {
            status = UNSUPPORTED;
        }
    }
    else
    {
        // Standard descriptor types not supported on interface requests
        status = UNSUPPORTED;
    }

    return status;
}