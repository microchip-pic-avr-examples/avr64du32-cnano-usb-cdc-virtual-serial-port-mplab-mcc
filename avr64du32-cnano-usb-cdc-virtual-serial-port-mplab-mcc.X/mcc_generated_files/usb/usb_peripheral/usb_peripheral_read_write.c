/**
 * USBPERIPHERALREADWRITE Peripheral Read/Write Source File
 * @file usb_peripheral_read_write.c
 * @ingroup usb_peripheral_read_write
 * @brief API module for usb_peripheral covering low level USB transaction functions.
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
#include <usb_peripheral_read_write.h>
#include <usb_protocol_headers.h>

/**
 * @ingroup usb_peripheral_read_write
 * @def Calculates from pipe address and direction to location in a transfer array.
 * @param pipe - A combination of endpoint address and direction
 * @return The pipe transaction index for this pipe in pipe_transfer[]
 */
#define PipeTransferIndexGet(pipe) (((pipe).address * 2) + (pipe).direction)

STATIC USB_PIPE_TRANSFER_t pipeTransfer[USB_EP_NUM * 2];

RETURN_CODE_t USB_TransactionStart(USB_PIPE_t pipe)
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
            USB_EndpointOutNAKClear(pipe.address);
        }
        else
        {
            USB_EndpointInNAKClear(pipe.address);
        }

        status = SUCCESS;
    }

    return status;
}

RETURN_CODE_t USB_TransactionAbort(USB_PIPE_t pipe)
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
            USB_EndpointOutNAKSet(pipe.address);
        }
        else
        {
            USB_EndpointInNAKSet(pipe.address);
        }

        pipeTransfer[PipeTransferIndexGet(pipe)].status = USB_PIPE_TRANSFER_ABORTED;
        status = SUCCESS;
    }

    return status;
}

RETURN_CODE_t USB_TransactionCompleteAck(USB_PIPE_t pipe)
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
            USB_EndpointOutTransactionCompleteAck(pipe.address);
        }
        else
        {
            USB_EndpointInTransactionCompleteAck(pipe.address);
        }
        pipeTransfer[PipeTransferIndexGet(pipe)].status = USB_PIPE_TRANSFER_OK;
        status = SUCCESS;
    }

    return status;
}

bool USB_TransactionIsCompleted(void)
{
    return USB_TransactionCompleteInterruptIs();
}

RETURN_CODE_t USB_TransactionCompletedPipeGet(USB_PIPE_t *pipe)
{
    RETURN_CODE_t status = UNINITIALIZED;

    if (USB_TransactionIsCompleted())
    {
        // Finds FIFO entry by adding (subtracting) the signed read pointer to the size of the FIFO
        // Reading the FIFO Read Pointer will handle the Transaction Complete Interrupt flag.
        // The USB_FifoReadPointerGet is a device-specific function.

        uint8_t fifoEntry = endpointTable.FIFO[(USB_EP_NUM * 2u) + USB_FifoReadPointerGet()];

        // The FIFO entry contains the endpoint address and direction of the endpoint to handle next.
        USB_PIPE_t returnPipe = { .direction = (fifoEntry & USB_DIR_bm) >> USB_DIR_bp, .address = (fifoEntry & USB_EPNUM_gm) >> USB_EPNUM_gp };

        if ((uint8_t)USB_EP_NUM <= returnPipe.address)
        {
            status = ENDPOINT_ADDRESS_ERROR;
        }
        else
        {
            pipe->address = returnPipe.address;
            pipe->direction = returnPipe.direction;
            status = SUCCESS;
        }
    }
    else
    {
        // No transaction is completed.
        status = PIPE_TRANSFER_ERROR;
    }

    return status;
}

