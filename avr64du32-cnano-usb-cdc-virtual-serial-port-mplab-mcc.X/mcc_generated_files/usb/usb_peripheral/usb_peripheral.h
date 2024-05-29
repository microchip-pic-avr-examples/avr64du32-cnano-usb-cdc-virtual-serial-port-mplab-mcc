/**
 * USBPERIPHERAL Peripheral Header File
 * @file usb_peripheral.h
 * @defgroup usb_peripheral USB Peripheral Hardware Abstraction Layer (HAL)
 * @brief Interface for a USB peripheral module that needs to be implemented by a device-specific USB module driver.
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

#ifndef USB_PERIPHERAL_H
// cppcheck-suppress misra-c2012-2.5
#define USB_PERIPHERAL_H

#include <stdbool.h>
#include <stdint.h>

#include <usb_common_elements.h>
#include <usb_peripheral_endpoint.h>
#include <usb_peripheral_read_write.h>
#include <usb_protocol_headers.h>

/**
 * @ingroup usb_peripheral
 * @struct USB_CONTROL_TRANSFER_t
 * @brief The data structure for internally handling control transfers, either IN or OUT.
 */
typedef struct USB_CONTROL_TRANSFER_struct
{
    uint8_t buffer[64];                                     /**<Default buffer for control data transfers*/
    volatile USB_CONTROL_STATUS_t status;                   /**<The status of a transfer on this pipe*/
    uint8_t *transferDataPtr;                               /**<Location in RAM to send or fill during transfer*/
    uint16_t transferDataSize;                              /**<Number of bytes to transfer to or from RAM location*/
    uint16_t totalBytesTransferred;                         /**<Number of data transfered last transaction*/
    USB_SETUP_PROCESS_CALLBACK_t processSetupCallback;      /**<Callback to call during setup process*/
    USB_SETUP_OVERUNDERRUN_CALLBACK_t overUnderRunCallback; /**<Callback to call on a control overrun or underrun*/
    USB_SETUP_ENDOFREQUEST_CALLBACK_t endOfRequestCallback; /**<Callback to call when a setup request is complete*/
    USB_SETUP_REQUEST_t setupRequest;                       /**<Setup request packet*/
} USB_CONTROL_TRANSFER_t;

/**
 * @ingroup usb_peripheral
 * @brief Detects if the Setup event was received.
 * @param None.
 * @retval 0 - Setup event was not received
 * @retval 1 - Setup event was received
 */
bool USB_SetupIsReceived(void);

/**
 * @ingroup usb_peripheral
 * @brief Detects if the Start-of-Frame (SOF) event was received.
 * @param None.
 * @retval 0 - SOF event was not received
 * @retval 1 - SOF event was received
 */
bool USB_EventSOFIsReceived(void);

/**
 * @ingroup usb_peripheral
 * @brief Clears the SOF event.
 * @param None.
 * @return None.
 */
void USB_EventSOFClear(void);

/**
 * @ingroup usb_peripheral
 * @brief Detects if the Reset event was received.
 * @param None.
 * @retval 1 - Reset event was received
 * @retval 0 - Reset event was not received
 */
bool USB_EventResetIsReceived(void);

/**
 * @ingroup usb_peripheral
 * @brief Clears the Reset event.
 * @param None.
 * @return None.
 */
void USB_EventResetClear(void);

/**
 * @ingroup usb_peripheral
 * @brief Detects if an Overflow and/or Underflow event was received.
 * @param None.
 * @return A value representing the events received
 */
uint8_t USB_EventOverUnderflowIsReceived(void);

/**
 * @ingroup usb_peripheral
 * @brief Detects if an Overflow and/or Underflow event was received on the control endpoints.
 * @param None.
 * @return A value representing the events received
 */
uint8_t USB_ControlOverUnderflowIsReceived(void);

/**
 * @ingroup usb_peripheral
 * @brief Clears the Over/Underflow event.
 * @param None.
 * @return None.
 */
void USB_EventOverUnderflowClear(void);

/**
 * @ingroup usb_peripheral
 * @brief Detects if a Suspend event was received.
 * @param None.
 * @return A boolean value representing the Suspend event received condition
 * @retval 0 - Suspend event was not received
 * @retval 1 - Suspend event was received
 */
bool USB_EventSuspendIsReceived(void);

/**
 * @ingroup usb_peripheral
 * @brief Clears the Suspend event.
 * @param None.
 * @return None.
 */
void USB_EventSuspendClear(void);

/**
 * @ingroup usb_peripheral
 * @brief Detects if a Resume event was received.
 * @param None.
 * @retval 0 - Resume event was not received
 * @retval 1 - Resume event was received
 */
bool USB_EventResumeIsReceived(void);

/**
 * @ingroup usb_peripheral
 * @brief Clears the Resume event.
 * @param None.
 * @return None.
 */
