/**
 * USBPROTOCOLHEADERS USB Protocol Headers Header File
 * @file usb_protocol_headers.h
 * @defgroup usb_protocol USB Protocol
 * @ingroup usb_core
 * @brief Common data structures, enumerations and macro definitons based on the USB 2.0 base protocol.
 * @version USB Protocol Version 1.0.0
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

#ifndef USB_PROTOCOL_HEADERS_H
// cppcheck-suppress misra-c2012-2.5
#define	USB_PROTOCOL_HEADERS_H

#include "usb_common_elements.h"
#include <stdbool.h>
#include <stdint.h>
#include <usb_config.h>

/*
 * ENDPOINT LAYER
 */

/**
 * @ingroup usb_protocol
 * @def USB_EP_DIR_IN
 * @brief Endpoint direction IN.
 */
#define USB_EP_DIR_IN 0x01u

/**
 * @ingroup usb_protocol
 * @def USB_EP_DIR_OUT
 * @brief Endpoint direction OUT.
 */
#define USB_EP_DIR_OUT 0x00u

/**
 * @ingroup usb_protocol
 * @def OVERFLOW_EVENT
 * @brief Overflow event for the endpoint.
 */
#define OVERFLOW_EVENT 1u

/**
 * @ingroup usb_protocol
 * @def UNDERFLOW_EVENT
 * @brief Underflow event for the endpoint.
 */
#define UNDERFLOW_EVENT 2u

/**
 * @ingroup usb_protocol
 * @enum USB_ENDPOINT_enum
 * @brief Defines labels for the different endpoint types as per the USB 2.0 base specification.
 */
typedef enum USB_ENDPOINT_enum
{
    CONTROL = 0,     /**<Control transfer type*/
    ISOCHRONOUS = 1, /**<Isochronous transfer type*/
    BULK = 2,        /**<Bulk transfer type*/
    INTERRUPT = 3,   /**<Interrupt transfer type*/
    DISABLED = 0xff, /**<Endpoint disabled*/
} USB_ENDPOINT_t;

/**
 * @ingroup usb_protocol
 * @struct USB_PIPE_struct
 * @brief Structure for a pipe which has an address and direction.
 */
typedef struct USB_PIPE_struct
{
    uint8_t address : 7;
    uint8_t direction : 1;
} USB_PIPE_t;

/**
 *READ WRITE LAYER
 */

/**
 * @ingroup usb_protocol
 * @enum USB_TRANSFER_STATUS_enum
 * @brief Defines the possible states of a configured transfer.
 */
typedef enum USB_TRANSFER_STATUS_enum
{
    USB_PIPE_TRANSFER_OK = 0,      /**<Successful transfer on the pipe*/
    USB_PIPE_TRANSFER_BUSY = 1,    /**<The pipe is busy*/
    USB_PIPE_TRANSFER_ABORTED = 2, /**<Transfer aborted on the pipe*/
    USB_PIPE_TRANSFER_ERROR = 3,   /**<Failure during transfer on the pipe*/
} USB_TRANSFER_STATUS_t;

/**
 * @ingroup usb_protocol
 * @enum USB_CONTROL_STATUS_enum
 * @brief Defines the possible states of a configured control transfer.
 */
typedef enum USB_CONTROL_STATUS_enum
{
    USB_CONTROL_SETUP = 0,     /**< Wait a SETUP packet*/
    USB_CONTROL_DATA_OUT = 1,  /**< Wait an OUT data packet*/
    USB_CONTROL_DATA_IN = 2,   /**< Wait an IN data packet*/
    USB_CONTROL_ZLP = 3,       /**< Wait an IN or OUT ZLP packet*/
    USB_CONTROL_STALL_REQ = 4, /**< STALL enabled on IN and OUT packets*/
} USB_CONTROL_STATUS_t;

/**
 * @ingroup usb_protocol
 * @def USB_V2_0
 * @brief USB Specification version 2.00.
 */
#define USB_V2_0 0x0200

/**
 * @ingroup usb_protocol
 * @def USB_V2_1
 * @brief USB Specification version 2.01.
 */
#define USB_V2_1 0x0201

/**
 * @ingroup usb_protocol
 * @def NO_SUBCLASS
 * @brief No subclass code.
 */
#define NO_SUBCLASS 0x00