RETURN_CODE_t USB_PipeReset(USB_PIPE_t pipe)
{
    RETURN_CODE_t status = UNINITIALIZED;
    USB_PIPE_TRANSFER_t *pipeTransferPtr = &pipeTransfer[PipeTransferIndexGet(pipe)];

    if ((uint8_t)USB_EP_NUM <= pipe.address)
    {
        status = ENDPOINT_ADDRESS_ERROR;
    }
    else
    {
        pipeTransferPtr->status = USB_PIPE_TRANSFER_OK;
        pipeTransferPtr->transferDataPtr = NULL;
        pipeTransferPtr->transferDataSize = 0;
        pipeTransferPtr->bytesTransferred = 0;
        pipeTransferPtr->transferEndCallback = NULL;
        pipeTransferPtr->ZLPEnable = false;

        status = SUCCESS;
    }

    return status;
}

USB_TRANSFER_STATUS_t USB_PipeStatusGet(USB_PIPE_t pipe)
{

    return pipeTransfer[PipeTransferIndexGet(pipe)].status;
}

bool USB_PipeStatusIsBusy(USB_PIPE_t pipe)
{

    return (pipeTransfer[PipeTransferIndexGet(pipe)].status == USB_PIPE_TRANSFER_BUSY);
}

void USB_PipeDataPtrSet(USB_PIPE_t pipe, uint8_t *dataPtr)
{

    pipeTransfer[PipeTransferIndexGet(pipe)].transferDataPtr = dataPtr;
}

uint8_t *USB_PipeDataPtrGet(USB_PIPE_t pipe)
{

    return pipeTransfer[PipeTransferIndexGet(pipe)].transferDataPtr;
}

void USB_PipeDataToTransferSizeSet(USB_PIPE_t pipe, uint16_t dataSize)
{

    pipeTransfer[PipeTransferIndexGet(pipe)].transferDataSize = dataSize;
}

uint16_t USB_PipeDataToTransferSizeGet(USB_PIPE_t pipe)
{

    return pipeTransfer[PipeTransferIndexGet(pipe)].transferDataSize;
}

uint16_t USB_PipeDataTransferredSizeGet(USB_PIPE_t pipe)
{

    return pipeTransfer[PipeTransferIndexGet(pipe)].bytesTransferred;
}

void USB_PipeDataTransferredSizeSet(USB_PIPE_t pipe, uint16_t dataSize)
{

    pipeTransfer[PipeTransferIndexGet(pipe)].bytesTransferred = dataSize;
}

void USB_PipeDataTransferredSizeReset(USB_PIPE_t pipe)
{

    pipeTransfer[PipeTransferIndexGet(pipe)].bytesTransferred = 0;
}

void USB_PipeTransferZLP_Enable(USB_PIPE_t pipe)
{
    // Only enable manual ZLP if hardware AZLP is not enabled.
    if (((USB_EP_DIR_IN == pipe.direction) && (0u == endpointStaticConfig[pipe.address].InAzlpEnable))
        || ((USB_EP_DIR_OUT == pipe.direction) && (0u == endpointStaticConfig[pipe.address].OutAzlpEnable)))
    {
        pipeTransfer[PipeTransferIndexGet(pipe)].ZLPEnable = true;
    }
}

void USB_PipeTransferEndCallbackRegister(USB_PIPE_t pipe, USB_TRANSFER_END_CALLBACK_t callback)
{
    pipeTransfer[PipeTransferIndexGet(pipe)].transferEndCallback = callback;
}

void USB_PipeTransferEndCallback(USB_PIPE_t pipe)
{
    USB_PIPE_TRANSFER_t *pipeTransferPtr = &pipeTransfer[PipeTransferIndexGet(pipe)];

    if (NULL != pipeTransferPtr->transferEndCallback)
    {
        pipeTransferPtr->transferEndCallback(pipe, pipeTransferPtr->status, pipeTransferPtr->bytesTransferred);
    }
}

