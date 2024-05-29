/**
 * USBCDCVIRTUALSERIALPORT CDC Virtual Serial Port Source File
 * @file usb_cdc_virtual_serial_port.c
 * @ingroup usb_cdc
 * @brief This file contains implementation for a CDC application
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

#include <usb_cdc_virtual_serial_port.h>
#include <usb_cdc.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <usb_config.h>
#include <circular_buffer.h>

// ZLP state
static bool zlpStateTX = true;

// USB Pipes
STATIC USB_PIPE_t CDCTxPipe = {
    .address = USB_CDC_BULK_EP_IN,
    .direction = USB_EP_DIR_IN,
};

STATIC USB_PIPE_t CDCRxPipe = {
    .address = USB_CDC_BULK_EP_OUT,
    .direction = USB_EP_DIR_OUT,
};

// RX Buffer
STATIC uint8_t usbCDCReceiveTempBuffer[USB_CDC_RX_PACKET_SIZE] __attribute__((aligned(2)));
STATIC uint8_t usbCDCReceiveArray[USB_CDC_RX_BUFFER_SIZE];
STATIC CIRCULAR_BUFFER_t usbCDCReceiveBuffer = {
    .content = usbCDCReceiveArray,
    .head = 0,
    .tail = 0,
    .maxLength = USB_CDC_RX_BUFFER_SIZE,
};
// TX Buffer
STATIC uint8_t usbCDCTransmitArray[USB_CDC_TX_BUFFER_SIZE];
STATIC CIRCULAR_BUFFER_t usbCDCTransmitBuffer = {
    .content = usbCDCTransmitArray,
    .head = 0,
    .tail = 0,
    .maxLength = USB_CDC_TX_BUFFER_SIZE,
};

void USB_CDCVirtualSerialPortInitialize(void)
{
    USB_CDCInitialize();
}

RETURN_CODE_t USB_CDCVirtualSerialPortHandler(void)
{
    RETURN_CODE_t status = SUCCESS;

    // Checks if data have been added to transmit buffer
    if (false == CIRCBUF_Empty(&usbCDCTransmitBuffer))
    {
        // Transmits data to host if pipe not busy
        if (false == USB_PipeStatusIsBusy(CDCTxPipe))
        {
            status = USB_TransferWriteStart(CDCTxPipe, usbCDCTransmitArray, usbCDCTransmitBuffer.head, zlpStateTX, USB_CDCDataTransmitted);
        }
        else
        {
            // Pipe is busy, retry on next iteration
        }
    }
    else
    {
        // No data to transmit
    }

    // Checks if outgoing data transmitted or not available
    if (SUCCESS == status)
    {
        // Checks if room exist for 1 USB CDC packet in the receive buffer
        if (USB_CDC_RX_PACKET_SIZE <= CIRCBUF_FreeSpace(&usbCDCReceiveBuffer))
        {
            // Receives data from host if pipe not busy
            if (false == USB_PipeStatusIsBusy(CDCRxPipe))
            {
                status = USB_TransferReadStart(CDCRxPipe, usbCDCReceiveTempBuffer, USB_CDC_RX_PACKET_SIZE, false, USB_CDCDataReceived);
            }
            else
            {
                // Pipe is busy, retry on next iteration
            }
        }
        else
        {
            // RX buffer is full, retry on next iteration
        }
    }
    else
    {
        ; // Skips read if write failed
    }

    return status;
}

CDC_RETURN_CODE_t USB_CDCRead(uint8_t *data)
{
    return CIRCBUF_Dequeue(&usbCDCReceiveBuffer, data);
}

CDC_RETURN_CODE_t USB_CDCWrite(uint8_t data)
{
    return CIRCBUF_Enqueue(&usbCDCTransmitBuffer, data);
}

bool USB_CDCTxBusy(void)
{
    return CIRCBUF_Full(&usbCDCTransmitBuffer) || USB_PipeStatusIsBusy(CDCTxPipe);
}

void USB_CDCDataReceived(USB_PIPE_t pipe, USB_TRANSFER_STATUS_t status, uint16_t bytesTransferred)
{
    (void)(pipe);

    if (USB_PIPE_TRANSFER_OK == status)
    {
        // Echo data back
        // USB_TransferWriteStart(CDCTxPipe, usbCDCReceiveTempBuffer, bytesTransferred, zlpStateTX, NULL);
        // Moves received data to circular buffer
        for (uint16_t i = 0; i < bytesTransferred; i++)
        {
            CIRCBUF_Enqueue(&usbCDCReceiveBuffer, usbCDCReceiveTempBuffer[i]);
        }
    }
    else
    {
        ; // Transfer error, do nothing in callback
    }
}

void USB_CDCDataTransmitted(USB_PIPE_t pipe, USB_TRANSFER_STATUS_t status, uint16_t bytesTransferred)
{
    (void)(pipe);
    (void)(bytesTransferred);

    if (USB_PIPE_TRANSFER_OK == status)
    {
        // Data transmitted, reset transmit buffer
        usbCDCTransmitBuffer.head = 0;
        usbCDCTransmitBuffer.tail = 0;
    }
    else
    {
        ; // Transfer error, do nothing in callback
    }
}