/**
 * @ingroup usb_protocol
 * @def NO_PROTOCOL
 * @brief No protocol code.
 */
#define NO_PROTOCOL 0x00

/**
 * @ingroup usb_protocol
 * @def CLASS_IAD
 * @brief IAD class code.
 */
#define CLASS_IAD 0xEF

/**
 * @ingroup usb_protocol
 * @def SUB_CLASS_IAD
 * @brief IAD subclass code.
 */
#define SUB_CLASS_IAD 0x02

/**
 * @ingroup usb_protocol
 * @def PROTOCOL_IAD
 * @brief IAD protocol code.
 */
#define PROTOCOL_IAD 0x01

/**
 * @ingroup usb_protocol
 * @def USB_ENDPOINT_FEATURE_HALT
 * @brief USB endpoint feature halt.
 */
#define USB_ENDPOINT_FEATURE_HALT 0x00u

/**
 * @ingroup usb_protocol
 * @def DESCRIPTOR_STRING_LENGTH
 * @brief Calculates descriptor length of a UTF-16 string descriptor without the null character.
 */
#define DESCRIPTOR_STRING_LENGTH(wstring) (sizeof(wstring) / sizeof(wchar_t) - 1)

/**
 * @ingroup usb_protocol
 * @enum USB_DEVICE_CLASS_t
 * @brief Type define for standard device class
 */
typedef enum USB_DEVICE_CLASS_enum
{
    USB_NO_DEVICE_CLASS = 0x00,                    /**<Use class code info from Interface Descriptors*/
    USB_AUDIO_DEVICE_CLASS = 0x01,                 /**<Audio device*/
    USB_CDC_DEVICE_CLASS = 0x02,                   /**<Communications and CDC Control*/
    USB_HID_DEVICE_CLASS = 0x03,                   /**<HID (Human Interface Device)*/
    USB_PHYSICAL_DEVICE_CLASS = 0x05,              /**<Physical device*/
    USB_IMAGE_DEVICE_CLASS = 0x06,                 /**<Still imaging device*/
    USB_PRINTER_DEVICE_CLASS = 0x07,               /**<Printer device*/
    USB_MASS_STORAGE_DEVICE_CLASS = 0x08,          /**<Mass storage device*/
    USB_HUB_DEVICE_CLASS = 0x09,                   /**<Hub*/
    USB_CDC_DATA_DEVICE_CLASS = 0x0A,              /**<CDC data device*/
    USB_SMART_CARD_DEVICE_CLASS = 0x0B,            /**<Smart Card device*/
    USB_CONTENT_SECURITY_DEVICE_CLASS = 0x0D,      /**<Content security device*/
    USB_VIDEO_DEVICE_CLASS = 0x0E,                 /**<Video device*/
    USB_PERSONAL_HEALTHCARE_DEVICE_CLASS = 0x0F,   /**<Personal healthcare device*/
    USB_AUDIO_VIDEO_DEVICE_CLASS = 0x10,           /**<Audio/Video devices*/
    USB_BILLBOARD_DEVICE_CLASS = 0x11,             /**<Billboard device*/
    USB_TYPE_C_BRIDGE_DEVICE_CLASS = 0x12,         /**<USB Type-C bridge device*/
    USB_BULK_DISPLAY_PROTOCOL_DEVICE_CLASS = 0x13, /**<USB Bulk display protocol device*/
    USB_MCTP_DEVICE_CLASS = 0x14,                  /**<MCTP over USB protocol endpoint device*/
    USB_I3C_DEVICE_CLASS = 0x3C,                   /**<I3C device*/
    USB_DIAGNOSTIC_DEVICE_CLASS = 0xDC,            /**<Diagnostic device*/
    USB_WIRELESS_DEVICE_CLASS = 0xE0,              /**<Wireless controller*/
    USB_MISC_DEVICE_CLASS = 0xEF,                  /**<Miscellaneous*/
    USB_APPLICATION_DEVICE_CLASS = 0xFE,           /**<Application specific*/
    USB_VENDOR_DEVICE_CLASS = 0xFF,                /**<Vendor specific*/

} USB_DEVICE_CLASS_t;

/**
 * @ingroup usb_protocol
 * @enum USB_REQUEST_DIR_enum
 * @brief Standard USB enumeration used by setup requests.
 */
