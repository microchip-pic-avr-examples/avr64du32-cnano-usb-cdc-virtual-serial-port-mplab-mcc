/**
 * USBCOREDESCRIPTOR Core Descriptors Source File
 * @file usb_core_descriptors.h
 * @ingroup usb_core_descriptors
 * @brief descriptors for the USB Core Stack.
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
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <usb_common_elements.h>
#include <usb_config.h>
#include <usb_core.h>
#include <usb_core_descriptors.h>
#include <usb_core_events.h>
#include <usb_peripheral.h>
#include <usb_protocol_headers.h>

/**
 * @ingroup usb_core_descriptors
 * @def USB_DEFAULT_INTERFACE
 * @brief Default interface number.
 */
#define USB_DEFAULT_INTERFACE 0u

/**
 * @ingroup usb_core_descriptors
 * @def USB_DEFAULT_ALTERNATE_SETTING
 * @brief Default alternate setting.
 */
#define USB_DEFAULT_ALTERNATE_SETTING 0u

/**
 * @ingroup usb_core_descriptors
 * @def USB_DESCRIPTOR_SEARCH_LIMIT
 * @brief The number of descriptors NextDescriptorPointerGet will search through before returning an error.
 */
#define USB_DESCRIPTOR_SEARCH_LIMIT 30u

/**
 * @typedef  USB_DESCRIPTOR_PTR_t
 * @brief Union of a uint8_t pointer and pointers to the different descriptor types.
 * @misradeviation{@advisory,19.2} Needed for the stack to parse through the configuration descriptors
 * without pointer casting between the different descriptor types and uint8_t.
 */
// cppcheck-suppress misra-c2012-19.2
typedef union USB_DESCRIPTOR_PTR_union
{
    uint8_t *bytePtr;
    USB_DESCRIPTOR_HEADER_t *headerPtr;
    USB_ENDPOINT_DESCRIPTOR_t *endpointPtr;
    USB_INTERFACE_DESCRIPTOR_t *interfacePtr;
    USB_CONFIGURATION_DESCRIPTOR_t *configurationPtr;
} USB_DESCRIPTOR_PTR_t;


STATIC USB_CONFIGURATION_DESCRIPTOR_t *activeConfigurationPtr = NULL;
STATIC uint8_t activeInterfaces[USB_INTERFACE_NUM];
STATIC USB_DESCRIPTOR_POINTERS_t *applicationPointers = NULL;

RETURN_CODE_t USB_DescriptorPointersSet(USB_DESCRIPTOR_POINTERS_t *descriptorPointersPtr)
{
    RETURN_CODE_t status = UNINITIALIZED;

    if (NULL != descriptorPointersPtr)
    {
        // Checks that the device pointer is pointing to a struct with the device type.
        if ((NULL == descriptorPointersPtr->devicePtr) || (USB_DESCRIPTOR_TYPE_DEVICE != (USB_DESCRIPTOR_TYPE_t)descriptorPointersPtr->devicePtr->header.bDescriptorType))
        {
            status = DESCRIPTOR_POINTER_ERROR;
        }
        // Checks that the first configuration pointer is pointing to a struct with the configuration type.
        else if ((NULL == descriptorPointersPtr->configurationsPtr) || (USB_DESCRIPTOR_TYPE_CONFIGURATION != (USB_DESCRIPTOR_TYPE_t)descriptorPointersPtr->configurationsPtr->header.bDescriptorType))
        {
            status = DESCRIPTOR_POINTER_ERROR;
        }
        else
        {
            status = SUCCESS;
        }
    }
    else
    {
        status = DESCRIPTOR_POINTER_ERROR;
    }

    if (SUCCESS == status)
    {
        // Saves the pointer structure address.
        applicationPointers = descriptorPointersPtr;
    }

    return status;
}