RETURN_CODE_t USB_InTransactionRun(USB_PIPE_t pipe)
{
    USB_PIPE_TRANSFER_t *pipeTransferPtr = &pipeTransfer[PipeTransferIndexGet(pipe)];
    RETURN_CODE_t status = UNINITIALIZED;
    uint16_t nextTransactionSize;

    if (USB_EP_DIR_IN != pipe.direction)
    {
        // Pipe is OUT, returns error code.
        status = ENDPOINT_DIRECTION_ERROR;
    }
    else
    {
        // Makes sure the transfer status is busy.
        pipeTransferPtr->status = USB_PIPE_TRANSFER_BUSY;

        // Calculates the size of next transaction.
        nextTransactionSize = pipeTransferPtr->transferDataSize - pipeTransferPtr->bytesTransferred;
        if (0U == nextTransactionSize)
        {
            // All data is sent, check if we need to send a manual ZLP as well.
            if (true == pipeTransferPtr->ZLPEnable)
            {
                // Sends a zero-length package by setting bytes to send to 0.
                USB_NumberBytesToSendSet(pipe.address, 0u);
                USB_NumberBytesSentReset(pipe.address);
                USB_EndpointInNAKClear(pipe.address);

                // Clears ZLPEnable to show it has been sent.
                pipeTransferPtr->ZLPEnable = false;
            }
            else
            {
                // Everything has been sent, return transfer status to OK.
                pipeTransferPtr->status = USB_PIPE_TRANSFER_OK;
            }

            status = SUCCESS;
        }
        else
        {
            uint16_t endpointSize = USB_EndpointSizeGet(pipe);
            if ((0u == endpointStaticConfig[pipe.address].InMultipktEnable) && (nextTransactionSize > endpointSize))
            {
                // Only send endpoint size packet per transaction when MultiPacket is disabled.
                nextTransactionSize = endpointSize;
            }
            else
            {
                // Check if a manual ZLP is needed after transaction, if transaction size is a multiple of endpoint size.
                pipeTransferPtr->ZLPEnable = (pipeTransferPtr->ZLPEnable) && (0U == (nextTransactionSize % (uint16_t)endpointSize));
            }

            // Configure where to transfer from.
            status = EndpointBufferSet(pipe, &pipeTransferPtr->transferDataPtr[pipeTransferPtr->bytesTransferred]);

            // Send transaction
            if (SUCCESS == status)
            {
                USB_NumberBytesToSendSet(pipe.address, nextTransactionSize);
                USB_NumberBytesSentReset(pipe.address);
                USB_EndpointInNAKClear(pipe.address);
            }
        }
    }

    return status;
}

RETURN_CODE_t USB_OutTransactionRun(USB_PIPE_t pipe)
{
    USB_PIPE_TRANSFER_t *pipeTransferPtr = &pipeTransfer[PipeTransferIndexGet(pipe)];
    RETURN_CODE_t status = UNINITIALIZED;

    if (USB_EP_DIR_OUT != pipe.direction)
    {
        // Pipe is IN, return error code.
        status = ENDPOINT_DIRECTION_ERROR;
    }
    else
    {
        // Make sure the transfer status is busy.
        pipeTransferPtr->status = USB_PIPE_TRANSFER_BUSY;

        // Update the data pointer for the next transaction.
        status = EndpointBufferSet(pipe, &pipeTransferPtr->transferDataPtr[pipeTransferPtr->bytesTransferred]);

        // Calculate the size of next transaction.
        uint16_t endpointSize = USB_EndpointSizeGet(pipe);
        uint16_t nextTransactionSize = pipeTransferPtr->transferDataSize - pipeTransferPtr->bytesTransferred;
        if (0u == endpointStaticConfig[pipe.address].OutMultipktEnable)
        {
            if (nextTransactionSize < endpointSize)
            {
                // Temporarily enable MultiPacket to avoid receiving data that overflows endpoint buffer.
                USB_EndpointOutMultipktEnable(pipe.address);
            }
            else
            {
                // Only expect one endpoint size packet per transaction when MultiPacket is disabled.
                if (nextTransactionSize > endpointSize)
                {
                    nextTransactionSize = endpointSize;
                }

                // Disable MultiPacket in case it was enabled for previous transaction.
                USB_EndpointOutMultipktDisable(pipe.address);
            }
        }

        if (0u == nextTransactionSize)
        {
            // Clear ZLPEnable to indicate that the transfer is completed and the ZLP transfer is initated.
            pipeTransferPtr->ZLPEnable = false;

            // Everything has been sent, return transfer status to OK.
            pipeTransferPtr->status = USB_PIPE_TRANSFER_OK;
        }
        else
        {
            // Check if a manual ZLP is needed after transaction, if transaction size is a multiple of endpoint size.
            pipeTransferPtr->ZLPEnable = pipeTransferPtr->ZLPEnable && (0u == (nextTransactionSize % endpointSize));
        }

        // Start the transaction
        USB_NumberBytesReceivedReset(pipe.address);
        USB_NumberBytesToReceiveSet(pipe.address, nextTransactionSize);
        USB_EndpointOutNAKClear(pipe.address);
    }

    return status;
}