typedef enum USB_REQUEST_DIR_enum
{
    USB_REQUEST_DIR_OUT = 0, /**<Setup request has direction OUT*/
    USB_REQUEST_DIR_IN = 1,  /**<Setup request has direction IN*/
} USB_REQUEST_DIR_t;

/**
 * @ingroup usb_protocol
 * @enum USB_REQUEST_TYPE_enum
 * @brief USB request types (bmRequestType).
 */
typedef enum USB_REQUEST_TYPE_enum
{
    USB_REQUEST_TYPE_STANDARD = 0, /**<Standard USB request defined in the USB specification*/
    USB_REQUEST_TYPE_CLASS = 1,    /**<Class-specific request defined in the USB Class Specification*/
    USB_REQUEST_TYPE_VENDOR = 2,   /**<Vendor-specific request not defined in the USB Specification*/
} USB_REQUEST_TYPE_t;

/**
 * @ingroup usb_protocol
 * @enum USB_REQUEST_RECIPIENT_enum
 * @brief USB recipient codes (bmRequestType).
 */
typedef enum USB_REQUEST_RECIPIENT_enum
{
    USB_REQUEST_RECIPIENT_DEVICE = 0,    /**<Request is directed at the entire USB device*/
    USB_REQUEST_RECIPIENT_INTERFACE = 1, /**<Request is directed at an interface within the USB device*/
    USB_REQUEST_RECIPIENT_ENDPOINT = 2,  /**<Request is directed at an endpoint within an interface*/
    USB_REQUEST_RECIPIENT_OTHER = 3,     /**<Request is directed at another specific recipient*/
} USB_REQUEST_RECIPIENT_t;

/**
 * @ingroup usb_protocol
 * @enum USB_REQUEST_ID_enum
 * @brief Standard USB requests (bRequest).
 */
typedef enum USB_REQUEST_ID_enum
{
    USB_REQUEST_GET_STATUS = 0,        /**<Retrieve status information, such as device power status or endpoint stall conditions*/
    USB_REQUEST_CLEAR_FEATURE = 1,     /**<Clear or reset specific device or component features, like clearing an endpoint halt condition*/
    USB_REQUEST_SET_FEATURE = 3,       /**<Set or enable specific device or component features, often used to configure device behavior*/
    USB_REQUEST_SET_ADDRESS = 5,       /**<Assign a unique device address during enumeration*/
    USB_REQUEST_GET_DESCRIPTOR = 6,    /**<Request descriptor information, specifying the type of descriptor being requested*/
    USB_REQUEST_SET_DESCRIPTOR = 7,    /**<Update certain descriptors*/
    USB_REQUEST_GET_CONFIGURATION = 8, /**<Retrieve the currently selected device configuration*/
    USB_REQUEST_SET_CONFIGURATION = 9, /**<Select a specific device configuration*/
    USB_REQUEST_GET_INTERFACE = 10,    /**<Retrieve the currently selected alternate setting of an interface*/
    USB_REQUEST_SET_INTERFACE = 11,    /**<Select a specific alternate setting for an interface*/
    USB_REQUEST_SYNCH_FRAME = 12,      /**<Retrieve synchronization information for isochronous transfers*/
} USB_REQUEST_ID_t;

/**
 * @ingroup usb_protocol
 * @enum USB_DESCRIPTOR_TYPE_enum
 * @brief Standard USB descriptor types.
 */