RETURN_CODE_t USB_DescriptorConfigurationEnable(uint8_t configurationValue)
{
    RETURN_CODE_t status = UNINITIALIZED;

    // Descriptor pointer to search through the different descriptors
    // cppcheck-suppress misra-c2012-19.2
    USB_DESCRIPTOR_PTR_t currentDescriptor;

    if (NULL == applicationPointers)
    {
        status = DESCRIPTOR_POINTER_ERROR;
    }
    else
    {
        if (NULL != activeConfigurationPtr)
        {
            status = SUCCESS;

            // Find and disable all active interfaces in the current configuration
            currentDescriptor.configurationPtr = activeConfigurationPtr;
            uint8_t numInterfaces = activeConfigurationPtr->bNumInterfaces;
            while ((SUCCESS == status) && (numInterfaces > 0u))
            {
                status = NextDescriptorPointerGet(USB_DESCRIPTOR_TYPE_INTERFACE, &currentDescriptor.headerPtr);

                if (SUCCESS == status)
                {
                    if (activeInterfaces[currentDescriptor.interfacePtr->bInterfaceNumber] == currentDescriptor.interfacePtr->bAlternateSetting)
                    {
                        status = USB_DescriptorInterfaceConfigure(currentDescriptor.interfacePtr->bInterfaceNumber, USB_DEFAULT_ALTERNATE_SETTING, false);
                        numInterfaces--;
                    }
                }
            }
        }
        else
        {
            // No current configuration, nothing to disable
            status = SUCCESS;
        }

        if (SUCCESS == status)
        {
            if (USB_REQUEST_DEVICE_DISABLE_CONFIGURATION == configurationValue)
            {
                // Active configuration is disabled, so clear pointer
                activeConfigurationPtr = NULL;
            }
            else
            {
                // Get new configuration pointer and enable its interfaces
                status = ConfigurationPointerGet(configurationValue, &activeConfigurationPtr);

                if (SUCCESS == status)
                {
                    // Find and enable all interfaces in the set configuration with bAlternateSetting == 0
                    currentDescriptor.configurationPtr = activeConfigurationPtr;
                    uint8_t numInterfaces = activeConfigurationPtr->bNumInterfaces;
                    while ((SUCCESS == status) && (numInterfaces > 0u))
                    {
                        status = NextDescriptorPointerGet(USB_DESCRIPTOR_TYPE_INTERFACE, &currentDescriptor.headerPtr);
                        if (SUCCESS == status)
                        {
                            if (USB_DEFAULT_ALTERNATE_SETTING == currentDescriptor.interfacePtr->bAlternateSetting)
                            {
                                status = USB_DescriptorInterfaceConfigure(currentDescriptor.interfacePtr->bInterfaceNumber, USB_DEFAULT_ALTERNATE_SETTING, true);
                                numInterfaces--;
                            }
                        }
                    }
                }
            }
        }
    }

    return status;
}

uint8_t USB_DescriptorActiveConfigurationValueGet(void)
{
    uint8_t configurationValue = USB_REQUEST_DEVICE_DISABLE_CONFIGURATION;

    if (NULL != activeConfigurationPtr)
    {
        configurationValue = activeConfigurationPtr->bConfigurationValue;
    }

    return configurationValue;
}

bool USB_DescriptorActiveConfigurationSelfPoweredGet(void)
{
    return (activeConfigurationPtr->bmAttributes & USB_CONFIG_ATTR_SELF_POWERED) == USB_CONFIG_ATTR_SELF_POWERED;
}

bool USB_DescriptorActiveConfigurationRemoteWakeupGet(void)
{
    return (activeConfigurationPtr->bmAttributes & USB_CONFIG_ATTR_REMOTE_WAKEUP) == USB_CONFIG_ATTR_REMOTE_WAKEUP;
}

RETURN_CODE_t ConfigurationPointerGet(uint8_t configurationValue, USB_CONFIGURATION_DESCRIPTOR_t **configurationPtr)
{
    RETURN_CODE_t status = UNINITIALIZED;

    // Checks if the requested configuration is an existing configuration.
    if (configurationValue > applicationPointers->devicePtr->bNumConfigurations)
    {
        status = DESCRIPTOR_CONFIGURATIONS_ERROR;
    }
    else
    {
        // If there is only one configuration, return the pointer to the configuration.
        if (1u == applicationPointers->devicePtr->bNumConfigurations)
        {
            *configurationPtr = applicationPointers->configurationsPtr;
            status = SUCCESS;
        }
        else
        {
            // Pointer initialized to the address of the first configuration descriptor.
            // cppcheck-suppress misra-c2012-19.2
            USB_DESCRIPTOR_PTR_t currentDescriptor = { .configurationPtr = applicationPointers->configurationsPtr };

            uint8_t i = applicationPointers->devicePtr->bNumConfigurations;
            while (i-- > 0u)
            {
                if (currentDescriptor.configurationPtr->bConfigurationValue != configurationValue)
                {
                    status = NextDescriptorPointerGet(USB_DESCRIPTOR_TYPE_CONFIGURATION, &currentDescriptor.headerPtr);
                }
                else
                {
                    status = SUCCESS;

                    // Ends loop on success
                    i = 0;
                }

                if (SUCCESS != status)
                {
                    // Ends loop on error.
                    i = 0;
                }
            }

            if (SUCCESS == status)
            {
                if (currentDescriptor.configurationPtr->bConfigurationValue == configurationValue)
                {
                    *configurationPtr = currentDescriptor.configurationPtr;
                }
                else
                {
                    // configurationValue not found
                    status = DESCRIPTOR_SEARCH_ERROR;
                }
            }
        }
    }

    return status;
}

