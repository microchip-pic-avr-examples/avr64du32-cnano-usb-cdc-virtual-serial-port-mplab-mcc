/**
 * USBPERIPHERALENDPOINT Peripheral Endpoint Source File
 * @file usb_peripheral_endpoint.c
 * @ingroup usb_peripheral_endpoint
 * @brief API module for usb_peripheral covering endpoint related functions.
 * @version USB Device Stack HAL Driver Version 1.0.0
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
#include <usb_peripheral_avr_du.h>
#include <usb_peripheral_endpoint.h>
#include <usb_protocol_headers.h>

#if defined(USB_EP_NUM) && defined(USB_MAX_ENDPOINTS)
    #if USB_EP_NUM > USB_MAX_ENDPOINTS
        #error "USB_EP_NUM is too large, max is USB_MAX_ENDPOINTS"
    #endif
#else
    #error "USB_EP_NUM not configured"
#endif

/**
 * @ingroup usb_peripheral_endpoint
 * @brief Algorithm to detect if a given number is a power of two.
 * A number is a power of two if it has exactly one '1' in its binary representation. This is true if subtracting '1' from the number
 * and doing an AND operation on the result with the number itself returns 0.
 * @param number 8-bit unsigned integer
 * @retval True - The given number is a power of two
 * @retval False - The given number is not a power of two
 */
#define IsPowerOfTwo(number) ((0u != (number)) && (((number) & ((number)-1u)) == 0u))

/**
 * @ingroup usb_peripheral_endpoint
 * @brief SRAM tables for the FIFO and endpoint registers, as well as the FRAMENUM register.
 * Represents the endpoint configuration table based on the number of endpoints in use.
 * This line instantiates an object using the data structure type.
 */
USB_ENDPOINT_TABLE_t endpointTable __attribute__((aligned(2)));

RETURN_CODE_t USB_EndpointConfigure(USB_PIPE_t pipe, uint16_t endpointSize, USB_ENDPOINT_t endpointType)
{
    RETURN_CODE_t status = UNINITIALIZED;

    uint8_t endpointConfiguration = 0;
    if (SUCCESS != ConvertEndpointSizeToMask(endpointSize, endpointType, &endpointConfiguration))
    {
        status = ENDPOINT_SIZE_ERROR;
    }
    else if ((uint8_t)USB_EP_NUM <= pipe.address)
    {
        status = ENDPOINT_ADDRESS_ERROR;
    }
    else if (INTERRUPT < endpointType)
    {
        status = ENDPOINT_TYPE_ERROR;
    }
    else
    {
        switch (endpointType)
        {
        case CONTROL:
            endpointConfiguration |= USB_TYPE_CONTROL_gc;
            break;
        case ISOCHRONOUS:
            endpointConfiguration |= USB_TYPE_ISO_gc;
            break;
        case BULK:
        case INTERRUPT:
            endpointConfiguration |= USB_TYPE_BULKINT_gc;
            break;
        default:
            endpointConfiguration |= USB_TYPE_DISABLE_gc;
            break;
        }

        if (USB_EP_DIR_OUT == pipe.direction)
        {
            USB_EndpointOutNAKSet(pipe.address);
            USB_EndpointOutStatusClear(pipe.address);
            USB_NumberBytesReceivedReset(pipe.address);
            USB_EndpointOutControlSet(pipe.address, endpointConfiguration);

            // Set up the static endpoint configurations
            if ((uint8_t)0x01 == endpointStaticConfig[pipe.address].OutMultipktEnable)
            {
                USB_EndpointOutMultipktEnable(pipe.address);

                if ((uint8_t)0x01 == endpointStaticConfig[pipe.address].OutAzlpEnable)
                {
                    USB_EndpointOutAzlpEnable(pipe.address);
                }

                status = SUCCESS;
            }
            else if ((uint8_t)0x01 == endpointStaticConfig[pipe.address].OutAzlpEnable)
            {
                // AZLP only works together with multipacket
                status = ENDPOINT_AZLP_ERROR;
            }
            else
            {
                status = SUCCESS;
            }

            if ((uint8_t)0x01 != endpointStaticConfig[pipe.address].OutTrncInterruptEnable)
            {
                USB_EndpointOutTransactionCompleteInterruptDisable(pipe.address);
            }
        }
        else
        {
            USB_EndpointInNAKSet(pipe.address);
            USB_EndpointInStatusClear(pipe.address);
            USB_NumberBytesToSendReset(pipe.address);
            USB_EndpointInControlSet(pipe.address, endpointConfiguration);

            // Set up the static endpoint configurations
            if ((uint8_t)0x01 == endpointStaticConfig[pipe.address].InMultipktEnable)
            {
                USB_EndpointInMultipktEnable(pipe.address);

                if ((uint8_t)0x01 == endpointStaticConfig[pipe.address].InAzlpEnable)
                {
                    USB_EndpointInAlzpEnable(pipe.address);
                }

                status = SUCCESS;
            }
            else if ((uint8_t)0x01 == endpointStaticConfig[pipe.address].InAzlpEnable)
            {
                // AZLP only works together with multipacket
                status = ENDPOINT_AZLP_ERROR;
            }
            else
            {
                status = SUCCESS;
            }

            if ((uint8_t)0x01 != endpointStaticConfig[pipe.address].InTrncInterruptEnable)
            {
                USB_EndpointInTransactionCompleteDisable(pipe.address);
            }
        }
    }

    return status;
}