typedef enum USB_DESCRIPTOR_TYPE_enum
{
    USB_DESCRIPTOR_TYPE_DEVICE = 1,                    /**<Provides essential information about the USB device*/
    USB_DESCRIPTOR_TYPE_CONFIGURATION = 2,             /**<Describes a specific configuration of the device*/
    USB_DESCRIPTOR_TYPE_STRING = 3,                    /**<Contains human-readable string information*/
    USB_DESCRIPTOR_TYPE_INTERFACE = 4,                 /**<Specifies the characteristics of a single interface within a configuration*/
    USB_DESCRIPTOR_TYPE_ENDPOINT = 5,                  /**<Defines the characteristics of a specific endpoint within an interface*/
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER = 6,          /**<For high-speed USB devices, informs the host if the device has different device information for when operating in full-speed*/
    USB_DESCRIPTOR_TYPE_OTHER_SPEED_CONFIGURATION = 7, /**<Provides details about the configuration of a device for a specific speed when operating at high-speed*/
    USB_DESCRIPTOR_TYPE_INTERFACE_POWER = 8,           /**<Specifies the amount of power that an interface of a USB device consumes when it's active*/
    USB_DESCRIPTOR_TYPE_IAD = 11,                      /**<Interface Association Descriptor which associates a group of interfaces that form a single function, helping to manage composite devices*/
    USB_DESCRIPTOR_TYPE_BOS = 15,                      /**<Binary Object Store Descriptor which provides information about the capabilities of the device*/
    USB_DESCRIPTOR_TYPE_DEVICE_CAPABILITY = 16,        /**<Describes specific capabilities and features supported by the device, such as USB Power Delivery or USB 2.0 features*/
    USB_DESCRIPTOR_TYPE_CLASS = 0x20,                  /**<Class descriptor types are from 0x20 to 0x3f*/
    USB_DESCRIPTOR_TYPE_VENDOR = 0x40,                 /**<Vendor descriptor types are from 0x40 to 0x5f*/
} USB_DESCRIPTOR_TYPE_t;

/**
 * @ingroup usb_protocol
 * @enum USB_SETUP_REQUEST_struct
 * @brief Ch. 9.3 USB Device SETUP request.
 * The data payload of SETUP packets always follows this structure.
 */
typedef struct USB_SETUP_REQUEST_struct
{

    struct
    {
        uint8_t recipient                  : 5; /**< Recipient type bit field*/
        uint8_t type                       : 2; /**< Request type bit field*/
        uint8_t dataPhaseTransferDirection : 1; /**< Data stage direction bit field*/
    } bmRequestType;
    uint8_t bRequest; /**< Request identifier*/
    uint16_t wValue;  /**< Request specific value*/
    uint16_t wIndex;  /**< Request specific index*/
    uint16_t wLength; /**< Number of bytes to transfer in data stage*/
} USB_SETUP_REQUEST_t;

/**
 * @ingroup usb_protocol
 * @enum USB_DESCRIPTOR_HEADER_struct
 * @brief Ch.9.6 Standard USB device descriptor structure.
 */
typedef struct USB_DESCRIPTOR_HEADER_struct
{
    uint8_t bLength;         /**< Descriptor size in bytes - sizeof(USB_DEVICE_DESCRIPTOR_t)*/
    uint8_t bDescriptorType; /**< Descriptor type constant - USB_DESCRIPTOR_TYPE_DEVICE*/
} USB_DESCRIPTOR_HEADER_t;

/**
 * @ingroup usb_protocol
 * @enum USB_DEVICE_DESCRIPTOR_struct
 * @brief Ch.9.6.1 Standard USB device descriptor structure.
 */
typedef struct USB_DEVICE_DESCRIPTOR_struct
{
    USB_DESCRIPTOR_HEADER_t header; /**< Descriptor type and size*/
    uint16_t bcdUSB;                /**< USB spec release number in BCD format*/
    uint8_t bDeviceClass;           /**< Device Class Code*/
    uint8_t bDeviceSubClass;        /**< Device SubClass Code*/
    uint8_t bDeviceProtocol;        /**< Device Protocol Code*/
    uint8_t bMaxPacketSize0;        /**< Maximum packet size for endpoint 0*/
    uint16_t idVendor;              /**< Vendor ID*/
    uint16_t idProduct;             /**< Product ID*/
    uint16_t bcdDevice;             /**< Device release number in BCD format*/
    uint8_t iManufacturer;          /**< Manufacturer string descriptor index*/
    uint8_t iProduct;               /**< Product string descriptor index*/
    uint8_t iSerialNumber;          /**< Device serial number string descriptor index*/
    uint8_t bNumConfigurations;     /**< Number of possible configurations*/
} USB_DEVICE_DESCRIPTOR_t;

/**
 * @ingroup usb_protocol
 * @enum USB_DEV_QUAL_DESC_struct
 * @brief Ch. 9.6.2 Standard USB device qualifier descriptor structure.
 * This descriptor contains information about the device when running at
 * the "other" speed (i.e. if the device is currently operating at high
 * speed, this descriptor can be used to determine what would change if
 * the device was operating at full speed.)
 */