RETURN_CODE_t NextDescriptorPointerGet(USB_DESCRIPTOR_TYPE_t descriptorType, USB_DESCRIPTOR_HEADER_t **descriptorHeaderPtr)
{
    RETURN_CODE_t status = UNINITIALIZED;

    // cppcheck-suppress misra-c2012-19.2
    USB_DESCRIPTOR_PTR_t currentDescriptor = { .headerPtr = *descriptorHeaderPtr };

    uint8_t incrementCount = 0u;
    while (UNINITIALIZED == status)
    {
        // Increments to the start of the next pointer.
        if ((USB_DESCRIPTOR_TYPE_CONFIGURATION == descriptorType) && (USB_DESCRIPTOR_TYPE_CONFIGURATION == (USB_DESCRIPTOR_TYPE_t)currentDescriptor.headerPtr->bDescriptorType))
        {
            // If the device is looking for the next configuration, it increments the pointer with total length of the configuration.
            currentDescriptor.bytePtr = &currentDescriptor.bytePtr[currentDescriptor.configurationPtr->wTotalLength];
        }
        else
        {
            // Else it only increments with the descriptor length.
            currentDescriptor.bytePtr = &currentDescriptor.bytePtr[currentDescriptor.headerPtr->bLength];
        }

        // Checks whether it has found the correct descriptor type or if it needs to continue looping.
        if (descriptorType == (USB_DESCRIPTOR_TYPE_t)currentDescriptor.headerPtr->bDescriptorType)
        {
            status = SUCCESS;
            *descriptorHeaderPtr = currentDescriptor.headerPtr;
        }
        else
        {
            // If it has looped through too many descriptors, it is assumed that the descriptor structure is set up incorrectly and the loop is exited.
            if (incrementCount++ > USB_DESCRIPTOR_SEARCH_LIMIT)
            {
                status = DESCRIPTOR_SEARCH_ERROR;
            }
        }
    }

    return status;
}

RETURN_CODE_t USB_DescriptorInterfaceConfigure(uint8_t interfaceNumber, uint8_t alternateSetting, bool enable)
{
    RETURN_CODE_t status = UNINITIALIZED;

    if (NULL != activeConfigurationPtr)
    {
        // Pointer initialized to the address of the active configuration descriptor
        // cppcheck-suppress misra-c2012-19.2
        USB_DESCRIPTOR_PTR_t currentDescriptor = { .configurationPtr = activeConfigurationPtr };

        // Limit to end of configuration to make sure the loop does not overflow
        uint8_t *endOfConfiguration = &currentDescriptor.bytePtr[currentDescriptor.configurationPtr->wTotalLength];

        // Find first interface descriptor before entering loop
        status = NextDescriptorPointerGet(USB_DESCRIPTOR_TYPE_INTERFACE, &currentDescriptor.headerPtr);

        // Loop through all the descriptors in the current configuration
        USB_INTERFACE_DESCRIPTOR_t *enableInterfacePtr = NULL;
        while ((SUCCESS == status) && (currentDescriptor.bytePtr < endOfConfiguration))
        {
            // Check if interface number and alternate setting correspond to the active interface before disabling endpoints
            if ((interfaceNumber == currentDescriptor.interfacePtr->bInterfaceNumber) && (activeInterfaces[interfaceNumber] == currentDescriptor.interfacePtr->bAlternateSetting))
            {
                // Disable endpoints for the active alternate interface
                status = DescriptorEndpointsConfigure(currentDescriptor.interfacePtr, false);
                if (SUCCESS == status)
                {
                    // Reset the active alternate interface to 0
                    status = ActiveAlternateSettingSet(interfaceNumber, USB_DEFAULT_ALTERNATE_SETTING);
                }
            }

            if (enable)
            {
                if (interfaceNumber == currentDescriptor.interfacePtr->bInterfaceNumber)
                {
                    if (alternateSetting == currentDescriptor.interfacePtr->bAlternateSetting)
                    {
                        // Requested interface found
                        enableInterfacePtr = currentDescriptor.interfacePtr;
                    }
                }
            }

            status = NextDescriptorPointerGet(USB_DESCRIPTOR_TYPE_INTERFACE, &currentDescriptor.headerPtr);
            if (DESCRIPTOR_SEARCH_ERROR == status)
            {
                // Search error from NextDescriptorPointerGet means search is complete
                if ((false == enable) || (NULL != enableInterfacePtr))
                {
                    // Search was successful, correcting status
                    status = SUCCESS;

                    // Set byte pointer to end of config to exit loop
                    currentDescriptor.bytePtr = endOfConfiguration;
                }
            }
        }

        if (SUCCESS == status)
        {
            if (true == enable)
            {
                if (NULL != enableInterfacePtr)
                {
                    // Enable the endpoints for the activated interface
                    status = DescriptorEndpointsConfigure(enableInterfacePtr, true);
                    if (SUCCESS == status)
                    {
                        status = ActiveAlternateSettingSet(interfaceNumber, alternateSetting);
                    }
                }
                else
                {
                    status = DESCRIPTOR_SEARCH_ERROR;
                }
            }
        }
    }
    else
    {
        status = DESCRIPTOR_POINTER_ERROR;
    }

    return status;
}

