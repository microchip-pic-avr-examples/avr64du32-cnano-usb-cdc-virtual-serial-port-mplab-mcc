/**
 * USBCOREREQUESTSDEVICE USB Core Requests Device Core File
 * @file usb_core_requests_device.c
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

#include <usb_core_requests_device.h>
#include <usb_common_elements.h>
#include <usb_protocol_headers.h>
#include <usb_config.h>
#include <usb_peripheral.h>
#include <usb_core.h>
#include <usb_core_descriptors.h>

STATIC uint8_t deviceAddress = 0;

RETURN_CODE_t SetupDeviceRequestGetStatus(void)
{
    // Return IN transaction with Remote Wake-up and Self Powered.
    uint8_t data[] = {0, 0};

   if (USB_DescriptorActiveConfigurationSelfPoweredGet())
   {
       data[0] |= USB_REQUEST_DEVICE_SELF_POWERED;
   }
   if (USB_DescriptorActiveConfigurationRemoteWakeupGet())
   {
       data[0] |= USB_REQUEST_DEVICE_REMOTE_WAKEUP;
   }

    return USB_ControlTransferDataWriteBuffer(data, sizeof(data));
}

RETURN_CODE_t SetupDeviceRequestClearFeature(USB_SETUP_REQUEST_t *setupRequestPtr)
{
    RETURN_CODE_t status = UNINITIALIZED;

    // Clear feature for DEVICE_REMOTE_WAKEUP and TEST_MODE not yet supported
    (void)setupRequestPtr;

    return status;
}

RETURN_CODE_t SetupDeviceRequestSetFeature(USB_SETUP_REQUEST_t *setupRequestPtr)
{
    RETURN_CODE_t status = UNINITIALIZED;

    // Set feature for DEVICE_REMOTE_WAKEUP and TEST_MODE not yet supported
    (void)setupRequestPtr;

    return status;
}

RETURN_CODE_t SetupDeviceRequestSetAddress(uint8_t address)
{
    // Must register the callback here since device address must be set after completion of status stage.
    deviceAddress = address;
    USB_ControlEndOfRequestCallbackRegister(&SetupDeviceAddressCallback);

    return SUCCESS;
}

void SetupDeviceAddressCallback(void)
{
    USB_DeviceAddressConfigure(deviceAddress);
    USB_ControlEndOfRequestCallbackRegister(NULL);
}

RETURN_CODE_t SetupDeviceRequestGetDescriptor(USB_SETUP_REQUEST_t *setupRequestPtr)
{
    RETURN_CODE_t status = UNINITIALIZED;

    uint8_t descriptorType = (uint8_t)(setupRequestPtr->wValue >> 8u);
    uint8_t descriptorIndex = (uint8_t)(setupRequestPtr->wValue & 0xffu);

    if (USB_DESCRIPTOR_TYPE_VENDOR <= (USB_DESCRIPTOR_TYPE_t)descriptorType)
    {
       // Vendor Get_Descriptor Requests handled by VendorRequest callback.
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
        // Class Get_Descriptor Requests handled by ClassRequest callback.
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
        uint8_t *descriptorPtr = NULL;
        uint16_t descriptorLength = 0;

        if (USB_DESCRIPTOR_TYPE_STRING == (USB_DESCRIPTOR_TYPE_t)descriptorType)
        {
            status = USB_DescriptorStringPointerGet(descriptorIndex, setupRequestPtr->wIndex, &descriptorPtr, &descriptorLength);
        }
        else
        {
            // USB_DescriptorPointerGet will handle remaining invalid descriptorTypes.
            status = USB_DescriptorPointerGet(descriptorType, descriptorIndex, &descriptorPtr, &descriptorLength);
        }

        if (SUCCESS == status)
        {
            if (descriptorLength > setupRequestPtr->wLength)
            {
                descriptorLength = setupRequestPtr->wLength;
            }

            status = USB_ControlTransferDataSet(descriptorPtr, descriptorLength);
        }
    }

    return status;
}

RETURN_CODE_t SetupDeviceRequestGetConfiguration(void)
{
    uint8_t configurationValue = USB_DescriptorActiveConfigurationValueGet();

    return USB_ControlTransferDataWriteBuffer(&configurationValue, sizeof(configurationValue));
}

RETURN_CODE_t SetupDeviceRequestSetConfiguration(uint8_t configurationValue)
{
    RETURN_CODE_t status = UNINITIALIZED;

    if ((deviceAddress == 0u))
    {
        status = USB_CONNECTION_ERROR;
    }
    else
    {
        // Enables configuration, clears it if configurationValue is zero.
        status = USB_DescriptorConfigurationEnable(configurationValue);
    }

    return status;
}
