/**
 * USBCDCVIRTUALSERIAL CDC Virtual Serial Port Header File
 * @file usb_cdc_virtual_serial_port.h
 * @ingroup usb_cdc
 * @brief This file contains prototypes and datatypes for a CDC application
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

#ifndef USB_CDC_VIRTUAL_SERIAL_PORT_H
#define USB_CDC_VIRTUAL_SERIAL_PORT_H

#include <stdint.h>
#include <stdbool.h>
#include <usb_core.h>
#include <usb_common_elements.h>
#include <usb_protocol_cdc.h>

/**
 * @ingroup usb_cdc
 * @enum CDC_RETURN_CODE_t
 * @brief Type define for the CDC return codes.
 */
typedef enum CDC_RETURN_CODE_enum
{
    CDC_SUCCESS = 0,      /**<Action successfully executed*/
    CDC_BUFFER_FULL = -1, /**<Error triggered by full CDC buffer*/
    CDC_BUFFER_EMPTY = -2 /**<Error triggered by empty CDC buffer*/
} CDC_RETURN_CODE_t;

/**
 * @ingroup usb_cdc
 * @brief Initializes the CDC Virtual Serial Port functionality.
 * @param None.
 * @return None.
 */
void USB_CDCVirtualSerialPortInitialize(void);

/**
 * @ingroup usb_cdc
 * @brief Performs Virtual Serial Port writes using the CDC class.
 * @param None.
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_CDCVirtualSerialPortHandler(void);

/**
 * @ingroup usb_cdc
 * @brief Pulls data from the CDC receive buffer.
 * @param buffer - Pointer to application receive buffer
 * @return status - Result of the called circular buffer function
 */
CDC_RETURN_CODE_t USB_CDCRead(uint8_t *data);

/**
 * @ingroup usb_cdc
 * @brief Adds data to the CDC transmit buffer.
 * @param data - Pointer to data to be transmitted
 * @param length - Length in number of bytes for data to be transmitted
 * @return status - Result of the called circular buffer function
 */
CDC_RETURN_CODE_t USB_CDCWrite(uint8_t data);

/**
 * @ingroup usb_cdc
 * @brief Checks if the transmit buffer is full.
 * @param None.
 * @retval 0 - Buffer not full
 * @retval 1 - Buffer full
 */
bool USB_CDCTxBusy(void);

/**
 * @ingroup usb_cdc
 * @brief Callback function called after the USB IN transaction started.
 * @param pipe - USB pipe used for the started transaction
 * @param status - Transfer status
 * @param bytesTransferred - Number of bytes transmitted in the transaction
 * @return None.
 */
void USB_CDCDataTransmitted(USB_PIPE_t pipe, USB_TRANSFER_STATUS_t status, uint16_t bytesTransferred);

/**
 * @ingroup usb_cdc
 * @brief Callback function called after the USB OUT transaction started.
 * @param pipe - USB pipe used for the started transaction
 * @param status - Transfer status
 * @param bytesTransferred - Number of bytes received in the transaction
 * @return None.
 */
void USB_CDCDataReceived(USB_PIPE_t pipe, USB_TRANSFER_STATUS_t status, uint16_t bytesTransferred);

#endif /* USB_CDC_VIRTUAL_SERIAL_PORT_H */