void USB_EventResumeClear(void);

/**
 * @ingroup usb_peripheral
 * @brief Detects if a Stalled event was received.
 * @param None.
 * @retval 0 - Stalled event was not received
 * @retval 1 - Stalled event was received
 */
bool USB_EventStalledIsReceived(void);

/**
 * @ingroup usb_peripheral
 * @brief Clears the Stalled event.
 * @param None.
 * @return None.
 */
void USB_EventStalledClear(void);

/**
 * @ingroup usb_peripheral
 * @brief Attaches the device to the USB bus.
 * @param None.
 * @return None.
 */
void USB_BusAttach(void);

/**
 * @ingroup usb_peripheral
 * @brief Detaches the device from the USB bus.
 * @param None.
 * @return None.
 */
void USB_BusDetach(void);

/**
 * @ingroup usb_peripheral
 * @brief Checks if the device is attached to the USB bus not.
 * @param None.
 * @retval 0 - USB bus is not attached
 * @retval 1 - USB bus is attached
 */
bool USB_IsBusAttached(void);

/**
 * @ingroup usb_peripheral
 * @brief Sets the device address.
 * @param deviceAddress - Device address to set
 * @return None.
 */
void USB_DeviceAddressConfigure(uint8_t deviceAddress);

/**
 * @ingroup usb_peripheral
 * @brief Gets the current frame number.
 * @param None.
 * @return 15-bit frame number
 */
uint16_t USB_FrameNumberGet(void);

/**
 * @ingroup usb_peripheral
 * @brief Ensures correct control endpoint initialization.
 * @param None.
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_ControlEndpointsInit(void);

/**
 * @ingroup usb_peripheral
 * @brief Verifies the received control setup.
 * @param None.
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_ControlSetupReceived(void);

/**
 * @ingroup usb_peripheral
 * @brief Handles completed transactions on the control endpoints. Checks and verifies data OUT, data IN, ZLP OUT and ZLP IN.
 * @param pipe - A combination of endpoint address and direction
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_ControlTransactionComplete(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral
 * @brief Sends ZLP OUT and ZLP IN transactions on the control endpoints.
 * @param direction - The endpoint direction to send the ZLP
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_ControlTransferZLP(uint8_t direction);

/**
 * @ingroup usb_peripheral
 * @brief Ensures correct control transfer reset.
 * @param None.
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_ControlTransferReset(void);

/**
 * @ingroup usb_peripheral
 * @brief Updates the transfer data pointer and size in ControlTransfer.
 * @param *dataPtr - Pointer to new data
 * @param dataSize - Number of elements in the array
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_ControlTransferDataSet(uint8_t *dataPtr, uint16_t dataSize);

/**
 * @ingroup usb_peripheral
 * @brief Copies data to the transfer buffer and sets the transfer data pointer and size in ControlTransfer.
 * @param *dataPtr - Pointer to data to copy
 * @param dataSize - Number of elements in the array
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_ControlTransferDataWriteBuffer(uint8_t *dataPtr, uint8_t dataSize);

/**
 * @ingroup usb_peripheral
 * @brief Sets the callback for end of a control request.
 * @param callback - The function to call for the end of a control request
 * @return None.
 */
void USB_ControlEndOfRequestCallbackRegister(USB_SETUP_ENDOFREQUEST_CALLBACK_t callback);

/**
 * @ingroup usb_peripheral
 * @brief Sets the callback for the setup processing.
 * @param callback - The function to call for the setup processing
 * @return None.
 */
void USB_ControlProcessSetupCallbackRegister(USB_SETUP_PROCESS_CALLBACK_t callback);

/**
 * @ingroup usb_peripheral
 * @brief Sets the callback for a control overrun or underrun.
 * @param callback - The function to call on a control overrun or underrun
 * @return None.
 */
void USB_ControlOverUnderRunCallbackRegister(USB_SETUP_OVERUNDERRUN_CALLBACK_t callback);

/**
 * @ingroup usb_peripheral
 * @brief Handles the control Over/Underflow events.
 * @param overunderflow - A value representing overflow or underflow
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_ControlProcessOverUnderflow(uint8_t overunderflow);

/**
 * @ingroup usb_peripheral
 * @brief Handles the Stall events.
 * @param pipe - A combination of endpoint address and direction
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_HandleEventStalled(USB_PIPE_t pipe);

/**
 * @ingroup usb_peripheral
 * @brief Enables the peripheral and the frame number, enables and resets FIFO, sets the endpoint table address and max endpoints.
 * @param None.
 * @return None.
 */
void USB_PeripheralInitialize(void);

/**
 * @ingroup usb_peripheral
 * @brief Disables the USB peripheral and aborts any ongoing transaction.
 * @param None.
 * @return None.
 */
void USB_PeripheralDisable(void);

#endif /* USB_PERIPHERAL_H */
