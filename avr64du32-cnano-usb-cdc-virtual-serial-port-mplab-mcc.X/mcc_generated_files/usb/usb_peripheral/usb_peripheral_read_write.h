/**
 * USBPERIPHERALREADWRITE Peripheral Read/Write Header File
 * @file usb_peripheral_read_write.h
 * @defgroup usb_peripheral_read_write USB Peripheral Read/Write
 * @ingroup usb_peripheral
 * @brief API module for usb_peripheral covering low-level USB transaction functions.
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

#ifndef USB_PERIPHERAL_READ_WRITE_H
// cppcheck-suppress misra-c2012-2.5
#define USB_PERIPHERAL_READ_WRITE_H

#include <stdbool.h>
#include <stdint.h>

#include "usb_common_elements.h"
#include "usb_protocol_headers.h"

/**
 * @ingroup usb_peripheral_read_write
 * @brief Starts sending or receiving data on an endpoint by clearing BUSNACK.
 * Used as a final step while setting up a transaction on the bus.
 * @param pipe - A combination of endpoint address and direction
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_TransactionStart(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_read_write
 * @brief Aborts the next transaction on an endpoint by setting BUSNACK.
 * Used to stop exchanging data on an endpoint. The device will start NAKing requests from the host after calling this API.
 * @param pipe - A combination of endpoint address and direction
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_TransactionAbort(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_read_write
 * @brief Acknowledges the Transaction Complete status condition by clearing the Transaction Complete status bit.
 * Used to clear the Transaction Complete status bit after a transaction has successfully completed.
 * @param pipe - A combination of endpoint address and direction
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_TransactionCompleteAck(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_read_write
 * @brief Helper function to return the endpoint transaction complete condition.
 * @param None.
 * @retval 0 - Transaction not complete or pipe address is out of bounds
 * @retval 1 - Transaction is complete
 */
bool USB_TransactionIsCompleted(void);

/**
 * @ingroup usb_peripheral_read_write
 * @brief Returns the pipe address and direction for the latest completed transaction.
 * @param pipe - A combination of endpoint address and direction
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_TransactionCompletedPipeGet(USB_PIPE_t *pipe);

/**
 * @ingroup usb_peripheral_read_write
 * @brief Resets the pipe.
 * @param pipe - A combination of endpoint address and direction
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_PipeReset(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_read_write
 * @brief Gets the current status of pipe.
 * @param pipe - A combination of endpoint address and direction
 * @return USB_PIPE_TRANSFER_OK or an Error code according to USB_TRANSFER_STATUS_t
 */
USB_TRANSFER_STATUS_t USB_PipeStatusGet(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_read_write
 * @brief Checks if the pipe status is busy.
 * @param pipe - A combination of endpoint address and direction
 * @retval 0  -  Pipe status not busy
 * @retval 1  -  Pipe status is busy
 */
bool USB_PipeStatusIsBusy(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_read_write
 * @brief Configures the pointer for the data transfer in a given pipe.
 * @param pipe - A combination of endpoint address and direction
 * @param *dataPtr - The pointer to the data location
 * @return None.
 */
void USB_PipeDataPtrSet(USB_PIPE_t pipe, uint8_t *dataPtr);

/**
 * @ingroup usb_peripheral_read_write
 * @brief Gets the current data pointer for a given pipe.
 * @param pipe - A combination of endpoint address and direction
 * @return The pointer to the data location
 */
uint8_t *USB_PipeDataPtrGet(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_read_write
 * @brief Sets the size of pipe data to transfer.
 * @param pipe - A combination of endpoint address and direction
 * @param dataSize - The size of pipe data to transfer
 * @return None.
 */
void USB_PipeDataToTransferSizeSet(USB_PIPE_t pipe, uint16_t dataSize);

/**
 * @ingroup usb_peripheral_read_write
 * @brief Gets the size of pipe data to transfer.
 * @param pipe - A combination of endpoint address and direction
 * @return The size of pipe data to transfer
 */
uint16_t USB_PipeDataToTransferSizeGet(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_read_write
 * @brief Gets the size of the transferred pipe data.
 * @param pipe - A combination of endpoint address and direction
 * @return The size of transferred pipe data
 */
uint16_t USB_PipeDataTransferredSizeGet(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_read_write
 * @brief Sets the size of the transferred pipe data.
 * @param pipe - A combination of endpoint address and direction
 * @param dataSize - The size of pipe data transferred
 * @return None.
 */
void USB_PipeDataTransferredSizeSet(USB_PIPE_t pipe, uint16_t dataSize);

/**
 * @ingroup usb_peripheral_read_write
 * @brief Resets the size of transferred pipe data.
 * @param pipe - A combination of endpoint address and direction
 * @return None.
 */
void USB_PipeDataTransferredSizeReset(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_read_write
 * @brief Enables a ZLP on a transfer.
 * It is enabled by default if the AZLP static config is enabled for the pipe.
 * @param pipe - A combination of endpoint address and direction
 * @return None.
 */
void USB_PipeTransferZLP_Enable(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_read_write
 * @brief Sets the callback for transfer end.
 * @param pipe - A combination of endpoint address and direction
 * @param callback - A combination of pipe, status and transferred bytes
 * @return None.
 */
void USB_PipeTransferEndCallbackRegister(USB_PIPE_t pipe, USB_TRANSFER_END_CALLBACK_t callback);

/**
 * @ingroup usb_peripheral_read_write
 * @brief Calls the callback for transfer end.
 * @param pipe - A combination of endpoint address and direction
 * @return None.
 */
void USB_PipeTransferEndCallback(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_read_write
 * @brief Checks the correctness of IN transactions and runs them.
 * @param pipe - A combination of endpoint address and direction
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_InTransactionRun(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_read_write
 * @brief Checks the correctness OUT transactions and runs them.
 * @param pipe - A combination of endpoint address and direction
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_OutTransactionRun(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_read_write
 * @brief Handles completed IN and OUT transactions.
 * Processes the completed transaction and either completes the transfer or runs the next transaction.
 * Will call the pipe transferEndCallback at the end of transfer, if configured.
 * @param pipe - A combination of endpoint address and direction
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_PipeTransactionComplete(USB_PIPE_t pipe);

#endif /* USB_PERIPHERAL_READ_WRITE_H */