typedef struct USB_DEV_QUAL_DESC_struct
{
    USB_DESCRIPTOR_HEADER_t header; /**< Descriptor type and size*/
    uint16_t bcdUSB;
    uint8_t bDeviceClass;
    uint8_t bDeviceSubClass;
    uint8_t bDeviceProtocol;
    uint8_t bMaxPacketSize0;
    uint8_t bNumConfigurations;
    uint8_t bReserved;
} USB_DEV_QUAL_DESC_t;

/**
 * @ingroup usb_protocol
 * @enum USB_DEV_BOS_DESC_struct
 * @brief USB Device BOS descriptor structure.
 * The Binary device Object Store (BOS) descriptor defines a root
 * descriptor that is similar to the configuration descriptor, and is
 * the base descriptor for accessing a family of related descriptors.
 * A host can read a BOS descriptor and learn from the wTotalLength field
 * the entire size of the device-level descriptor set, or it can read in
 * the entire BOS descriptor set of device capabilities.
 * The host accesses this descriptor using the GetDescriptor() request.
 * The descriptor type in the GetDescriptor() request is set to BOS.
 */
typedef struct USB_DEV_BOS_DESC_struct
{
    USB_DESCRIPTOR_HEADER_t header; /**< Descriptor type and size*/
    uint16_t wTotalLength;
    uint8_t bNumDeviceCaps;
} USB_DEV_BOS_DESC_t;

/**
 * @ingroup usb_protocol
 * @enum USB_DEV_CAPA_EXT_DESC_struct
 * @brief USB Device Capabilities - USB 2.0 Extension Descriptor structure.
 * Defines the set of USB 1.1-specific device level capabilities.
 */
typedef struct USB_DEV_CAPA_EXT_DESC_struct
{
    USB_DESCRIPTOR_HEADER_t header; /**< Descriptor type and size*/
    uint8_t bDevCapabilityType;
    uint32_t bmAttributes;
} USB_DEV_CAPA_EXT_DESC_t;

/**
 * @ingroup usb_protocol
 * @enum USB_DEV_LPM_DESC_struct
 * @brief USB Device LPM Descriptor structure.
 * The BOS descriptor and capabilities descriptors for LPM.
 */
typedef struct USB_DEV_LPM_DESC_struct
{
    USB_DEV_BOS_DESC_t bos;
    USB_DEV_CAPA_EXT_DESC_t capa_ext;
} USB_DEV_LPM_DESC_t;

/**
 * @ingroup usb_protocol
 * @enum USB_ASSOCIATION_DESC_struct
 * @brief Standard USB Interface Association Descriptor structure.
 */
typedef struct USB_ASSOCIATION_DESC_struct
{
    USB_DESCRIPTOR_HEADER_t header; /**< Descriptor type and size*/
    uint8_t bFirstInterface;        /**< Number of interface*/
    uint8_t bInterfaceCount;        /**< Value to select alternate setting*/
    uint8_t bFunctionClass;         /**< Class code assigned by the USB*/
    uint8_t bFunctionSubClass;      /**< Sub-class code assigned by the USB*/
    uint8_t bFunctionProtocol;      /**< Protocol code assigned by the USB*/
    uint8_t iFunction;              /**< Index of string descriptor*/
} USB_ASSOCIATION_DESC_t;

/**
 * @ingroup usb_protocol
 * @enum USB_CONFIGURATION_DESCRIPTOR_struct
 * @brief Ch. 9.6.3 Standard USB configuration descriptor structure.
 */
typedef struct USB_CONFIGURATION_DESCRIPTOR_struct
{
    USB_DESCRIPTOR_HEADER_t header; /**< Descriptor type and size*/
    uint16_t wTotalLength;
    uint8_t bNumInterfaces;
    uint8_t bConfigurationValue;
    uint8_t iConfiguration;
    uint8_t bmAttributes;
    uint8_t bMaxPower;
} USB_CONFIGURATION_DESCRIPTOR_t;

/**
 * @ingroup usb_protocol
 * @def USB_CONFIG_ATTR_MUST_SET
 * @brief USB Attribute bitfield for the configuration descriptor.
 */
#define USB_CONFIG_ATTR_MUST_SET (1u << 7u) /**< Must always be set*/

/**
 * @ingroup usb_protocol
 * @def USB_CONFIG_ATTR_BUS_POWERED
 * @brief USB Attribute Bus Powered bitfield for the configuration descriptor.
 */