RETURN_CODE_t ActiveAlternateSettingSet(uint8_t interfaceNumber, uint8_t alternateSetting)
{
    RETURN_CODE_t status = UNINITIALIZED;

    if (interfaceNumber < USB_INTERFACE_NUM)
    {
        activeInterfaces[interfaceNumber] = alternateSetting;
        status = SUCCESS;
    }
    else
    {
        status = INTERFACE_SET_ERROR;
    }

    return status;
}

RETURN_CODE_t ActiveAlternateSettingGet(uint8_t interfaceNumber, uint8_t *alternateSetting)
{
    RETURN_CODE_t status = UNINITIALIZED;

    if (interfaceNumber < USB_INTERFACE_NUM)
    {
        *alternateSetting = activeInterfaces[interfaceNumber];
        status = SUCCESS;
    }
    else
    {
        status = INTERFACE_GET_ERROR;
    }

    return status;
}

RETURN_CODE_t DescriptorEndpointsConfigure(USB_INTERFACE_DESCRIPTOR_t *interfacePtr, bool enable)
{
    RETURN_CODE_t status = UNINITIALIZED;

    if ((uint8_t)USB_DESCRIPTOR_TYPE_INTERFACE == interfacePtr->header.bDescriptorType)
    {
        // The number of endpoints to enable/disable is found from the interface.
        uint8_t numEndpoints = interfacePtr->bNumEndpoints;
        if (numEndpoints > 0u)
        {
            // cppcheck-suppress misra-c2012-19.2
            USB_DESCRIPTOR_PTR_t currentDescriptor = { .interfacePtr = interfacePtr };

            while (numEndpoints > 0u)
            {
                // Pre-increments to the next descriptor, since the initial descriptor is the interface.
                currentDescriptor.bytePtr = &currentDescriptor.bytePtr[currentDescriptor.headerPtr->bLength];

                if (USB_DESCRIPTOR_TYPE_ENDPOINT == (USB_DESCRIPTOR_TYPE_t)currentDescriptor.headerPtr->bDescriptorType)
                {
                    if (true == enable)
                    {
                        // Configures endpoint according to descriptor.
                        status
                            = USB_EndpointConfigure(currentDescriptor.endpointPtr->bEndpointAddress, currentDescriptor.endpointPtr->wMaxPacketSize, currentDescriptor.endpointPtr->bmAttributes.type);
                    }
                    else
                    {
                        // Aborts any ongoing transfer and disable endpoint.
                        status = USB_TransferAbort(currentDescriptor.endpointPtr->bEndpointAddress);
                        if (SUCCESS == status)
                        {
                            status = USB_EndpointDisable(currentDescriptor.endpointPtr->bEndpointAddress);
                        }
                    }

                    numEndpoints--;

                    if (SUCCESS != status)
                    {
                        // Exits loop immediately.
                        numEndpoints = 0;
                    }
                }
            }
        }
        else
        {
            // Interface has no endpoints.
            status = SUCCESS;
        }
    }
    else
    {
        status = DESCRIPTOR_ENDPOINT_ERROR;
    }

    return status;
}

