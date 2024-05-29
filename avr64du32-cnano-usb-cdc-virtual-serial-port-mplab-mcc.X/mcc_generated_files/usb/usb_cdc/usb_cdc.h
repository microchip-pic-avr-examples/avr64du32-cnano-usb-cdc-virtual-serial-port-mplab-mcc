/**
 * USBCDC CDC Header File
 * @file usb_cdc.h
 * @defgroup usb_cdc USB Communications Device Class (CDC)
 * @brief This file contains prototypes and data types for a CDC application
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

#ifndef USB_CDC_H
#define USB_CDC_H

#include <usb_common_elements.h>
#include <usb_protocol_cdc.h>
#include <usb_protocol_headers.h>

/**
 * @ingroup usb_cdc
 * @brief Initializes the CDC class.
 * @param None.
 * @return None.
 */
void USB_CDCInitialize(void);

/**
 * @ingroup usb_cdc
 * @brief Performs handling of control transfers.
 * @param setupRequestPtr - Pointer to the Setup Request struct
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_CDCRequestHandler(USB_SETUP_REQUEST_t *setupRequestPtr);

/**
 * @ingroup usb_cdc
 * @brief Checks if the Data Terminal Equipment bit has been set from the host.
 * @param None.
 * @retval 0 - False if bit not set
 * @retval 1 - True if bit set
 */
bool USB_CDCDataTerminalReady(void);

/**
 * @ingroup usb_cdc
 * @brief Sets the data transfer baud rate for the CDC communication.
 * @param baud - Data transfer baud rate
 * @return None.
 */
void USB_CDCSetBaud(uint16_t baud);

/**
 * @ingroup usb_cdc
 * @brief Gets the data transfer baud rate for the CDC communication.
 * @param None.
 * @return baud - Data transfer baud rate
 */
uint32_t USB_CDCGetBaud(void);

/**
 * @ingroup usb_cdc
 * @brief Sets the number of data transfer stop bits for the CDC communication.
 * @param numStopBits - Number of stop bits
 * @return None.
 */
void USB_CDCSetStopBits(USB_CDC_LINE_CODING_STOP_BITS_t numStopBits);

/**
 * @ingroup usb_cdc
 * @brief Gets the number of data transfer stop bits for the CDC communication.
 * @param None.
 * @return numStopBits - Number of stop bits
 */
USB_CDC_LINE_CODING_STOP_BITS_t USB_CDCGetStopBits(void);

/**
 * @ingroup usb_cdc
 * @brief Sets the data transfer parity for the CDC communication.
 * @param parity - Data transfer parity
 * @return None.
 */
void USB_CDCSetParity(USD_CDC_LINE_CODING_PARITY_t parity);

/**
 * @ingroup usb_cdc
 * @brief Gets the data transfer parity for the CDC communication.
 * @param None.
 * @return parity - Data transfer parity
 */
USD_CDC_LINE_CODING_PARITY_t USB_CDCGetParity(void);

/**
 * @ingroup usb_cdc
 * @brief Sets the number of data transfer data bits for the CDC communication.
 * @param numDataBits - Number of data bits
 * @return None.
 */
void USB_CDCSetDataBits(USD_CDC_LINE_CODING_DATA_BITS_t numDataBits);

/**
 * @ingroup usb_cdc
 * @brief Gets the number of data transfer data bits for the CDC communication.
 * @param None.
 * @return numDataBits - Number of data bits
 */
USD_CDC_LINE_CODING_DATA_BITS_t USB_CDCGetDataBits(void);

#endif /* USB_CDC_H */