/**
 * USBCOMMONELEMENTS Common Elements Header File
 * @file usb_common_elements.h
 * @defgroup usb_common USB Common Elements
 * @ingroup usb_core
 * @brief Common elements for the USB stack.
 * @version USB Common Elements Version 1.0.0
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

#ifndef USB_COMMON_ELEMENTS_H
// cppcheck-suppress misra-c2012-2.5
#define USB_COMMON_ELEMENTS_H

#ifndef TEST
#define STATIC static
#else
#define STATIC
#endif

/**
 * @ingroup usb_common
 * @enum RETURN_CODE_enum
 * @brief Describes the different function return reserved codes used by the USB stack.
 */

typedef enum RETURN_CODE_enum
{
    UNSUPPORTED = 2,   /**<Action not supported by the USB Device Stack*/
    UNINITIALIZED = 1, /**<Status unchanged since initialization*/
    SUCCESS = 0,       /**<Action successfully executed*/

    ENDPOINT_SIZE_ERROR = -1,      /**<Error related to the wMaxPacketSize in the endpoint configuration*/
    ENDPOINT_ADDRESS_ERROR = -2,   /**<Error related to the address byte of bEndpointAddress in the endpoint configuration*/
    ENDPOINT_DIRECTION_ERROR = -3, /**<Error related to the direction byte of bEndpointAddress in the endpoint configuration*/
    ENDPOINT_TYPE_ERROR = -4,      /**<Error related to the type bitmask of bmAttributes in the endpoint configuration*/
    ENDPOINT_AZLP_ERROR = -5,      /**<Error related to the Auto Zero Length Packet (AZLP) setting in the endpoint configuration*/
    ENDPOINT_ALIGN_ERROR = -6,     /**<Error related to unaligned OUT transactions when using multipacket*/

    PIPE_BUSY_ERROR = -10,     /**<Error triggered by the pipe being busy while attempting a read or write transaction*/
    PIPE_TRANSFER_ERROR = -11, /**<Error triggered by a failed pipe transaction*/

    CONTROL_SIZE_ERROR = -20,               /**<Error related to the size of the control endpoint transaction packet*/
    CONTROL_TRANSACTION_STATUS_ERROR = -21, /**<Error triggered by a failed transaction on the control endpoint*/
    CONTROL_SETUP_CALLBACK_ERROR = -22,     /**<Error triggered by a failed control setup*/
    CONTROL_SETUP_DIRECTION_ERROR = -23,    /**<Error triggerd by a control setup IN request not requesting any data*/

    DESCRIPTOR_POINTER_ERROR = -30,        /**<Error triggered by an invalid descriptor pointer*/
    DESCRIPTOR_CONFIGURATIONS_ERROR = -31, /**<Error triggered by an invalid configuration descriptor pointer*/
    DESCRIPTOR_INTERFACE_ERROR = -32,      /**<Error triggered by an invalid interface descriptor pointer*/
    DESCRIPTOR_ENDPOINT_ERROR = -33,       /**<Error triggered by an invalid endpoint descriptor pointer*/
    DESCRIPTOR_REQUEST_ERROR = -34,        /**<Error triggered by a failed attempt at retrieving a descriptor pointer*/
    DESCRIPTOR_SEARCH_ERROR = -35,         /**<Error triggered by an incorrect descriptor structure*/

    INTERFACE_SET_ERROR = -40, /**<Error triggered by a failure to set an interface*/
    INTERFACE_GET_ERROR = -41, /**<Error triggered by a failure to retrieve an interface*/

    USB_CONNECTION_ERROR = -50, /**<Error triggered by a failure during setup device request*/

    USB_CLASS_ERROR = -60, /**<Error triggered by an invalid class code*/
} RETURN_CODE_t;

/**
 * @ingroup usb_common
 * @def MAX_ENDPOINT_SIZE_DEFAULT
 * @brief The maximum endpoint packet size for the default endpoint types (control, bulk, interrupt).
 */
#define MAX_ENDPOINT_SIZE_DEFAULT (64)

/**
 * @ingroup usb_common
 * @def MAX_ENDPOINT_SIZE_ISO
 * @brief The maximum endpoint packet size for the isochronous endpoint type.
 */
#define MAX_ENDPOINT_SIZE_ISO (1023)

#endif /* USB_COMMON_ELEMENTS_H */
