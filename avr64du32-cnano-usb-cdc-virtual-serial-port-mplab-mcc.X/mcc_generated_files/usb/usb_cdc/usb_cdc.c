/**
 * USBCDC CDC Source File
 * @file usb_cdc.c
 * @ingroup usb_cdc
 * @brief This file contains implementation for CDC
 * @version USB Device Stack Driver Version 1.0.0
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

#include <stddef.h>
#include <usb_cdc.h>
#include <usb_common_elements.h>
#include <usb_core.h>
#include <usb_core_requests.h>
#include <usb_core_transfer.h>
#include <usb_protocol_cdc.h>
#include <usb_protocol_headers.h>

// #include <usb_descriptors.h>
#include <usb_config.h>

// Line state and setup
STATIC uint16_t usbCDCControlLineState;
STATIC USB_CDC_LINE_CODING_t usbCDCLineCoding;

void USB_CDCInitialize(void)
{
    // Initial values
    usbCDCControlLineState = 0;
    usbCDCLineCoding = (USB_CDC_LINE_CODING_t){
        .dwDTERate = 0,
        .bCharFormat = USB_CDC_LINE_CODING_ONE_STOP_BIT,
        .bParityType = USB_CDC_LINE_CODING_PARITY_NONE,
        .bDataBits = USB_CDC_LINE_CODING_8_DATA_BITS,
    };

    USB_ClassRequestCallbackRegister(USB_CDCRequestHandler);
}

RETURN_CODE_t USB_CDCRequestHandler(USB_SETUP_REQUEST_t *setupRequestPtr)
{
    RETURN_CODE_t status = UNINITIALIZED;

    // Tests if recipient is interface
    if (USB_REQUEST_RECIPIENT_INTERFACE == (USB_REQUEST_RECIPIENT_t)setupRequestPtr->bmRequestType.recipient)
    {
        // Determines request direction
        if (USB_REQUEST_DIR_IN == setupRequestPtr->bmRequestType.dataPhaseTransferDirection)
        {
            // If Class request
            if (USB_REQUEST_TYPE_CLASS == (USB_REQUEST_TYPE_t)setupRequestPtr->bmRequestType.type)
            {
                // Determines Class Get request ID
                switch (setupRequestPtr->bRequest)
                {
                case USB_CDC_REQUEST_GET_LINE_CODING:
                    status = USB_TransferControlDataSet((uint8_t *)&usbCDCLineCoding, sizeof(USB_CDC_LINE_CODING_t), NULL);
                    break;
                default:
                    status = UNSUPPORTED; // Currently unsupported request
                    break;
                }
            }
            else
            {
                status = UNSUPPORTED; // Unsupported or invalid request type
            }
        }
        else // USB_REQUEST_DIR_OUT
        {
            // If Class request
            if (USB_REQUEST_TYPE_CLASS == (USB_REQUEST_TYPE_t)setupRequestPtr->bmRequestType.type)
            {
                // Determines Class Set/Send request ID
                switch (setupRequestPtr->bRequest)
                {
                case USB_CDC_REQUEST_SET_LINE_CODING:
                    status = USB_TransferControlDataSet((uint8_t *)&usbCDCLineCoding, sizeof(USB_CDC_LINE_CODING_t), NULL);
                    break;
                case USB_CDC_REQUEST_SET_CONTROL_LINE_STATE:
                    usbCDCControlLineState = setupRequestPtr->wValue;
                    status = SUCCESS;
                    break;
                default:
                    status = UNSUPPORTED; // Currently unsupported request
                    break;
                }
            }
            else
            {
                status = UNSUPPORTED; // Unsupported or invalid request type
            }
        }
    }
    else // Non-interface recipient
    {
        status = UNSUPPORTED; // Unsupported recipients
    }

    return status;
}

bool USB_CDCDataTerminalReady(void)
{
    return usbCDCControlLineState & USB_CDC_DATA_TERMINAL_READY_bm;
}

void USB_CDCSetBaud(uint16_t baud)
{
    usbCDCLineCoding.dwDTERate = baud;
}

uint32_t USB_CDCGetBaud(void)
{
    return usbCDCLineCoding.dwDTERate;
}

void USB_CDCSetStopBits(USB_CDC_LINE_CODING_STOP_BITS_t numStopBits)
{
    usbCDCLineCoding.bCharFormat = numStopBits;
}

USB_CDC_LINE_CODING_STOP_BITS_t USB_CDCGetStopBits(void)
{
    return usbCDCLineCoding.bCharFormat;
}

void USB_CDCSetParity(USD_CDC_LINE_CODING_PARITY_t parity)
{
    usbCDCLineCoding.bParityType = parity;
}

USD_CDC_LINE_CODING_PARITY_t USB_CDCGetParity(void)
{
    return usbCDCLineCoding.bParityType;
}

void USB_CDCSetDataBits(USD_CDC_LINE_CODING_DATA_BITS_t numDataBits)
{
    usbCDCLineCoding.bDataBits = numDataBits;
}

USD_CDC_LINE_CODING_DATA_BITS_t USB_CDCGetDataBits(void)
{
    return usbCDCLineCoding.bDataBits;
}