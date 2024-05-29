/**
 * USBPERIPHERALAVRDU Peripheral AVR DU Specific Header File
 * @file usb_peripheral_avr_du.h
 * @defgroup usb_peripheral_avr_du USB Peripheral AVR DU
 * @ingroup usb_peripheral
 * @brief This file encompasses all the register settings of the AVR DU device in the form of inline functions.
 * It also abstracts the Read-Modify-Write loop for STATUS registers, which is required, as the hardware and software can both write
 * into the STATUS register.
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

#ifndef USB_PERIPHERAL_AVR_DU_H
// cppcheck-suppress misra-c2012-2.5
#define USB_PERIPHERAL_AVR_DU_H

#ifdef __XC8
    #include <xc.h>
#else // avr-gcc
    #include <avr/io.h>
#endif

#include <usb_config.h>
#include <usb_protocol_headers.h>

/**
 * @ingroup usb_peripheral_avr_du
 * @def ALWAYS_INLINE
 * @brief Alias that makes always inline function definitions more readable.
 */
#define ALWAYS_INLINE __attribute__((always_inline)) inline

/**
 * @ingroup usb_peripheral_avr_du
 * @struct USB_ENDPOINT_TABLE_struct
 * @brief Represents the endpoint configuration table based on the number of endpoints in use.
 * The table data structure is defined by USB_EP_TABLE_struct in the device header file,
 * modified to support configuration of size from USB_EP_NUM.
 */
typedef struct USB_ENDPOINT_TABLE_struct
{
    register8_t FIFO[USB_EP_NUM * 2u]; /**<FIFO Entry*/
    USB_EP_PAIR_t EP[USB_EP_NUM];      /**<USB Endpoint Register Pairs*/
    register16_t FRAMENUM;             /**<Frame Number*/
} USB_ENDPOINT_TABLE_t;

extern USB_ENDPOINT_TABLE_t endpointTable;

/**
 * @ingroup usb_peripheral_avr_du
 * @struct USB_PIPE_TRANSFER_struct
 * @brief Represents a transfer created for a pipe, either IN or OUT.
 */
