/**
 * USBPERIPHERALENDPOINT Peripheral Endpoint Header File
 * @file usb_peripheral_endpoint.h
 * @defgroup usb_peripheral_endpoint USB Peripheral Endpoint
 * @ingroup usb_peripheral
 * @brief API module for usb_peripheral_endpoint covering endpoint-related functions.
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

#ifndef USB_PERIPHERAL_ENDPOINT_H
// cppcheck-suppress misra-c2012-2.5
#define USB_PERIPHERAL_ENDPOINT_H

#include <stdbool.h>
#include <stdint.h>

#include "usb_common_elements.h"
#include "usb_protocol_headers.h"

/**
 * @ingroup usb_peripheral_endpoint
 * @brief Configures the endpoint with the desired settings using the Control and Status Register.
 * Used to set up an endpoint before using it in an application.
 * Sets up all the control register settings by looking up the usb_config.h file and clears the count registers.
 * @param pipe - A combination of endpoint address and direction
 * @param endpointSize - Number of bytes of data supported by the endpoint in one USB transaction
 * @param endpointType - Type of USB endpoint as defined by usb_endpoint_type
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_EndpointConfigure(USB_PIPE_t pipe, uint16_t endpointSize, USB_ENDPOINT_t endpointType);

/**
 * @ingroup usb_peripheral_endpoint
 * @brief Disables the endpoint by setting the endpoint type to 0x00.
 * @param pipe - A combination of endpoint address and direction
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_EndpointDisable(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_endpoint
 * @brief Helper function to return the endpoint size.
 * @param pipe - A combination of endpoint address and direction
 * @return The size of the endpoint
 */
uint16_t USB_EndpointSizeGet(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_endpoint
 * @brief Helper function to return the endpoint type.
 * @param pipe - A combination of endpoint address and direction
 * @return The endpoint type
 */
USB_ENDPOINT_t USB_EndpointTypeGet(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_endpoint
 * @brief Helps stall an endpoint when a command received from the host is invalid or unrecognizable.
 * Used if the host sends data that is not supported by the device.
 * @param pipe - A combination of endpoint address and direction
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_EndpointStall(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_endpoint
 * @brief Helps clear the Stall condition after the device has recovered from an unsupported command from the host.
 * Used to reset stall before the next USB transfer.
 * Used when the host issues a clear HALT/Feature request to reset stall.
 * @param pipe - A combination of endpoint address and direction
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_EndpointStallClear(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_endpoint
 * @brief Helper function to return the endpoint Stall condition.
 * @param pipe - A combination of endpoint address and direction
 * @return A boolean value representing the Stall condition. If the pipe address is out of bounds, the function will always return false
 */
bool USB_EndpointIsStalled(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_endpoint
 * @brief Acknowledges the stall status condition by clearing the Stall Status bit.
 * Used to clear the Stall Status bit after a stall has been detected.
 * @param pipe - A combination of endpoint address and direction
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_EndpointStalledConditionAck(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_endpoint
 * @brief Sets the Data Toggle bit on an endpoint which is used to ensure correct data sequence.
 * Only used if hardware data toggling is not available.
 * After a successful transaction, toggle the Data Toggle bit.
 * For SETUP transactions, ensure that the SETUP stage clears the Data Toggle bit,
 * while the data stage and status stage set the Data Toggle bit.
 * @param pipe - A combination of endpoint address and direction
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_DataToggleSet(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_endpoint
 * @brief Clears the Data Toggle bit on an endpoint which is used to ensure correct data sequence.
 * Only used if hardware data toggling is not available.
 * After a successful transaction, toggle the Data Toggle bit.
 * For SETUP transactions, ensure that the SETUP stage clears the Data Toggle bit,
 * while the data stage and status stage set the Data Toggle bit.
 * @param pipe - A combination of endpoint address and direction
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_DataToggleClear(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_endpoint
 * @brief Toggles the Data Toggle bit on an endpoint which is used to ensure correct data sequence.
 * Only used if hardware data toggling is not available.
 * After a successful transaction, toggle the Data Toggle bit.
 * For SETUP transactions, ensure that the SETUP stage clears the Data Toggle bit,
 * while the data stage and status stage set the Data Toggle bit.
 * @param pipe - A combination of endpoint address and direction
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_DataToggle(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral_endpoint
 * @brief Converts an endpoint size in number of bytes into a register setting.
 * Converts the endpoint size bit mask based on the EP_BUFSIZE setting of the endpoint control register.
 * @param endpointSize - The size to convert
 * @param endpointType - The endpoint type
 * @param endpointMaskPtr - Pointer to the mask variable to write to
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t ConvertEndpointSizeToMask(uint16_t endpointSize, USB_ENDPOINT_t endpointType, uint8_t *endpointMaskPtr);

/**
 * @ingroup usb_peripheral_endpoint
 * @brief Configures the endpoint data buffer to a location in RAM for the next transaction.
 * @param pipe - A combination of endpoint address and direction
 * @param bufAddress - The pointer to the data buffer the endpoint will use
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t EndpointBufferSet(USB_PIPE_t pipe, uint8_t *bufAddress);

#endif /* USB_PERIPHERAL_ENDPOINT_H */