#define USB_CONFIG_ATTR_BUS_POWERED (0u << 6u) /**< Bus-Powered*/

/**
 * @ingroup usb_protocol
 * @def USB_CONFIG_ATTR_SELF_POWERED
 * @brief USB Attribute Self Powered bitfield for the configuration descriptor.
 */
#define USB_CONFIG_ATTR_SELF_POWERED (1u << 6u) /**< Self-Powered*/

/**
 * @ingroup usb_protocol
 * @def USB_CONFIG_ATTR_REMOTE_WAKEUP
 * @brief USB Attribute Remote Wakeup bitfield for the configuration descriptor.
 */
#define USB_CONFIG_ATTR_REMOTE_WAKEUP (1u << 5u) /**< Remote wakeup supported*/

/**
 * @ingroup usb_protocol
 * @def USB_CONFIG_MAX_POWER
 * @brief USB Max Power bitfield for the configuration descriptor.
 */
#define USB_CONFIG_MAX_POWER(ma) (((ma) + 1u) / 2u) /**< Maximum power in mA*/

/**
 * @ingroup usb_protocol
 * @enum USB_REQUEST_DEVICE_SELF_POWERED
 * @brief USB Self Powered bitfield for the configuration descriptor.
 */
#define USB_REQUEST_DEVICE_SELF_POWERED (1u << 0u) /**< Self-Powered*/

/**
 * @ingroup usb_protocol
 * @enum USB_REQUEST_DEVICE_REMOTE_WAKEUP
 * @brief USB Remote Wake-up bitfield for the configuration descriptor.
 */
#define USB_REQUEST_DEVICE_REMOTE_WAKEUP (1u << 1u) /**< Remote Wake-up supported*/

/**
 * @ingroup usb_protocol
 * @enum USB_REQUEST_DEVICE_DISABLE_CONFIGURATION
 * @brief Disable any enabled configuration.
 */
#define USB_REQUEST_DEVICE_DISABLE_CONFIGURATION (0u)

/**
 * @ingroup usb_protocol
 * @struct USB_IAD_DESC_struct
 * @brief Standard USB association descriptor structure.
 */
typedef struct USB_IAD_DESC_struct
{
    USB_DESCRIPTOR_HEADER_t header; /**< Descriptor type and size*/
    uint8_t bFirstInterface;        /**< Number of interface*/
    uint8_t bInterfaceCount;        /**< Value to select alternate setting*/
    uint8_t bFunctionClass;         /**< Class code assigned by the USB*/
    uint8_t bFunctionSubClass;      /**< Sub-class code assigned by the USB*/
    uint8_t bFunctionProtocol;      /**< Protocol code assigned by the USB*/
    uint8_t iFunction;              /**< Index of string descriptor*/
} USB_IAD_DESC_t;

/**
 * @ingroup usb_protocol
 * @struct USB_INTERFACE_DESCRIPTOR_struct
 * @brief Ch. 9.6.5 Standard USB interface descriptor structure.
 */
typedef struct USB_INTERFACE_DESCRIPTOR_struct
{
    USB_DESCRIPTOR_HEADER_t header; /**< Descriptor type and size*/
    uint8_t bInterfaceNumber;
    uint8_t bAlternateSetting;
    uint8_t bNumEndpoints;
    uint8_t bInterfaceClass;
    uint8_t bInterfaceSubClass;
    uint8_t bInterfaceProtocol;
    uint8_t iInterface;
} USB_INTERFACE_DESCRIPTOR_t;

/**
 * @ingroup usb_protocol
 * @enum USB_ENDPOINT_DESCRIPTOR_struct
 * @brief Ch. 9.6.6 Standard USB endpoint descriptor structure.
 */
typedef struct USB_ENDPOINT_DESCRIPTOR_struct
{
    USB_DESCRIPTOR_HEADER_t header; /**< Descriptor type and size*/
    USB_PIPE_t bEndpointAddress;
    struct
    {
        uint8_t type : 2;
        uint8_t synchronisation : 2;
        uint8_t usage : 2;
        uint8_t reserved : 2;
    } bmAttributes;
    uint16_t wMaxPacketSize;
    uint8_t bInterval;
} USB_ENDPOINT_DESCRIPTOR_t;