RETURN_CODE_t USB_EndpointDisable(USB_PIPE_t pipe)
{
    RETURN_CODE_t status = UNINITIALIZED;

    if ((uint8_t)USB_EP_NUM <= pipe.address)
    {
        status = ENDPOINT_ADDRESS_ERROR;
    }
    else
    {
        if (USB_EP_DIR_OUT == pipe.direction)
        {
            USB_EndPointOutDisable(pipe.address);
        }
        else
        {
            USB_EndPointInDisable(pipe.address);
        }

        status = SUCCESS;
    }

    return status;
}

uint16_t USB_EndpointSizeGet(USB_PIPE_t pipe)
{
    uint8_t endpointType = 0;
    uint8_t endpointSizeConfig = 0;
    int16_t endpointSize = 0;
    if (USB_EP_DIR_OUT == pipe.direction)
    {
        endpointType = USB_EndPointOutTypeConfigGet(pipe.address);
        endpointSizeConfig = (USB_TYPE_ISO_gc == endpointType) ? USB_EndpointOutIsoSizeGet(pipe.address) : USB_EndpointOutDefaultSizeGet(pipe.address);
    }
    else
    {
        endpointType = USB_EndPointInTypeConfigGet(pipe.address);
        endpointSizeConfig = (USB_TYPE_ISO_gc == endpointType) ? USB_EndpointInIsoSizeGet(pipe.address) : USB_EndpointInDefaultSizeGet(pipe.address);
    }
    if (USB_BUFSIZE_ISO_BUF1023_gc == endpointSizeConfig)
    {
        endpointSize = MAX_ENDPOINT_SIZE_ISO;
    }
    else
    {
        endpointSize = 8U << (uint16_t)endpointSizeConfig;
    }
    return endpointSize;
}

USB_ENDPOINT_t USB_EndpointTypeGet(USB_PIPE_t pipe)
{
    USB_TYPE_t endpointConfigType;
    if (USB_EP_DIR_OUT == pipe.direction)
    {
        endpointConfigType = USB_EndPointOutTypeConfigGet(pipe.address);
    }
    else // USB_EP_DIR_IN
    {
        endpointConfigType = USB_EndPointInTypeConfigGet(pipe.address);
    }

    USB_ENDPOINT_t endpointType = DISABLED;
    switch (endpointConfigType)
    {
    case USB_TYPE_CONTROL_gc:
        endpointType = CONTROL;
        break;
    case USB_TYPE_BULKINT_gc:
        // Peripheral does not distinguish between BULK and INTERRUPT, returning BULK
        endpointType = BULK;
        break;
    case USB_TYPE_ISO_gc:
        endpointType = ISOCHRONOUS;
        break;
    default:
        // endpointType = DISABLED;
        break;
    }

    return endpointType;
}

RETURN_CODE_t USB_EndpointStall(USB_PIPE_t pipe)
{
    RETURN_CODE_t status = UNINITIALIZED;

    if ((uint8_t)USB_EP_NUM <= pipe.address)
    {
        status = ENDPOINT_ADDRESS_ERROR;
    }
    else
    {
        if (USB_EP_DIR_OUT == pipe.direction)
        {
            USB_EndpointOutStall(pipe.address);
        }
        else
        {
            USB_EndpointInStall(pipe.address);
        }

        status = SUCCESS;
    }

    return status;
}

RETURN_CODE_t USB_EndpointStallClear(USB_PIPE_t pipe)
{
    RETURN_CODE_t status = UNINITIALIZED;

    if ((uint8_t)USB_EP_NUM <= pipe.address)
    {
        status = ENDPOINT_ADDRESS_ERROR;
    }
    else
    {
        if (USB_EP_DIR_OUT == pipe.direction)
        {
            USB_EndpointOutStallClear(pipe.address);
        }
        else
        {
            USB_EndpointInStallClear(pipe.address);
        }

        status = SUCCESS;
    }

    return status;
}

bool USB_EndpointIsStalled(USB_PIPE_t pipe)
{

    bool isStalled = false;

    if ((uint8_t)USB_EP_NUM > pipe.address)
    {
        if (USB_EP_DIR_OUT == pipe.direction)
        {
            isStalled = USB_EndpointOutIsStalled(pipe.address);
        }
        else
        {
            isStalled = USB_EndpointInIsStalled(pipe.address);
        }
    }

    return isStalled;
}