RETURN_CODE_t USB_DescriptorPointerGet(USB_DESCRIPTOR_TYPE_t descriptor, uint8_t attribute, uint8_t **descriptorPtr, uint16_t *descriptorLength)
{
    RETURN_CODE_t status = UNINITIALIZED;

    // cppcheck-suppress misra-c2012-19.2
    USB_DESCRIPTOR_PTR_t localDescriptorPtr;

    switch (descriptor)
    {
    case USB_DESCRIPTOR_TYPE_DEVICE:
        // Returns pointer to device descriptor.
        if (applicationPointers != NULL)
        {
            *descriptorPtr = (uint8_t *)applicationPointers->devicePtr;
            *descriptorLength = (uint16_t)applicationPointers->devicePtr->header.bLength;
            status = SUCCESS;
        }
        else
        {
            status = DESCRIPTOR_POINTER_ERROR;
        }
        break;
    case USB_DESCRIPTOR_TYPE_CONFIGURATION:;
        // Returns pointer to configuration, with the total length.

        status = ConfigurationPointerGet(attribute, &localDescriptorPtr.configurationPtr);
        if (SUCCESS == status)
        {
            *descriptorPtr = localDescriptorPtr.bytePtr;
            *descriptorLength = localDescriptorPtr.configurationPtr->wTotalLength;
        }
        break;
    case USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER:
        // Only for high-speed.
        status = UNSUPPORTED;
        break;
    case USB_DESCRIPTOR_TYPE_OTHER_SPEED_CONFIGURATION:
        // Only for high-speed.
        status = UNSUPPORTED;
        break;
    case USB_DESCRIPTOR_TYPE_BOS:
        if (NULL != applicationPointers->deviceBOSptr)
        {
            *descriptorPtr = (uint8_t *)applicationPointers->deviceBOSptr;
            *descriptorLength = (uint16_t)applicationPointers->deviceBOSptr->wTotalLength;
            status = SUCCESS;
        }
        else
        {
            status = UNSUPPORTED;
        }
        break;
    default:
        // Find class or vendor descriptor types in the active configuration
        if (descriptor >= USB_DESCRIPTOR_TYPE_CLASS)
        {
            localDescriptorPtr.configurationPtr = activeConfigurationPtr;

            // Find the first descriptor available of the current type
            status = NextDescriptorPointerGet(descriptor, &localDescriptorPtr.headerPtr);
            if (SUCCESS == status)
            {
                *descriptorPtr = (uint8_t *)localDescriptorPtr.headerPtr;
                *descriptorLength = localDescriptorPtr.headerPtr->bLength;
            }
        }
        else
        {
            status = DESCRIPTOR_REQUEST_ERROR;
        }

        break;
    }

    if (SUCCESS != status)
    {
        *descriptorPtr = NULL;
        *descriptorLength = 0u;
    }

    return status;
}

RETURN_CODE_t USB_DescriptorStringPointerGet(uint8_t stringIndex, uint16_t langID, uint8_t **descriptorAddressPtr, uint16_t *descriptorLength)
{
    RETURN_CODE_t status = UNINITIALIZED;

    if (NULL != applicationPointers->langIDptr)
    {
        if (stringIndex == 0u)
        {
            // Index 0 is the language id index, writes pointer and length.
            *descriptorAddressPtr = (uint8_t *)applicationPointers->langIDptr;
            *descriptorLength = (uint16_t)applicationPointers->langIDptr->header.bLength;
            status = SUCCESS;
        }
        else
        {
            // Iterates through the supported language IDs to find the index.
            uint8_t langIdx = 0;
            for (langIdx = 0; langIdx < LANG_ID_NUM; langIdx++)
            {
                if (langID == applicationPointers->langIDptr->id_array[langIdx])
                {
                    // Language match, langIdx found.
                    break;
                }
            }

            if (LANG_ID_NUM == langIdx)
            {
                // Language ID not in langID struct, returns UNSUPPORTED.
                status = UNSUPPORTED;
            }
            else if (NULL != applicationPointers->stringPtrs[langIdx])
            {
                // Iterates through string descriptors to account for different string lengths.
                USB_DESCRIPTOR_HEADER_t *stringHeader = applicationPointers->stringPtrs[langIdx];
                if (1u == stringIndex)
                {
                    status = SUCCESS;
                }
                else
                {
                    for (uint8_t i = 1u; i < stringIndex; i++)
                    {
                        status = NextDescriptorPointerGet(USB_DESCRIPTOR_TYPE_STRING, &stringHeader);
                    }
                }

                // Writes pointer and length.
                if (SUCCESS == status)
                {
                    *descriptorAddressPtr = (uint8_t *)stringHeader;
                    *descriptorLength = (uint16_t)stringHeader->bLength;
                }
            }
            else
            {
                // stringPtrs not set up correctly, returns error.
                status = DESCRIPTOR_POINTER_ERROR;
            }
        }
    }
    else
    {
        // langIDptr not set up, returns unsupported and stalls request.
        status = UNSUPPORTED;
    }

    return status;
}