/**
 * @ingroup usb_protocol
 * @struct USB_STRING_LANG_ID_DESCRIPTOR_struct
 * @brief Structure for the USB string Language ID descriptor.
 */
typedef struct USB_STRING_LANG_ID_DESCRIPTOR_struct
{
    USB_DESCRIPTOR_HEADER_t header; /**< Descriptor type and size*/
    uint16_t id_array[LANG_ID_NUM];
} USB_STRING_LANG_ID_DESCRIPTOR_t;

/**
 * @ingroup usb_protocol
 * @struct USB_STRING_DESCRIPTOR_struct
 * @brief Structure with pointers to the standard USB descriptors.
 */
typedef struct USB_DESCRIPTOR_POINTERS_struct
{
    USB_DEVICE_DESCRIPTOR_t *devicePtr;
    USB_CONFIGURATION_DESCRIPTOR_t *configurationsPtr;
    USB_DEV_BOS_DESC_t *deviceBOSptr;
    USB_STRING_LANG_ID_DESCRIPTOR_t *langIDptr;
    USB_DESCRIPTOR_HEADER_t *stringPtrs[LANG_ID_NUM];
} USB_DESCRIPTOR_POINTERS_t;

/**
 * @ingroup usb_protocol
 * @brief Function callback type USB_TRANSFER_END_CALLBACK_t.
 * Callback type used for transfer complete notifications.
 * @param pipe - Address and direction of the pipe used for the transfer
 * @param status - Status of the completed transfer, USB_PIPE_TRANSFER_OK when successful
 * @param bytesTransferred - Number of bytes transferred
 * @return None.
 */
typedef void (*USB_TRANSFER_END_CALLBACK_t)(USB_PIPE_t pipe, USB_TRANSFER_STATUS_t status, uint16_t bytesTransferred);

/**
 * @ingroup usb_protocol
 * @brief Function callback type USB_SETUP_PROCESS_CALLBACK_t.
 * Callback type used for setup request processing, with a return code to let the stack know to proceed.
 * @param *setupRequestPtr - Pointer to the current setup request data structure
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
typedef RETURN_CODE_t (*USB_SETUP_PROCESS_CALLBACK_t)(USB_SETUP_REQUEST_t *setupRequestPtr);

/**
 * @ingroup usb_protocol
 * @brief Function callback type USB_SETUP_STRING_CALLBACK_t.
 * Callback type used for setup request processing a string descriptor, with a return code to let the stack know to proceed.
 * @param stringIndex - Specifies which string of device information is requested
 * @param langID - Which language the string requested must be in
 * @param **descriptorAddressPtr - Pointer to write string descriptor address to
 * @param *descriptorLength - pointer to the size of the descriptor
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
typedef RETURN_CODE_t (*USB_SETUP_STRING_CALLBACK_t)(uint8_t stringIndex, uint16_t langID, uint8_t **descriptorAddressPtr, uint16_t *descriptorLength);

/**
 * @ingroup usb_protocol
 * @brief Function callback type USB_SETUP_EVENT_CALLBACK_t.
 * Callback type used for setup request notifications.
 * @param *setupRequestPtr -  Pointer to the current setup request data structure
 * @return None.
 */
typedef void (*USB_SETUP_EVENT_CALLBACK_t)(USB_SETUP_REQUEST_t *setupRequestPtr);

/**
 * @ingroup usb_protocol
 * @brief Function callback type USB_SETUP_OVERUNDERRUN_CALLBACK_t.
 * Callback type used for USB Overrun and Underrun event processing on the control endpoints, with a return code to let the stack know to proceed.
 * @param None.
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
typedef RETURN_CODE_t (*USB_SETUP_OVERUNDERRUN_CALLBACK_t)(void);

/**
 * @ingroup usb_protocol
 * @brief Function callback type USB_SETUP_ENDOFREQUEST_CALLBACK_t.
 * Callback type used for setup request complete notifications.
 * @param None.
 * @return None.
 */
typedef void (*USB_SETUP_ENDOFREQUEST_CALLBACK_t)(void);

/**
 * @ingroup usb_protocol
 * @brief Function callback type USB_EVENT_CALLBACK_t.
 * Callback type used for USB event notifications.
 * @param None.
 * @return None.
 */
typedef void (*USB_EVENT_CALLBACK_t)(void);

#endif /* USB_PROTOCOL_HEADERS_H */