RETURN_CODE_t USB_EndpointStalledConditionAck(USB_PIPE_t pipe)
{
    RETURN_CODE_t status = UNINITIALIZED;

    if ((uint8_t)USB_EP_NUM <= pipe.address)
    {
        status = ENDPOINT_ADDRESS_ERROR;
    }
    else
    {
        if (USB_EP_DIR_OUT == pipe.direction)
        {
            USB_EndpointOutStallAck(pipe.address);
        }
        else
        {
            USB_EndpointInStallAck(pipe.address);
        }

        status = SUCCESS;
    }

    return status;
}

RETURN_CODE_t USB_DataToggleSet(USB_PIPE_t pipe)
{
    RETURN_CODE_t status = UNINITIALIZED;

    if ((uint8_t)USB_EP_NUM <= pipe.address)
    {
        status = ENDPOINT_ADDRESS_ERROR;
    }
    else
    {
        if (USB_EP_DIR_OUT == pipe.direction)
        {
            USB_EndpointOutDataToggleSet(pipe.address);
        }
        else
        {
            USB_EndpointInDataToggleSet(pipe.address);
        }

        status = SUCCESS;
    }

    return status;
}

RETURN_CODE_t USB_DataToggleClear(USB_PIPE_t pipe)
{
    RETURN_CODE_t status = UNINITIALIZED;

    if ((uint8_t)USB_EP_NUM <= pipe.address)
    {
        status = ENDPOINT_ADDRESS_ERROR;
    }
    else
    {
        if (USB_EP_DIR_OUT == pipe.direction)
        {
            USB_EndpointOutDataToggleClear(pipe.address);
        }
        else
        {
            USB_EndpointInDataToggleClear(pipe.address);
        }

        status = SUCCESS;
    }

    return status;
}

RETURN_CODE_t USB_DataToggle(USB_PIPE_t pipe)
{
    RETURN_CODE_t status = UNINITIALIZED;

    if ((uint8_t)USB_EP_NUM <= pipe.address)
    {
        status = ENDPOINT_ADDRESS_ERROR;
    }
    else
    {
        if (USB_EP_DIR_OUT == pipe.direction)
        {
            (USB_EndpointOutDataToggleIsSet(pipe.address)) ? USB_DataToggleClear(pipe) : USB_DataToggleSet(pipe);
        }
        else
        {
            (USB_EndpointInDataToggleIsSet(pipe.address)) ? USB_DataToggleClear(pipe) : USB_DataToggleSet(pipe);
        }

        status = SUCCESS;
    }

    return status;
}

RETURN_CODE_t ConvertEndpointSizeToMask(uint16_t endpointSize, USB_ENDPOINT_t endpointType, uint8_t *endpointMaskPtr)
{
    RETURN_CODE_t status = UNINITIALIZED;

    if (ISOCHRONOUS == endpointType)
    {
        if (((uint16_t)MAX_ENDPOINT_SIZE_ISO < endpointSize) || ((endpointSize < (uint16_t)MAX_ENDPOINT_SIZE_ISO) && !(IsPowerOfTwo(endpointSize))))
        {
            status = ENDPOINT_SIZE_ERROR;
        }
    }
    else
    {
        if (((uint16_t)MAX_ENDPOINT_SIZE_DEFAULT < endpointSize) || !(IsPowerOfTwo(endpointSize)))
        {
            status = ENDPOINT_SIZE_ERROR;
        }
    }

    if (UNINITIALIZED == status)
    {
        if ((uint16_t)MAX_ENDPOINT_SIZE_ISO == endpointSize)
        {
            *endpointMaskPtr = USB_BUFSIZE_ISO_BUF1023_gc;
        }
        else
        {
            uint8_t mask = 0;
            uint16_t baseSize = 8;

            while (baseSize < endpointSize)
            {

                mask++;
                baseSize <<= 1;
            }

            *endpointMaskPtr = mask << USB_BUFSIZE_DEFAULT_gp;
        }

        status = SUCCESS;
    }

    return status;
}

RETURN_CODE_t EndpointBufferSet(USB_PIPE_t pipe, uint8_t *bufAddress)
{
    RETURN_CODE_t status = UNINITIALIZED;

    if ((uint8_t)USB_EP_NUM <= pipe.address)
    {
        status = ENDPOINT_ADDRESS_ERROR;
    }
    else
    {
        if (USB_EP_DIR_OUT == pipe.direction)
        {
            // Errata: Out transactions must be word aligned when using multipacket
            if ((1u == endpointStaticConfig[pipe.address].OutMultipktEnable) && (((uint16_t)bufAddress & 0x0001) != 0u))
            {
                status = ENDPOINT_ALIGN_ERROR;
            }
            else
            {
                USB_EndpointOutBufferSet(pipe.address, bufAddress);
                status = SUCCESS;
            }
        }
        else
        {
            USB_EndpointInBufferSet(pipe.address, bufAddress);
            status = SUCCESS;
        }
    }

    return status;
}