RETURN_CODE_t USB_PipeTransactionComplete(USB_PIPE_t pipe)
{
    USB_PIPE_TRANSFER_t *pipeTransferPtr = &pipeTransfer[PipeTransferIndexGet(pipe)];
    RETURN_CODE_t status = UNINITIALIZED;
    uint16_t transactionSize;

    if (USB_EP_DIR_IN == pipe.direction)
    {
        // Transaction complete on IN.
        if (USB_EndpointInMultipktIsEnabled(pipe.address) == true)
        {
            // With multipacket enabled we know exactly what got transferred.
            transactionSize = USB_NumberBytesSentGet(pipe.address);
        }
        else
        {
            // With multipacket disabled we know what we meant to transfer.
            transactionSize = USB_NumberBytesToSendGet(pipe.address);
        }

        // Check if we need to send more data, or ZLP.
        pipeTransferPtr->bytesTransferred += transactionSize;
        if ((pipeTransferPtr->bytesTransferred != pipeTransferPtr->transferDataSize) || (pipeTransferPtr->ZLPEnable))
        {
            status = USB_InTransactionRun(pipe);
        }
        else
        {
            pipeTransferPtr->status = USB_PIPE_TRANSFER_OK;
            status = SUCCESS;
        }
    }
    else
    {
        // Transaction complete on OUT.
        transactionSize = USB_NumberBytesReceivedGet(pipe.address);

        // Checks if we have transferred more than we wanted.
        uint16_t expectedTransferRemainingSize = pipeTransferPtr->transferDataSize - pipeTransferPtr->bytesTransferred;
        if (expectedTransferRemainingSize < transactionSize)
        {
            // We may have overflowed the receive location!
            if (USB_NumberBytesToReceiveGet(pipe.address) == expectedTransferRemainingSize)
            {
                // Multipacket has limited what we received, even if transactionSize is larger.
                transactionSize = expectedTransferRemainingSize;
            }
            else
            {
                pipeTransferPtr->status = USB_PIPE_TRANSFER_ERROR;
                status = PIPE_TRANSFER_ERROR;
            }
        }

        if (PIPE_TRANSFER_ERROR != status)
        {
            // Updates bytes transfered and check if we need to run more transactions.
            pipeTransferPtr->bytesTransferred += transactionSize;

            if (((pipeTransferPtr->bytesTransferred < pipeTransferPtr->transferDataSize) || pipeTransferPtr->ZLPEnable) && (0u == (transactionSize % USB_EndpointSizeGet(pipe))))
            {
                status = USB_OutTransactionRun(pipe);
            }
            else
            {
                pipeTransferPtr->status = USB_PIPE_TRANSFER_OK;
                status = SUCCESS;
            }
        }
    }

    // Checks if transfer is completed and cleans up.
    if (USB_PIPE_TRANSFER_BUSY != pipeTransferPtr->status)
    {
        USB_PipeTransferEndCallback(pipe);
    }

    return status;
}