typedef struct USB_PIPE_TRANSFER_struct
{
    USB_TRANSFER_STATUS_t status;                    /**<The status of a transfer on this pipe*/
    uint8_t ZLPEnable : 1;                           /**<A Zero Length Packet (ZLP) is enabled for the end of this transfer if the transfer size is a multiple of endpoint size */
    uint8_t reserved  : 7;                           /**<These bits are unused*/
    uint8_t *transferDataPtr;                        /**<Location in RAM to send or fill during transfer*/
    uint16_t transferDataSize;                       /**<Number of bytes to transfer to or from the RAM location*/
    uint16_t bytesTransferred;                       /**<Total number of data transfered*/
    USB_TRANSFER_END_CALLBACK_t transferEndCallback; /**<Callback to call at the end of transfer when transfer_data_size == bytes_transfered, NULL if not used*/
} USB_PIPE_TRANSFER_t;

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Waits until a Read-Modify-Write operation is done.
 * This blocking wait operation is expected to complete within 14 clock cycles.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void WaitUntilRMWDone(void)
{
    while ((USB0.INTFLAGSB & USB_RMWBUSY_bm) != 0u)
    {
        ;
    }
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables the OUT endpoint with the given address.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndPointOutDisable(uint8_t endpointAddress)
{
    (endpointTable.EP[endpointAddress].OUT.CTRL &= (~USB_TYPE_gm));
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables the IN endpoint with the given address.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndPointInDisable(uint8_t endpointAddress)
{
    (endpointTable.EP[endpointAddress].IN.CTRL &= (~USB_TYPE_gm));
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if the OUT endpoint at the given address is enabled.
 * @param endpointAddress - Address of the endpoint
 * @retval 0 Endpoint not enabled
 * @retval 1 Endpoint enabled
 */
static ALWAYS_INLINE bool USB_EndPointOutIsEnabled(uint8_t endpointAddress)
{
    return ((endpointTable.EP[endpointAddress].OUT.CTRL & USB_TYPE_gm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if the IN endpoint at the given address is enabled.
 * @param None.
 * @retval 0 Endpoint not enabled
 * @retval 1 Endpoint enabled
 */
static ALWAYS_INLINE bool USB_EndPointInIsEnabled(uint8_t endpointAddress)
{
    return ((endpointTable.EP[endpointAddress].IN.CTRL & USB_TYPE_gm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Gets the OUT endpoint configuration at the given address.
 * @param endpointAddress - Address of the endpoint
 * @return Endpoint configuration type
 */
static ALWAYS_INLINE uint8_t USB_EndPointOutTypeConfigGet(uint8_t endpointAddress)
{
    return (endpointTable.EP[endpointAddress].OUT.CTRL & USB_TYPE_gm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Gets the IN endpoint configuration at the given address.
 * @param endpointAddress - Address of the endpoint
 * @return Endpoint configuration type
 */
static ALWAYS_INLINE uint8_t USB_EndPointInTypeConfigGet(uint8_t endpointAddress)
{
    return (endpointTable.EP[endpointAddress].IN.CTRL & USB_TYPE_gm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Sets endpoint control OUT.
 * @param endpointAddress - Address of the endpoint
 * @param value - Register bitmask
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointOutControlSet(uint8_t endpointAddress, uint8_t value)
{
    (endpointTable.EP[endpointAddress].OUT.CTRL = (value));
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Sets endpoint control IN.
 * @param endpointAddress - Address of the endpoint
 * @param value - Register bitmask
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointInControlSet(uint8_t endpointAddress, uint8_t value)
{
    (endpointTable.EP[endpointAddress].IN.CTRL = (value));
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Clears OUT endpoint status.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointOutStatusClear(uint8_t endpointAddress)
{
    WaitUntilRMWDone();
    USB0.STATUS[endpointAddress].OUTCLR = ~USB_BUSNAK_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Clears IN endpoint status.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointInStatusClear(uint8_t endpointAddress)
{
    WaitUntilRMWDone();
    USB0.STATUS[endpointAddress].INCLR = ~USB_BUSNAK_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Sets the endpoint size for a default type OUT endpoint.
 * @param endpointAddress - Address of the endpoint
 * @param endpointSizeConfig - Size of endpoint to set
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointOutDefaultSizeSet(uint8_t endpointAddress, uint8_t endpointSizeConfig)
{
    (endpointTable.EP[endpointAddress].OUT.CTRL = (endpointTable.EP[endpointAddress].OUT.CTRL & (~USB_BUFSIZE_DEFAULT_gm)) | ((endpointSizeConfig)&USB_BUFSIZE_DEFAULT_gm));
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Sets the endpoint size for a default type IN endpoint.
 * @param endpointAddress - Address of the endpoint
 * @param endpointSizeConfig - Size of endpoint to set
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointInDefaultSizeSet(uint8_t endpointAddress, uint8_t endpointSizeConfig)
{
    (endpointTable.EP[endpointAddress].IN.CTRL = (endpointTable.EP[endpointAddress].IN.CTRL & (~USB_BUFSIZE_DEFAULT_gm)) | ((endpointSizeConfig)&USB_BUFSIZE_DEFAULT_gm));
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Sets the endpoint size for an isochronous OUT endpoint.
 * @param endpointAddress - Address of the endpoint
 * @param endpointSizeConfig - Size of endpoint to set
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointOutIsoSizeSet(uint8_t endpointAddress, uint8_t endpointSizeConfig)
{
    (endpointTable.EP[endpointAddress].OUT.CTRL = (endpointTable.EP[endpointAddress].OUT.CTRL & (~USB_BUFSIZE_ISO_gm)) | ((endpointSizeConfig)&USB_BUFSIZE_ISO_gm));
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Sets the endpoint size for an isochronous IN endpoint.
 * @param endpointAddress - Address of the endpoint
 * @param endpointSizeConfig - Size of endpoint to set
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointInIsoSizeSet(uint8_t endpointAddress, uint8_t endpointSizeConfig)
{
    (endpointTable.EP[endpointAddress].IN.CTRL = (endpointTable.EP[endpointAddress].IN.CTRL & (~USB_BUFSIZE_ISO_gm)) | ((endpointSizeConfig)&USB_BUFSIZE_ISO_gm));
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Gets the size of a default type OUT endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return OUT endpoint size
 */
static ALWAYS_INLINE uint8_t USB_EndpointOutDefaultSizeGet(uint8_t endpointAddress)
{
    return (endpointTable.EP[endpointAddress].OUT.CTRL & USB_BUFSIZE_DEFAULT_gm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Gets the size of a default type IN endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return IN endpoint size
 */
static ALWAYS_INLINE uint8_t USB_EndpointInDefaultSizeGet(uint8_t endpointAddress)
{
    return (endpointTable.EP[endpointAddress].IN.CTRL & USB_BUFSIZE_DEFAULT_gm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Gets the size of an isochronous OUT endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return OUT endpoint size
 */
static ALWAYS_INLINE uint8_t USB_EndpointOutIsoSizeGet(uint8_t endpointAddress)
{
    return (endpointTable.EP[endpointAddress].OUT.CTRL & USB_BUFSIZE_ISO_gm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Gets the size of an isochronous IN endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return IN endpoint size
 */
static ALWAYS_INLINE uint8_t USB_EndpointInIsoSizeGet(uint8_t endpointAddress)
{
    return (endpointTable.EP[endpointAddress].IN.CTRL & USB_BUFSIZE_ISO_gm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables transaction complete interrupt for the specified OUT endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointOutTransactionCompleteInterruptEnable(uint8_t endpointAddress)
{
    (endpointTable.EP[endpointAddress].OUT.CTRL &= ~USB_TCDSBL_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables transaction complete interrupt for the specified IN endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointInTransactionCompleteInterruptEnable(uint8_t endpointAddress)
{
    (endpointTable.EP[endpointAddress].IN.CTRL &= ~USB_TCDSBL_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables transaction complete interrupt for the specified OUT endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointOutTransactionCompleteInterruptDisable(uint8_t endpointAddress)
{
    (endpointTable.EP[endpointAddress].OUT.CTRL |= USB_TCDSBL_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables transaction complete interrupt for the specified IN endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointInTransactionCompleteDisable(uint8_t endpointAddress)
{
    (endpointTable.EP[endpointAddress].IN.CTRL |= USB_TCDSBL_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables multipacket for the specified OUT endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointOutMultipktEnable(uint8_t endpointAddress)
{
    (endpointTable.EP[endpointAddress].OUT.CTRL |= USB_MULTIPKT_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables multipacket for the specified IN endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointInMultipktEnable(uint8_t endpointAddress)
{
    (endpointTable.EP[endpointAddress].IN.CTRL |= USB_MULTIPKT_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables multipacket for the specified OUT endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointOutMultipktDisable(uint8_t endpointAddress)
{
    (endpointTable.EP[endpointAddress].OUT.CTRL &= ~USB_MULTIPKT_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables multipacket for the specified IN endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointInMultipktDisable(uint8_t endpointAddress)
{
    (endpointTable.EP[endpointAddress].IN.CTRL &= ~USB_MULTIPKT_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if multipacket is enabled on the specified OUT endpoint.
 * @param endpointAddress - Address of the endpoint
 * @retval 0 - Multipacket disabled
 * @retval 1 - Multipacket enabled
 */
static ALWAYS_INLINE bool USB_EndpointOutMultipktIsEnabled(uint8_t endpointAddress)
{
    return ((endpointTable.EP[endpointAddress].OUT.CTRL & USB_MULTIPKT_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if multipacket is enabled on the specified IN endpoint.
 * @param endpointAddress - Address of the endpoint
 * @retval 0 - Multipacket disabled
 * @retval 1 - Multipacket enabled
 */
static ALWAYS_INLINE bool USB_EndpointInMultipktIsEnabled(uint8_t endpointAddress)
{
    return ((endpointTable.EP[endpointAddress].IN.CTRL & USB_MULTIPKT_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables Auto Zero Length Packet (AZLP) on the specified OUT endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointOutAzlpEnable(uint8_t endpointAddress)
{
    (endpointTable.EP[endpointAddress].OUT.CTRL |= USB_AZLP_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables AZLP on the specified IN endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointInAlzpEnable(uint8_t endpointAddress)
{
    (endpointTable.EP[endpointAddress].IN.CTRL |= USB_AZLP_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables AZLP on the specified OUT endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointOutAzlpDisable(uint8_t endpointAddress)
{
    (endpointTable.EP[endpointAddress].OUT.CTRL &= ~USB_AZLP_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables AZLP on the specified IN endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointInAzlpDisable(uint8_t endpointAddress)
{
    (endpointTable.EP[endpointAddress].IN.CTRL &= ~USB_AZLP_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Stalls the specified OUT endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointOutStall(uint8_t endpointAddress)
{
    (endpointTable.EP[endpointAddress].OUT.CTRL |= USB_DOSTALL_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Stalls the specified IN endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointInStall(uint8_t endpointAddress)
{
    (endpointTable.EP[endpointAddress].IN.CTRL |= USB_DOSTALL_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Stops stalling the specified OUT endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointOutStallClear(uint8_t endpointAddress)
{
    (endpointTable.EP[endpointAddress].OUT.CTRL &= ~USB_DOSTALL_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Stops stalling the specified IN endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointInStallClear(uint8_t endpointAddress)
{
    (endpointTable.EP[endpointAddress].IN.CTRL &= ~USB_DOSTALL_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if the specified OUT endpoint is stalled.
 * @param endpointAddress - Address of the endpoint
 * @retval 0 - Endpoint is not stalled
 * @retval 1 - Endpoint is stalled
 */
static ALWAYS_INLINE bool USB_EndpointOutIsStalled(uint8_t endpointAddress)
{
    return ((endpointTable.EP[endpointAddress].OUT.CTRL & USB_DOSTALL_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if the specified IN endpoint is stalled.
 * @param endpointAddress - Address of the endpoint
 * @retval 0 - Endpoint is not stalled
 * @retval 1 - Endpoint is stalled
 */
static ALWAYS_INLINE bool USB_EndpointInIsStalled(uint8_t endpointAddress)
{
    return ((endpointTable.EP[endpointAddress].IN.CTRL & USB_DOSTALL_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Acknowledges that an OUT endpoint is stalled and Clears the USB STATUS register.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointOutStallAck(uint8_t endpointAddress)
{
    WaitUntilRMWDone();
    USB0.STATUS[endpointAddress].OUTCLR = USB_STALLED_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Acknowledges that an IN endpoint is stalled and Clears the USB STATUS register.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointInStallAck(uint8_t endpointAddress)
{
    WaitUntilRMWDone();
    USB0.STATUS[endpointAddress].INCLR = USB_STALLED_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Sets OUT endpoint status to NAK.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointOutNAKSet(uint8_t endpointAddress)
{
    WaitUntilRMWDone();
    USB0.STATUS[endpointAddress].OUTSET = USB_BUSNAK_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Sets IN endpoint status to NAK.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointInNAKSet(uint8_t endpointAddress)
{
    WaitUntilRMWDone();
    USB0.STATUS[endpointAddress].INSET = USB_BUSNAK_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Clears the USB NAK status from the OUT endpoint STATUS register.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointOutNAKClear(uint8_t endpointAddress)
{
    WaitUntilRMWDone();
    USB0.STATUS[endpointAddress].OUTCLR = USB_BUSNAK_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Clears the USB NAK status from the IN endpoint STATUS register.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointInNAKClear(uint8_t endpointAddress)
{
    WaitUntilRMWDone();
    USB0.STATUS[endpointAddress].INCLR = USB_BUSNAK_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks the OUT endpoint STATUS register for the NAK status.
 * @param endpointAddress - Address of the endpoint
 * @retval 0 - Endpoint is not NAKed
 * @retval 1 - Endpoint is NAKed
 */
static ALWAYS_INLINE bool USB_EndpointOutNAKIsSet(uint8_t endpointAddress)
{
    return ((endpointTable.EP[endpointAddress].OUT.STATUS & USB_BUSNAK_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks the OUT endpoint STATUS register for the NAK status.
 * @param endpointAddress - Address of the endpoint
 * @retval 0 - Endpoint is not NAKed
 * @retval 1 - Endpoint is NAKed
 */
static ALWAYS_INLINE bool USB_EndpointInNAKIsSet(uint8_t endpointAddress)
{
    return ((endpointTable.EP[endpointAddress].IN.STATUS & USB_BUSNAK_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Acknowledges the transaction complete status on a specified OUT endpoint and Clears the USB STATUS register.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointOutTransactionCompleteAck(uint8_t endpointAddress)
{
    WaitUntilRMWDone();
    USB0.STATUS[endpointAddress].OUTCLR = USB_TRNCOMPL_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Acknowledges the transaction complete status on a specified IN endpoint and Clears the USB STATUS register.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointInTransactionCompleteAck(uint8_t endpointAddress)
{
    WaitUntilRMWDone();
    USB0.STATUS[endpointAddress].INCLR = USB_TRNCOMPL_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if the USB OUT endpoint has the Transaction Complete status.
 * @param endpointAddress - Address of the endpoint
 * @retval 0 - Transaction incomplete
 * @retval 1 - Transaction complete
 */
static ALWAYS_INLINE bool USB_EndpointOutTransactionIsComplete(uint8_t endpointAddress)
{
    return ((endpointTable.EP[endpointAddress].OUT.STATUS & USB_TRNCOMPL_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if the USB IN endpoint has the Transaction Complete status.
 * @param endpointAddress - Address of the endpoint
 * @retval 0 - Transaction incomplete
 * @retval 1 - Transaction complete
 */
static ALWAYS_INLINE bool USB_EndpointInTransactionIsComplete(uint8_t endpointAddress)
{
    return ((endpointTable.EP[endpointAddress].IN.STATUS & USB_TRNCOMPL_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Acknowledges the Setup Received status on a specified OUT endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointOutSetupReceivedAck(uint8_t endpointAddress)
{
    WaitUntilRMWDone();
    USB0.STATUS[endpointAddress].OUTCLR = USB_EPSETUP_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Acknowledges the Setup Received status on a specified IN endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointInSetupCompleteAck(uint8_t endpointAddress)
{
    WaitUntilRMWDone();
    USB0.STATUS[endpointAddress].INCLR = USB_EPSETUP_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if the USB OUT endpoint has the Setup Received status.
 * @param endpointAddress - Address of the endpoint
 * @retval 0 - No setup received
 * @retval 1 - Setup received
 */
static ALWAYS_INLINE bool USB_EndpointOutSetupIsReceived(uint8_t endpointAddress)
{
    return ((endpointTable.EP[endpointAddress].OUT.STATUS & USB_EPSETUP_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if the USB IN endpoint has the Setup Received status.
 * @param endpointAddress - Address of the endpoint
 * @retval 0 - No setup received
 * @retval 1 - Setup received
 */
static ALWAYS_INLINE bool USB_EndpointInSetupIsReceived(uint8_t endpointAddress)
{
    return ((endpointTable.EP[endpointAddress].IN.STATUS & USB_EPSETUP_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Sets OUT endpoint data toggle.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointOutDataToggleSet(uint8_t endpointAddress)
{
    WaitUntilRMWDone();
    USB0.STATUS[endpointAddress].OUTSET = USB_TOGGLE_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Sets IN endpoint data toggle.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointInDataToggleSet(uint8_t endpointAddress)
{
    WaitUntilRMWDone();
    USB0.STATUS[endpointAddress].INSET = USB_TOGGLE_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Clears OUT endpoint data toggle.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointOutDataToggleClear(uint8_t endpointAddress)
{
    WaitUntilRMWDone();
    USB0.STATUS[endpointAddress].OUTCLR = USB_TOGGLE_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Clears IN endpoint data toggle.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointInDataToggleClear(uint8_t endpointAddress)
{
    WaitUntilRMWDone();
    USB0.STATUS[endpointAddress].INCLR = USB_TOGGLE_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if data toggle is set on the specified OUT endpoint.
 * @param endpointAddress - Address of the endpoint
 * @retval 0 - Data toggle is not set
 * @retval 1 - Data toggle is set
 */
static ALWAYS_INLINE bool USB_EndpointOutDataToggleIsSet(uint8_t endpointAddress)
{
    return ((endpointTable.EP[endpointAddress].OUT.STATUS & USB_TOGGLE_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if data toggle is set on the specified OUT endpoint.
 * @param endpointAddress - Address of the endpoint
 * @retval 0 - Data toggle is not set
 * @retval 1 - Data toggle is set
 */
static ALWAYS_INLINE bool USB_EndpointInDataToggleIsSet(uint8_t endpointAddress)
{
    return ((endpointTable.EP[endpointAddress].IN.STATUS & USB_TOGGLE_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Sets endpoint buffer OUT.
 * @param endpointAddress - Address of the endpoint
 * @param bufAddress - Address pointer to buffer
 * @return None.
 * @misradeviation{@advisory, 11.4} A conversion should not be performed between a pointer to object and an integer type.
 * The EP.OUT.DATAPTR register is a 16-bit register, expecting an AVR DU specific 16-bit RAM address.
 */
static ALWAYS_INLINE void USB_EndpointOutBufferSet(uint8_t endpointAddress, uint8_t *bufAddress)
{
    // cppcheck-suppress misra-c2012-11.4
    endpointTable.EP[endpointAddress].OUT.DATAPTR = (uint16_t)bufAddress;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Sets endpoint buffer IN.
 * @param endpointAddress - Address of the endpoint
 * @param bufAddress - Address pointer to buffer
 * @return None.
 * @misradeviation{@advisory, 11.4} A conversion should not be performed between a pointer to object and an integer type.
 * The EP.IN.DATAPTR register is a 16-bit register, expecting an AVR DU specific 16-bit RAM address.
 */
static ALWAYS_INLINE void USB_EndpointInBufferSet(uint8_t endpointAddress, uint8_t *bufAddress)
{
    // cppcheck-suppress misra-c2012-11.4
    endpointTable.EP[endpointAddress].IN.DATAPTR = (uint16_t)bufAddress;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Sets how many bytes of data are intended to be sent from the specified endpoint.
 * @param endpointAddress - Address of the endpoint
 * @param numberBytes - Amount of bytes to send
 * @return None.
 */
static ALWAYS_INLINE void USB_NumberBytesToSendSet(uint8_t endpointAddress, uint16_t numberBytes)
{
    (endpointTable.EP[endpointAddress].IN.CNT = (numberBytes));
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Reads out the CNT register to know how many bytes of data are intended to be sent from the specified endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return Amount of bytes to send
 */
static ALWAYS_INLINE uint16_t USB_NumberBytesToSendGet(uint8_t endpointAddress)
{
    return (endpointTable.EP[endpointAddress].IN.CNT);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Clears the CNT register to tell the peripheral no data is intended to be sent from the specified endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_NumberBytesToSendReset(uint8_t endpointAddress)
{
    USB_NumberBytesToSendSet(endpointAddress, 0x0000);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Reads out how many bytes have been sent from the specified endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return Amount of bytes that have been sent
 */
static ALWAYS_INLINE uint16_t USB_NumberBytesSentGet(uint8_t endpointAddress)
{
    return (endpointTable.EP[endpointAddress].IN.MCNT);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Clears the MCNT register that keeps track of how many bytes of data have been sent.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_NumberBytesSentReset(uint8_t endpointAddress)
{
    (endpointTable.EP[endpointAddress].IN.MCNT = (0x0000));
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Sets how many bytes of data are expected to be received on a specified endpoint.
 * @param endpointAddress - Address of the endpoint
 * @param numberBytes - The amount of bytes to receive
 * @return None.
 */
static ALWAYS_INLINE void USB_NumberBytesToReceiveSet(uint8_t endpointAddress, uint16_t numberBytes)
{
    (endpointTable.EP[(endpointAddress)].OUT.MCNT = (numberBytes));
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Gets how many bytes of data are expected to be received on a specified endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return Amount of bytes expected
 */
static ALWAYS_INLINE uint16_t USB_NumberBytesToReceiveGet(uint8_t endpointAddress)
{
    return (endpointTable.EP[endpointAddress].OUT.MCNT);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Clears the MCNT register to tell the peripheral no data is intended to be received on the specified endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_NumberBytesToReceiveReset(uint8_t endpointAddress)
{
    USB_NumberBytesToReceiveSet(endpointAddress, 0x0000);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Gets how many bytes of data have been received on a specified endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return Amount of bytes expected
 */
static ALWAYS_INLINE uint16_t USB_NumberBytesReceivedGet(uint8_t endpointAddress)
{
    return (endpointTable.EP[endpointAddress].OUT.CNT);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Resets the counter that counts amount of bytes of data received on a specific endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_NumberBytesReceivedReset(uint8_t endpointAddress)
{
    (endpointTable.EP[endpointAddress].OUT.CNT = (0x0000));
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if OUT endpoint has overflowed.
 * @param endpointAddress - Address of the endpoint
 * @retval 0 - No overflow on endpoint
 * @retval 1 - Overflow on endpoint
 */
static ALWAYS_INLINE bool USB_EndpointOutOverUnderflowIsSet(uint8_t endpointAddress)
{
    return ((endpointTable.EP[endpointAddress].OUT.STATUS & USB_UNFOVF_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if IN endpoint has underflowed.
 * @param endpointAddress - Address of the endpoint
 * @retval 0 - No underflow on endpoint
 * @retval 1 - Undeflow on endpoint
 */
static ALWAYS_INLINE bool USB_EndpointInOverUnderflowIsSet(uint8_t endpointAddress)
{
    return ((endpointTable.EP[endpointAddress].IN.STATUS & USB_UNFOVF_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Acknowledges overflow on the specified OUT endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointOutOverUnderflowAck(uint8_t endpointAddress)
{
    WaitUntilRMWDone();
    USB0.STATUS[endpointAddress].OUTCLR = USB_UNFOVF_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Acknowledges underflow on the specified IN endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointInOverUnderflowAck(uint8_t endpointAddress)
{
    WaitUntilRMWDone();
    USB0.STATUS[endpointAddress].INCLR = USB_UNFOVF_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if the specified OUT endpoint has a Cyclic Redundancy Check (CRC) failure.
 * @param endpointAddress - Address of the endpoint
 * @retval 0 - No CRC failure on endpoint
 * @retval 1 - CRC failure on endpoint
 */
static ALWAYS_INLINE bool USB_EndpointOutCRCHasFailed(uint8_t endpointAddress)
{
    return ((endpointTable.EP[endpointAddress].OUT.STATUS & USB_CRC_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if the specified IN endpoint has a CRC failure.
 * @param endpointAddress - Address of the endpoint
 * @retval 0 - No CRC failure on endpoint
 * @retval 1 - CRC failure on endpoint
 */
static ALWAYS_INLINE bool USB_EndpointInCRCHasFailed(uint8_t endpointAddress)
{
    return ((endpointTable.EP[endpointAddress].IN.STATUS & USB_CRC_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Acknowledges a CRC failure on the specified OUT endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointOutCRCAck(uint8_t endpointAddress)
{
    WaitUntilRMWDone();
    USB0.STATUS[endpointAddress].OUTCLR = USB_CRC_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Acknowledges a CRC failure on the specified IN endpoint.
 * @param endpointAddress - Address of the endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointInCRCAck(uint8_t endpointAddress)
{
    WaitUntilRMWDone();
    USB0.STATUS[endpointAddress].INCLR = USB_CRC_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables global NAK.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_GlobalNAKEnable(void)
{
    USB0.CTRLB |= USB_GNAK_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables global NAK.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_GlobalNAKDisable(void)
{
    USB0.CTRLB &= ~(USB_GNAK_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks the global NAK setting.
 * @param None.
 * @retval 0 - Global NAK is disabled
 * @retval 1 - Global NAK is enabled
 */
static ALWAYS_INLINE bool USB_GlobalNAKIsEnable(void)
{
    return ((USB0.CTRLB & USB_GNAK_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Tells the USB peripheral to attach.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_ConnectionAttach(void)
{
    USB0.CTRLB |= USB_ATTACH_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Tells the USB peripheral to detach.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_ConnectionDetach(void)
{
    USB0.CTRLB &= ~(USB_ATTACH_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if the USB connection is attached.
 * @param None.
 * @retval 0 - USB connection is not attached
 * @retval 1 - USB connection is attached
 */
static ALWAYS_INLINE bool USB_ConnectionIsAttach(void)
{
    return ((USB0.CTRLB & USB_ATTACH_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables the USB peripheral.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_Enable(void)
{
    USB0.CTRLA |= USB_ENABLE_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables the USB peripheral.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_Disable(void)
{
    USB0.CTRLA &= ~(USB_ENABLE_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if the USB peripheral is enabled.
 * @param None.
 * @retval 0 - USB peripheral not enabled
 * @retval 1 - USB peripheral enabled
 */
static ALWAYS_INLINE bool USB_IsEnable(void)
{
    return ((USB0.CTRLA & USB_ENABLE_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables USB FIFO.
 *
 * This is a device-specific function.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_FifoEnable(void)
{
    USB0.CTRLA |= USB_FIFOEN_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables USB FIFO.
 *
 * This is a device-specific function.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_FifoDisable(void)
{
    USB0.CTRLA &= ~(USB_FIFOEN_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if USB FIFO has been enabled.
 *
 * This is a device-specific function.
 * @param None.
 * @retval 0 - USB FIFO is not enabled
 * @retval 1 - USB FIFO is enabled
 */
static ALWAYS_INLINE bool USB_FifoIsEnable(void)
{
    return ((USB0.CTRLA & USB_FIFOEN_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables automatic global NAK for the USB peripheral.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_AutomaticGlobalNAKEnable(void)
{
    USB0.CTRLB |= USB_GNAUTO_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables automatic global NAK for the USB peripheral.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_AutomaticGlobalNAKDisable(void)
{
    USB0.CTRLB &= ~(USB_GNAUTO_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if automatic global NAK has been enabled.
 * @param None.
 * @retval 0 - Automatic global NAK is not enabled
 * @retval 1 - Automatic global NAK is enabled
 */
static ALWAYS_INLINE bool USB_AutomaticGlobalNAKIsEnable(void)
{
    return ((USB0.CTRLB & USB_GNAUTO_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables storing the last SOF token frame number in FRAMENUM.
 * This is a device-specific function.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_FrameNumEnable(void)
{
    USB0.CTRLA |= USB_STFRNUM_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables storing the last SOF token frame number in FRAMENUM.
 * This is a device-specific function.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_FrameNumDisable(void)
{
    USB0.CTRLA &= ~(USB_STFRNUM_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if storing of the last SOF token frame number is enabled.
 * This is a device-specific function.
 * @param None.
 * @retval 0 - Storing the last SOF token frame number in FRAMENUM is disabled
 * @retval 1 - Storing the last SOF token frame number in FRAMENUM is enabled
 */
static ALWAYS_INLINE bool USB_FrameNumIsEnable(void)
{
    return ((USB0.CTRLA & USB_STFRNUM_bm) != 0u);
}

/**
 * @ingroup usb_peripheral
 * @brief Gets the current frame number.
 * @param None.
 * @return 15-bit frame number
 */
static ALWAYS_INLINE uint16_t USB_FrameNumGet(void)
{
    return (endpointTable.FRAMENUM & USB_FRAMENUM_gm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Sets maximum number of endpoint addresses used by the USB peripheral.
 * @param maxEndpoint - Last accessible endpoint
 * @return None.
 */
static ALWAYS_INLINE void USB_MaxEndpointsSet(uint8_t maxEndpoint)
{
    USB0.CTRLA = ((USB0.CTRLA & ~USB_MAXEP_gm) | (((maxEndpoint) << USB_MAXEP_gp) & USB_MAXEP_gm));
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Clears the USB endpoint maximum, setting the maximum endpoint to EP0.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_MaxEndpointsReset(void)
{
    USB0.CTRLA &= ~(USB_MAXEP_gm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks what the maximum number of endpoint addresses is.
 * @param None.
 * @return Last accessible endpoint
 */
static ALWAYS_INLINE uint8_t USB_MaxEndpointsGet(void)
{
    return ((USB0.CTRLA & USB_MAXEP_gm) >> USB_MAXEP_gp);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Sets the address of the endpoint table.
 * This is a device-specific function.
 * @param endpointTableAddress - Address of the endpoint table
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointTableAddressSet(USB_EP_PAIR_t *endpointTableAddress)
{
    USB0.EPPTR = (uint16_t)endpointTableAddress;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Sets the address of the endpoint table to 0.
 * This is a device-specific function.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_EndpointTableAddressReset(void)
{
    USB0.EPPTR = 0x0000;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Gets the address of the endpoint table.
 * This is a device-specific function.
 * @param None.
 * @return The address of the endpoint table
 */
static ALWAYS_INLINE uint16_t USB_EndpointTableAddressGet(void)
{
    return (USB0.EPPTR);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Resets the read FIFO pointer.
 * This is a device-specific function.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_FifoReadPointerReset(void)
{
    USB0.FIFORP |= (USB_FIFORP_gm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Gets the read FIFO pointer.
 * This is a device-specific function.
 * @param None.
 * @return The FIFO read pointer
 */
static ALWAYS_INLINE int8_t USB_FifoReadPointerGet(void)
{
    return (int8_t)(USB0.FIFORP);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Resets the write FIFO pointer.
 * This is a device-specific function.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_FifoWritePointerReset(void)
{
    USB0.FIFOWP |= (USB_FIFOWP_gm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Gets the write FIFO pointer.
 * This is a device-specific function.
 * @param None.
 * @return The FIFO write pointer
 */
static ALWAYS_INLINE int8_t USB_FifoWritePointerGet(void)
{
    return (int8_t)(USB0.FIFOWP);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Sets the device address.
 * @param usbAddress - The device address to set
 * @return None.
 */
static ALWAYS_INLINE void USB_DeviceAddressSet(uint8_t usbAddress)
{
    USB0.ADDR = ((USB0.ADDR & ~USB_ADDR_gm) | (((usbAddress) << USB_ADDR_gp) & USB_ADDR_gm));
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Resets the device address.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_DeviceAddressReset(void)
{
    USB0.ADDR &= ~(USB_ADDR_gm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Gets the device address.
 * @param None.
 * @return The device address
 */
static ALWAYS_INLINE uint8_t USB_DeviceAddressGet(void)
{
    return ((USB0.ADDR & USB_ADDR_gm) >> USB_ADDR_gp);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables an upstream resume to be initated.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_UpstreamResumeEnable(void)
{
    USB0.CTRLB |= USB_URESUME_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if upstream resume is enabled, but not yet initiated.
 * @param None.
 * @retval 0 - Upstream resume initiated or not enabled
 * @retval 1 - Upstream resume enabled
 */
static ALWAYS_INLINE bool USB_UpstreamResumeIsEnable(void)
{
    return ((USB0.CTRLB & USB_URESUME_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Gets the USB bus state.
 * @param None.
 * @return The state of the USB bus
 */
static ALWAYS_INLINE uint8_t USB_BusStateGet(void)
{
    return (USB0.BUSSTATE);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if the USB bus has any specific status flags set.
 * @param bus_state_bm - The bitmap of the specific status flags to check
 * @retval 0 - No status flags set
 * @retval 1 - The bus has one or more specified status flags set
 */
static ALWAYS_INLINE bool USB_BusStateIs(uint8_t bus_state_bm)
{
    return ((USB0.BUSSTATE & (bus_state_bm)) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables the USB Start-Of-Frame interrupt.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_SOFInterruptEnable(void)
{
    USB0.INTCTRLA |= USB_SOF_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables the USB Start-Of-Frame interrupt.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_SOFInterruptDisable(void)
{
    USB0.INTCTRLA &= ~(USB_SOF_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Clears the USB Start-Of-Frame Interrupt flag.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_SOFInterruptClear(void)
{
    USB0.INTFLAGSA = USB_SOF_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if the USB Start-Of-Frame interrupt has been triggered.
 * @param None.
 * @retval 0 - Interrupt not triggered
 * @retval 1 - Interrupt triggered
 */
static ALWAYS_INLINE bool USB_SOFInterruptIs(void)
{
    return ((USB0.INTFLAGSA & USB_SOF_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables the USB Suspend interrupt.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_SuspendInterruptEnable(void)
{
    USB0.INTCTRLA |= USB_SUSPEND_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables the USB Suspend interrupt.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_SuspendInterruptDisable(void)
{
    USB0.INTCTRLA &= ~(USB_SUSPEND_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Clears the USB Suspend Interrupt flag.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_SuspendInterruptClear(void)
{
    USB0.INTFLAGSA = USB_SUSPEND_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if the USB Suspend interrupt has been triggered.
 * @param None.
 * @retval 0 - Interrupt not triggered
 * @retval 1 - Interrupt triggered
 */
static ALWAYS_INLINE bool USB_SuspendInterruptIs(void)
{
    return ((USB0.INTFLAGSA & USB_SUSPEND_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables the USB Resume interrupt.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_ResumeInterruptEnable(void)
{
    USB0.INTCTRLA |= USB_RESUME_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables the USB Resume interrupt.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_ResumeInterruptDisable(void)
{
    USB0.INTCTRLA &= ~(USB_RESUME_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Clears the USB Resume Interrupt flag.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_ResumeInterruptClear(void)
{
    USB0.INTFLAGSA = USB_RESUME_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if the USB Resume interrupt has been triggered.
 * @param None.
 * @retval 0 - Interrupt not triggered
 * @retval 1 - Interrupt triggered
 */
static ALWAYS_INLINE bool USB_ResumeInterruptIs(void)
{
    return ((USB0.INTFLAGSA & USB_RESUME_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables the USB Reset interrupt.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_ResetInterruptEnable(void)
{
    USB0.INTCTRLA |= USB_RESET_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables the USB Reset interrupt.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_ResetInterruptDisable(void)
{
    USB0.INTCTRLA &= ~(USB_RESET_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Clears the USB Reset Interrupt flag.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_ResetInterruptClear(void)
{
    USB0.INTFLAGSA = USB_RESET_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if the USB Reset interrupt has been triggered.
 * @param None.
 * @retval 0 - Interrupt not triggered
 * @retval 1 - Interrupt triggered
 */
static ALWAYS_INLINE bool USB_ResetInterruptIs(void)
{
    return ((USB0.INTFLAGSA & USB_RESET_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables the USB Stalled interrupt.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_StalledInterruptEnable(void)
{
    USB0.INTCTRLA |= USB_STALLED_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables the USB Stalled interrupt.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_StalledInterruptDisable(void)
{
    USB0.INTCTRLA &= ~(USB_STALLED_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Clears the USB Stalled Interrupt flag.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_StalledInterruptClear(void)
{
    USB0.INTFLAGSA = USB_STALLED_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if the USB Stalled interrupt has been triggered.
 * @param None.
 * @retval 0 - Interrupt not triggered
 * @retval 1 - Interrupt triggered
 */
static ALWAYS_INLINE bool USB_StalledInterruptIs(void)
{
    return ((USB0.INTFLAGSA & USB_STALLED_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables the USB Underflow interrupt.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_UnderflowInterruptEnable(void)
{
    USB0.INTCTRLA |= USB_UNF_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables the USB Underflow interrupt.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_UnderflowInterruptDisable(void)
{
    USB0.INTCTRLA &= ~(USB_UNF_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Clears the USB Underflow Interrupt flag.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_UnderflowInterruptClear(void)
{
    USB0.INTFLAGSA = USB_UNF_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if an Underflow interrupt has been triggered.
 * @param None.
 * @retval 0 - Interrupt not triggered
 * @retval 1 - Interrupt triggered
 */
static ALWAYS_INLINE bool USB_UnderflowInterruptIs(void)
{
    return ((USB0.INTFLAGSA & USB_UNF_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables the USB Overflow interrupt.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_OverflowInterruptEnable(void)
{
    USB0.INTCTRLA |= USB_OVF_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables the USB Overflow interrupt.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_OverflowInterruptDisable(void)
{
    USB0.INTCTRLA &= ~(USB_OVF_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Clears the USB Overflow Interrupt flag.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_OverflowInterruptClear(void)
{
    USB0.INTFLAGSA = USB_OVF_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if an Overflow interrupt has been triggered.
 * @param None.
 * @retval 0 - Interrupt not triggered
 * @retval 1 - Interrupt triggered
 */
static ALWAYS_INLINE bool USB_OverflowInterruptIs(void)
{
    return ((USB0.INTFLAGSA & USB_OVF_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables the USB Transaction Complete interrupt.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_TransactionCompleteInterruptEnable(void)
{
    USB0.INTCTRLB |= USB_TRNCOMPL_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables the USB Transaction Complete interrupt.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_TransactionCompleteInterruptDisable(void)
{
    USB0.INTCTRLB &= ~(USB_TRNCOMPL_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Clears the USB Transaction Complete Interrupt flag.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_TransactionCompleteInterruptAck(void)
{
    USB0.INTFLAGSB = USB_TRNCOMPL_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if a Transaction Complete interrupt has been triggered.
 * @param None.
 * @retval 0 - Interrupt not triggered
 * @retval 1 - Interrupt triggered
 */
static ALWAYS_INLINE bool USB_TransactionCompleteInterruptIs(void)
{
    return ((USB0.INTFLAGSB & USB_TRNCOMPL_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if the USB Read-Modify-Write Interrupt is enabled.
 * @param None.
 * @retval 0 - Interrupt not enabled
 * @retval 1 - Interrupt enabled
 */
static ALWAYS_INLINE bool USB_ReadModifyWriteInterruptIs(void)
{
    return ((USB0.INTFLAGSB & USB_RMWBUSY_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables the USB Global NAK Done interrupt.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_GlobalNAKDoneInterruptEnable(void)
{
    USB0.INTCTRLB |= USB_GNDONE_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables the USB Global NAK Done interrupt.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_GlobalNAKDoneInterruptDisable(void)
{
    USB0.INTCTRLB &= ~(USB_GNDONE_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Clears the USB Global NAK Done Interrupt flag.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_GlobalNAKDoneInterruptAck(void)
{
    USB0.INTFLAGSB = USB_GNDONE_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if the USB Global NAK Done interrupt has been triggered.
 * @param None.
 * @retval 0 - Interrupt not triggered
 * @retval 1 - Interrupt triggered
 */
static ALWAYS_INLINE bool USB_GlobalNAKDoneInterruptIs(void)
{
    return ((USB0.INTFLAGSB & USB_GNDONE_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Enables the USB Setup interrupt.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_SetupInterruptEnable(void)
{
    USB0.INTCTRLB |= USB_SETUP_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Disables the USB Setup interrupt.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_SetupInterruptDisable(void)
{
    USB0.INTCTRLB &= ~(USB_SETUP_bm);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Clears the USB Setup Interrupt flag.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_SetupInterruptClear(void)
{
    USB0.INTFLAGSB = USB_SETUP_bm;
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Checks if a USB Setup interrupt has been triggered.
 * @param None.
 * @retval 0 - Interrupt not triggered
 * @retval 1 - Interrupt triggered
 */
static ALWAYS_INLINE bool USB_SetupInterruptIs(void)
{
    return ((USB0.INTFLAGSB & USB_SETUP_bm) != 0u);
}

/**
 * @ingroup usb_peripheral_avr_du
 * @brief Clears all the USB Interrupt flags.
 * @param None.
 * @return None.
 */
static ALWAYS_INLINE void USB_InterruptFlagsClear(void)
{
    USB0.INTFLAGSA = 0xff;
    USB0.INTFLAGSB = 0xff;
}

#endif /* USB_PERIPHERAL_AVR_DU_H */
