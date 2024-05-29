/**
 * USBPROTOCOLCDC CDC Protocol Header File
 * @file usb_protocol_cdc.h
 * @ingroup usb_cdc
 * @brief USB Communications Device Class (CDC) protocol definitions
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

#ifndef USB_PROTOCOL_CDC_H
#define USB_PROTOCOL_CDC_H

#include <stdint.h>
#include <usb_config.h>

/**
 * @ingroup usb_cdc
 * @enum USB_CDC_INTERFACE_CLASS_t
 * @brief Type define for standard CDC interface class.
 */
typedef enum USB_CDC_INTERFACE_CLASS_enum
{
    USB_CDC_NO_INTERFACE_CLASS = 0x00,            /**<Interface level: No class*/
    USB_CDC_COMMUNICATION_INTERFACE_CLASS = 0x02, /**<Interface level: Communication class*/
    USB_CDC_DATA_INTERFACE_CLASS = 0x0A,          /**<Interface level: Data class*/

} USB_CDC_INTERFACE_CLASS_t;

/**
 * @ingroup usb_cdc
 * @enum USB_CDC_COMM_SUBCLASS_t
 * @brief Type define for standard CDC communication class subclasses.
 */
typedef enum USB_CDC_COMM_SUBCLASS_enum
{
    USB_CDC_COMM_SUBCLASS_DIRECT_LINE_CONTROL_MODE = 0x01,          /**<Communication interface subclass: Direct line control model*/
    USB_CDC_COMM_SUBCLASS_ABSTRACT_CONTROL_MODEL = 0x02,            /**<Communication interface subclass: Abstract control model*/
    USB_CDC_COMM_SUBCLASS_TELEPHONE_CONTROL_MODEL = 0x03,           /**<Communication interface subclass: Telephone control model*/
    USB_CDC_COMM_SUBCLASS_MULTI_CHANNEL_CONTROL_MODEL = 0x04,       /**<Communication interface subclass: Multi channel control model*/
    USB_CDC_COMM_SUBCLASS_CAPI_CONTROL_MODEL = 0x05,                /**<Communication interface subclass: Common application programming interface control model*/
    USB_CDC_COMM_SUBCLASS_ETHERNET_NETWORKING_CONTROL_MODEL = 0x06, /**<Communication interface subclass: Ethernet networking control model*/
    USB_CDC_COMM_SUBCLASS_ATM_NETWORKING_CONTROL_MODEL = 0x07,      /**<Communication interface subclass: ATM networking control model*/
    USB_CDC_COMM_SUBCLASS_WIRELESS_HANDSET_CONTROL_MODEL = 0x08,    /**<Communication interface subclass: Wireless handset control model*/
    USB_CDC_COMM_SUBCLASS_DEVICE_MANAGEMENT = 0x09,                 /**<Communication interface subclass: Device management*/
    USB_CDC_COMM_SUBCLASS_MOBILE_DIRECT_LINE_MODEL = 0x0A,          /**<Communication interface subclass: Mobile direct line model*/
    USB_CDC_COMM_SUBCLASS_OBEX = 0x0B,                              /**<Communication interface subclass: Object exchange*/
    USB_CDC_COMM_SUBCLASS_ETHERNET_EMULATION_MODEL = 0x0C,          /**<Communication interface subclass: Ethernet emulation model*/
    USB_CDC_COMM_SUBCLASS_NETWORK_CONTROL_MODEL = 0x0D,             /**<Communication interface subclass: Network control model*/

} USB_CDC_COMM_SUBCLASS_t;

/**
 * @ingroup usb_cdc
 * @enum USB_CDC_COMM_PROTOCOL_t
 * @brief Type define for standard CDC communication class protocols.
 */
typedef enum USB_CDC_COMM_PROTOCOL_enum
{
    USB_CDC_COMM_NO_PROTOCOL = 0x00,                               /**<Communication interface protocol: No protocol*/
    USB_CDC_COMM_PROTOCOL_USB_SPECIFICATION_COMMUNICATIONS = 0x00, /**<Communication interface protocol: USB specification communication*/
    USB_CDC_COMM_PROTOCOL_AT_COMMAND_ITU_T_V_250 = 0x01,           /**<Communication interface protocol: AT Commands V.250 etc*/
    USB_CDC_COMM_PROTOCOL_AT_COMMAND_PCCA_101 = 0x02,              /**<Communication interface protocol: AT Commands defined by PCCA-101*/
    USB_CDC_COMM_PROTOCOL_AT_COMMAND_PCCA_101_ANNEX_O = 0x03,      /**<Communication interface protocol: AT Commands defined by PCCA-101 & Annex O*/
    USB_CDC_COMM_PROTOCOL_AT_COMMAND_GSM_7_07 = 0x04,              /**<Communication interface protocol: AT Commands defined by GSM 07.07*/
    USB_CDC_COMM_PROTOCOL_AT_COMMAND_3GPP_27_07 = 0x05,            /**<Communication interface protocol: AT Commands defined by 3GPP 27.007*/
    USB_CDC_COMM_PROTOCOL_AT_COMMAND_C_S0017_0 = 0x06,             /**<Communication interface protocol: AT Commands defined by TIA for CDMA*/
    USB_CDC_COMM_PROTOCOL_USB_EEM = 0x07,                          /**<Communication interface protocol: Ethernet Emulation Model*/
    USB_CDC_COMM_PROTOCOL_USB_EXTERNAL_PROTOCOL = 0xFE,            /**<Communication interface protocol: External Protocol, commands defined by Command Set functional descriptor*/
    USB_CDC_COMM_PROTOCOL_USB_SPECIFICATION_VENDOR = 0xFF,         /**<Communication interface protocol: Vendor-specific*/

} USB_CDC_COMM_PROTOCOL_t;

/**
 * @ingroup usb_cdc
 * @enum USB_CDC_DATA_SUBCLASS_t
 * @brief Type define for standard CDC data class subclasses.
 */
typedef enum USB_CDC_DATA_SUBCLASS_enum
{
    USB_CDC_DATA_NO_SUBCLASS = 0x00, /**<Data interface subclass: No subclass*/
} USB_CDC_DATA_SUBCLASS_t;

/**
 * @ingroup usb_cdc
 * @enum USB_CDC_DATA_PROTOCOL_t
 * @brief Type define for standard CDC data class protocols.
 */
typedef enum USB_CDC_DATA_PROTOCOL_enum
{
    USB_CDC_DATA_NO_PROTOCOL = 0x00,                            /**<Data interface protocol: No protocol*/
    USB_CDC_DATA_PROTOCOL_USB_SPECIFICATION_DATA = 0x00,        /**<Data interface protocol: USB specification communication*/
    USB_CDC_DATA_PROTOCOL_USBNCM1_0 = 0x01,                     /**<Data interface protocol: Network Transfer Block*/
    USB_CDC_DATA_PROTOCOL_I_430 = 0x30,                         /**<Data interface protocol: Physical interface protocol for ISDN BRI*/
    USB_CDC_DATA_PROTOCOL_ISO_IEC_3309_1993 = 0x31,             /**<Data interface protocol: High-level data link control*/
    USB_CDC_DATA_PROTOCOL_TRANSPARENT = 0x32,                   /**<Data interface protocol: Transparent*/
    USB_CDC_DATA_PROTOCOL_Q_921M = 0x50,                        /**<Data interface protocol: Management protocol for Q.921 data link protocol*/
    USB_CDC_DATA_PROTOCOL_Q_921 = 0x51,                         /**<Data interface protocol: Data link protocol for Q.931*/
    USB_CDC_DATA_PROTOCOL_Q_921TM = 0x52,                       /**<Data interface protocol: TEI-multiplexor for Q.921 data link protocol*/
    USB_CDC_DATA_PROTOCOL_V_42BIS = 0x90,                       /**<Data interface protocol: Data compression procedures*/
    USB_CDC_DATA_PROTOCOL_Q_931_EURO_ISDN = 0x91,               /**<Data interface protocol: Euro-ISDN protocol control*/
    USB_CDC_DATA_PROTOCOL_V_120 = 0x92,                         /**<Data interface protocol: V.24 rate adaptation to ISDN*/
    USB_CDC_DATA_PROTOCOL_CAPI2_0 = 0x93,                       /**<Data interface protocol: Common application programming interface commands*/
    USB_CDC_DATA_PROTOCOL_HOST_BASED_DRIVER = 0xFD,             /**<Data interface protocol: Host based driver*/
    USB_CDC_DATA_PROTOCOL_CDC_SPECIFICATION_DATA = 0xFE,        /**<Data interface protocol: Protocol Unit functional descriptors on Communications Class Interface*/
    USB_CDC_DATA_PROTOCOL_USB_SPECIFICATION_DATA_VENDOR = 0xFF, /**<Data interface protocol: Vendor-specific*/

} USB_CDC_DATA_PROTOCOL_t;

/**
 * @ingroup usb_cdc
 * @enum USB_CDC_REQUEST_ID_t
 * @brief Type define for standard CDC request types.
 */
typedef enum USB_CDC_REQUEST_ID_enum
{
    USB_CDC_REQUEST_SEND_ENCAPSULATED_COMMAND = 0x00,                    /**<Request code to transmit protocol supported command from host to device*/
    USB_CDC_REQUEST_GET_ENCAPSULATED_RESPONSE = 0x01,                    /**<Request code to transmit protocol supported command from device to host*/
    USB_CDC_REQUEST_SET_COMM_FEATURE = 0x02,                             /**<Request code to update settings for given communication feature*/
    USB_CDC_REQUEST_GET_COMM_FEATURE = 0x03,                             /**<Request code to get the current settings for given communication feature*/
    USB_CDC_REQUEST_CLEAR_COMM_FEATURE = 0x04,                           /**<Request code to clear custom settings to given communication feature*/
    USB_CDC_REQUEST_SET_AUX_LINE_STATE = 0x10,                           /**<Request code to connect or disconnect a secondary jack to POTS circuit or CODEC*/
    USB_CDC_REQUEST_SET_HOOK_STATE = 0x11,                               /**<Request code to set the necessary PSTN line relay code for on-hook, off-hook, and caller ID states*/
    USB_CDC_REQUEST_PULSE_SETUP = 0x12,                                  /**<Request code to prepare for a pulse-dialing cycle*/
    USB_CDC_REQUEST_SEND_PULSE = 0x13,                                   /**<Request code to generate a specified number of make/break pulse cycles*/
    USB_CDC_REQUEST_SET_PULSE_TIME = 0x14,                               /**<Request code to set the timing of the make and break periods for pulse dialing*/
    USB_CDC_REQUEST_RING_AUX_JACK = 0x15,                                /**<Request code to generate a ring signal on a secondary phone jack*/
    USB_CDC_REQUEST_SET_LINE_CODING = 0x20,                              /**<Request code to specify typical asynchronous line-character formatting properties*/
    USB_CDC_REQUEST_GET_LINE_CODING = 0x21,                              /**<Request code to get the current asynchronous line-character formatting properties*/
    USB_CDC_REQUEST_SET_CONTROL_LINE_STATE = 0x22,                       /**<Request code to set RS-232/V.24 style control signals*/
    USB_CDC_REQUEST_SEND_BREAK = 0x23,                                   /**<Request code to send special carrier modulation that generates an RS-232 style break*/
    USB_CDC_REQUEST_SET_RINGER_PARMS = 0x30,                             /**<Request code to configure the ringer for the communications device*/
    USB_CDC_REQUEST_GET_RINGER_PARMS = 0x31,                             /**<Request code to return the ringer capabilities of the device and the current status of the deviceâ??s ringer*/
    USB_CDC_REQUEST_SET_OPERATION_PARMS = 0x32,                          /**<Request code to set the operational mode for the device*/
    USB_CDC_REQUEST_GET_OPERATION_PARMS = 0x33,                          /**<Request code to get the current operational mode for the device*/
    USB_CDC_REQUEST_SET_LINE_PARMS = 0x34,                               /**<Request code to change the state of the line for the given interface*/
    USB_CDC_REQUEST_GET_LINE_PARMS = 0x35,                               /**<Request code to report the state of the line for the given interface*/
    USB_CDC_REQUEST_DIAL_DIGITS = 0x36,                                  /**<Request code to dial the DTMF digits over the specified line*/
    USB_CDC_REQUEST_SET_UNIT_PARAMETER = 0x37,                           /**<Request code to set the value of a parameter belonging to a Unit identified by Unit Parameter Structure*/
    USB_CDC_REQUEST_GET_UNIT_PARAMETER = 0x38,                           /**<Request code to return the current value of a parameter belonging to a Unit pointed out by Unit Parameter Structure*/
    USB_CDC_REQUEST_CLEAR_UNIT_PARAMETER = 0x39,                         /**<Request code to restore the default value of a parameter belonging to a Unit identified by Unit Parameter Structure*/
    USB_CDC_REQUEST_GET_PROFILE = 0x3A,                                  /**<Request code to return the profile information as defined by CAPI 2.0*/
    USB_CDC_REQUEST_SET_ETHERNET_MULTICAST_FILTERS = 0x40,               /**<Request code to set the Ethernet device multicast filters as specified in the sequential list of 48 bit Ethernet multicast addresses*/
    USB_CDC_REQUEST_SET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER = 0x41, /**<Request code to set up the specified Ethernet power management pattern filter as described in the data structure*/
    USB_CDC_REQUEST_GET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER = 0x42, /**<Request code to retrieve the status of the specified Ethernet power management pattern filter from the device*/
    USB_CDC_REQUEST_SET_ETHERNET_PACKET_FILTER = 0x43,                   /**<Request code to configure device Ethernet packet filter settings*/
    USB_CDC_REQUEST_GET_ETHERNET_STATISTIC = 0x44,                       /**<Request code to retrieve a statistic based on the feature selector*/
    USB_CDC_REQUEST_SET_ATM_DATA_FORMAT = 0x50,                          /**<Request code to set the data format selected by the host*/
    USB_CDC_REQUEST_GET_ATM_DEVICE_STATISTICS = 0x51,                    /**<Request code to retrieve the device statistics based on the feature selector*/
    USB_CDC_REQUEST_SET_ATM_DEFAULT_VC = 0x52,                           /**<Request code to pre-select the VPI/VCI value for subsequent GetATMVCStatistics requests*/
    USB_CDC_REQUEST_GET_ATM_VC_STATISTICS = 0x53,                        /**<Request code to retrieve the ATM device statistics based on the feature selector for a pre-selected VPI/VCI as stipulated in latest preceding SetATMDefaultVC request*/
    USB_CDC_REQUEST_MDLM_SEMANTIC_MODEL_SPECIFIC_REQUESTS = 0x60,        /**<Request code 0x60 to 0x7F for MDLM Semantic-Model specific requests*/
    USB_CDC_REQUEST_GET_NTB_PARAMETERS = 0x80,                           /**<Request code to retrieve the parameters that describe NTBs for each direction*/
    USB_CDC_REQUEST_GET_NET_ADDRESS = 0x81,                              /**<Request code to return the functionâ??s current EUI-48 station address*/
    USB_CDC_REQUEST_SET_NET_ADDRESS = 0x82,                              /**<Request code to set the functionâ??s current EUI-48 station address*/
    USB_CDC_REQUEST_GET_NTB_FORMAT = 0x83,                               /**<Request code to return the NTB data format currently being used by the function*/
    USB_CDC_REQUEST_SET_NTB_FORMAT = 0x84,                               /**<Request code to select the format of NTB to be used for NTBs transmitted from the function to the host*/
    USB_CDC_REQUEST_GET_NTB_INPUT_SIZE = 0x85,                           /**<Request code to return NTB input size currently being used by the function*/
    USB_CDC_REQUEST_SET_NTB_INPUT_SIZE = 0x86,                           /**<Request code to select the maximum size of NTB that the device is permitted to send to the host*/
    USB_CDC_REQUEST_GET_MAX_DATAGRAM_SIZE = 0x87,                        /**<Request code to return the currently effective maximum datagram size that the function has in effect*/
    USB_CDC_REQUEST_SET_MAX_DATAGRAM_SIZE = 0x88,                        /**<Request code to select the maximum datagram size that either host or function will send in an NTB*/
    USB_CDC_REQUEST_GET_CRC_MODE = 0x89,                                 /**<Request code to return the currently selected CRC mode for NTBs formatted by the function*/
    USB_CDC_REQUEST_SET_CRC_MODE = 0x8A,                                 /**<Request code to control whether the function will append CRCs to datagrams when formatting NTBs to be sent to the host*/

} USB_CDC_REQUEST_ID_t;

/**
 * @ingroup usb_cdc
 * @enum USB_CDC_NOTIFICATION_ID_t
 * @brief Type define for standard CDC notification types.
 */
typedef enum USB_CDC_NOTIFICATION_ID_enum
{
    USB_CDC_NOTIFICATION_NETWORK_CONNECTION = 0x00,                        /**<Notifies the host about network connection status*/
    USB_CDC_NOTIFICATION_RESPONSE_AVAILABLE = 0x01,                        /**<Notifies the host that a response is available*/
    USB_CDC_NOTIFICATION_AUX_JACK_HOOK_STATE = 0x08,                       /**<Indicates that the loop has changed on the auxiliary phone interface of the USB device*/
    USB_CDC_NOTIFICATION_RING_DETECT = 0x09,                               /**<Indicates ring voltage on the POTS line interface of the USB device*/
    USB_CDC_NOTIFICATION_SERIAL_STATE = 0x20,                              /**<Sends asynchronous notification of UART status*/
    USB_CDC_NOTIFICATION_CALL_STATE_CHANGE = 0x28,                         /**<Identifies that a change has occurred to the state of a call on the line corresponding to the interface or union for the line*/
    USB_CDC_NOTIFICATION_LINE_STATE_CHANGE = 0x29,                         /**<Identifies that a change has occurred to the state of the line corresponding to the interface or main interface of a union sending the notification message*/
    USB_CDC_NOTIFICATION_CONNECTION_SPEED_CHANGE = 0x2A,                   /**<Informs the host-networking driver that a change in either the uplink or the downlink bit rate of the connection has occurred*/
    USB_CDC_NOTIFICATION_MDML_SEMANTIC_MODEL_SPECIFIC_NOTIFICATION = 0x40, /**<Notification code 40h-5Fh for MDLM Semantic-Model specific notifications*/

} USB_CDC_NOTIFICATION_ID_t;

/**
 * @ingroup usb_cdc
 * @enum USB_CDC_FUNCTIONAL_DESCRIPTOR_t
 * @brief Type define for standard CDC functional descriptors.
 */
typedef enum USB_CDC_FUNCTIONAL_DESCRIPTOR_enum
{
    USB_CDC_FD_CS_INTERFACE = 0x24, /**<Functional descriptor is connected to interface*/
    USB_CDC_FD_CS_ENDPOINT = 0x25,  /**<Functional descriptor is connected to endpoint*/

} USB_CDC_FUNCTIONAL_DESCRIPTOR_t;

/**
 * @ingroup usb_cdc
 * @enum USB_CDC_COMM_FUNCTIONAL_DESCRIPTOR_SUBTYPE_t
 * @brief Type define for standard CDC communication class functional descriptors.
 */
typedef enum USB_CDC_COMM_FUNCTIONAL_DESCRIPTOR_SUBTYPE_enum
{
    USB_CDC_COMM_FD_SUBTYPE_HEADER = 0x00,                                               /**<Functional descriptor subtype: Header, which marks the beginning of the concatenated set of functional descriptors for the interface*/
    USB_CDC_COMM_FD_SUBTYPE_CALL_MANAGEMENT = 0x01,                                      /**<Functional descriptor subtype: Call Management*/
    USB_CDC_COMM_FD_SUBTYPE_ABSTRACT_CONTROL_MANAGEMENT = 0x02,                          /**<Functional descriptor subtype: Abstract Control Management*/
    USB_CDC_COMM_FD_SUBTYPE_DIRECT_LINE_MANAGEMENT = 0x03,                               /**<Functional descriptor subtype: Direct Line Management*/
    USB_CDC_COMM_FD_SUBTYPE_TELEPHONE_RINGER = 0x04,                                     /**<Functional descriptor subtype: Telephone Ringer*/
    USB_CDC_COMM_FD_SUBTYPE_TELEPHONE_CALL_AND_LINE_STATE_REPORTING_CAPABILITIES = 0x05, /**<Functional descriptor subtype: Telephone Call and Line State Reporting Capabilities*/
    USB_CDC_COMM_FD_SUBTYPE_UNION = 0x06,                                                /**<Functional descriptor subtype: Union*/
    USB_CDC_COMM_FD_SUBTYPE_COUNTRY_SELECTION = 0x07,                                    /**<Functional descriptor subtype: Country Selection*/
    USB_CDC_COMM_FD_SUBTYPE_TELEPHONE_OPERATIONAL_MODES = 0x08,                          /**<Functional descriptor subtype: Telephone Operational Modes*/
    USB_CDC_COMM_FD_SUBTYPE_USB_TERMINAL = 0x09,                                         /**<Functional descriptor subtype: USB Terminal*/
    USB_CDC_COMM_FD_SUBTYPE_NETWORK_CHANNEL = 0x0A,                                      /**<Functional descriptor subtype: Network Channel Terminal*/
    USB_CDC_COMM_FD_SUBTYPE_PROTOCOL_UNIT = 0x0B,                                        /**<Functional descriptor subtype: Protocol Unit*/
    USB_CDC_COMM_FD_SUBTYPE_EXTENSION_UNIT = 0x0C,                                       /**<Functional descriptor subtype: Extension Unit*/
    USB_CDC_COMM_FD_SUBTYPE_MULTI_CHANNEL_MANAGEMENT = 0x0D,                             /**<Functional descriptor subtype: Multi-Channel Management*/
    USB_CDC_COMM_FD_SUBTYPE_CAPI_CONTROL_MANAGEMENT = 0x0E,                              /**<Functional descriptor subtype: Common application programming interface Control Management*/
    USB_CDC_COMM_FD_SUBTYPE_ETHERNET_NETWORKING = 0x0F,                                  /**<Functional descriptor subtype: Ethernet Networking*/
    USB_CDC_COMM_FD_SUBTYPE_ATM_NETWORKING = 0x10,                                       /**<Functional descriptor subtype: ATM Networking*/
    USB_CDC_COMM_FD_SUBTYPE_WIRELESS_HANDSET_CONTROL_MODEL = 0x11,                       /**<Functional descriptor subtype: Wireless Handset Control Model*/
    USB_CDC_COMM_FD_SUBTYPE_MOBILE_DIRECT_LINE_MODEL = 0x12,                             /**<Functional descriptor subtype: Mobile Direct Line Model*/
    USB_CDC_COMM_FD_SUBTYPE_MDLM_DETAIL = 0x13,                                          /**<Functional descriptor subtype: Mobile Direct Line Model Detail*/
    USB_CDC_COMM_FD_SUBTYPE_DEVICE_MANAGEMENT_MODEL = 0x14,                              /**<Functional descriptor subtype: Device Management Model*/
    USB_CDC_COMM_FD_SUBTYPE_OBEX = 0x15,                                                 /**<Functional descriptor subtype: Object exchange*/
    USB_CDC_COMM_FD_SUBTYPE_COMMAND_SET = 0x16,                                          /**<Functional descriptor subtype: Command Set*/
    USB_CDC_COMM_FD_SUBTYPE_COMMAND_SET_DETAIL = 0x17,                                   /**<Functional descriptor subtype: Command Set Detail*/
    USB_CDC_COMM_FD_SUBTYPE_TELEPHONE_CONTROL_MODEL = 0x18,                              /**<Functional descriptor subtype: Telephone Control Model*/
    USB_CDC_COMM_FD_SUBTYPE_OBEX_SERVICE_IDENTIFIER = 0x19,                              /**<Functional descriptor subtype: Object exchange Service Identifier*/
    USB_CDC_COMM_FD_SUBTYPE_NCM = 0x1A,                                                  /**<Functional descriptor subtype: Network control model*/

} USB_CDC_COMM_FUNCTIONAL_DESCRIPTOR_SUBTYPE_t;

/**
 * @ingroup usb_cdc
 * @enum USB_CDC_DATA_FUNCTIONAL_DESCRIPTOR_SUBTYPE_t
 * @brief Type define for standard CDC data class functional descriptors.
 */
typedef enum USB_CDC_DATA_FUNCTIONAL_DESCRIPTOR_SUBTYPE_enum
{
    USB_CDC_DATA_FD_HEADER = 0x00, /**<functional descriptor subtype: Header, which marks the beginning of the concatenated set of functional descriptors for the interface*/

} USB_CDC_DATA_FUNCTIONAL_DESCRIPTOR_SUBTYPE_t;

/**
 * @ingroup usb_cdc
 * @struct USB_CDC_HEADER_FUNCTIONAL_DESCRIPTOR_t
 * @brief Type define for the CDC Header functional descriptor subtype.
 */
typedef struct USB_CDC_HEADER_FUNCTIONAL_DESCRIPTOR_struct
{
    uint8_t bLength;            /**<Size of this descriptor in bytes*/
    uint8_t bDescriptorType;    /**<CDC functional descriptor type*/
    uint8_t bDescriptorSubtype; /**<CDC functional descriptor subtype*/
    uint16_t bcdCDC;            /**<USB Class Definitions for Communications Devices Specification release number in binary-coded decimal*/

} USB_CDC_HEADER_FUNCTIONAL_DESCRIPTOR_t;

/**
 * @ingroup usb_cdc
 * @struct USB_CDC_ACM_FUNCTIONAL_DESCRIPTOR_t
 * @brief Type define for the CDC Abstract Control Management functional descriptor subtype.
 */
typedef struct USB_CDC_ACM_FUNCTIONAL_DESCRIPTOR_struct
{
    uint8_t bLength;            /**<Size of this descriptor in bytes*/
    uint8_t bDescriptorType;    /**<CDC functional descriptor type*/
    uint8_t bDescriptorSubtype; /**<CDC functional descriptor subtype*/
    uint8_t bmCapabilities;     /**<The capabilities that this configuration supports. A bit value of zero means that the request is not supported.*/

} USB_CDC_ACM_FUNCTIONAL_DESCRIPTOR_t;

/**
 * @ingroup usb_cdc
 * @enum USB_CDC_ACM_FUNCTIONAL_CAPABILITIES_t
 * @brief Type define for the CDC Abstract Control Management functional descriptor capabilities.
 */
typedef enum USB_CDC_ACM_FUNCTIONAL_CAPABILITIES_enum
{
    USB_CDC_ACM_FUNCTIONAL_CAPABILITIES_COMM_FEATURE = 0x01,          /**<Device supports the request combination of Set_Comm_Feature, Clear_Comm_Feature, and Get_Comm_Feature*/
    USB_CDC_ACM_FUNCTIONAL_CAPABILITIES_CONTROL_LINE_CODING = 0x02,   /**<Device supports the request combination of Set_Line_Coding, Set_Control_Line_State, Get_Line_Coding, and the notification Serial_State*/
    USB_CDC_ACM_FUNCTIONAL_CAPABILITIES_SEND_BREAK_bm = 0x04,         /**<Device supports the request Send_Break*/
    USB_CDC_ACM_FUNCTIONAL_CAPABILITIES_NETWORK_CONNECTION_bm = 0x08, /**<Device supports the notification Network_Connection*/
} USB_CDC_ACM_FUNCTIONAL_CAPABILITIES_t;

#ifdef USB_CDC_UNION_SUBORDINATE_NUM
/**
 * @ingroup usb_cdc
 * @struct USB_CDC_UNION_FUNCTIONAL_DESCRIPTOR_t
 * @brief Type define for the CDC union functional descriptor subtype.
 */
typedef struct USB_CDC_UNION_FUNCTIONAL_DESCRIPTOR_struct
{
    uint8_t bLength;                                              /**<Size of this descriptor in bytes*/
    uint8_t bDescriptorType;                                      /**<CDC functional descriptor type*/
    uint8_t bDescriptorSubtype;                                   /**<CDC functional descriptor subtype*/
    uint8_t bControlInterface;                                    /**<The interface number of the controlling interface*/
    uint8_t bSubordinateInterface[USB_CDC_UNION_SUBORDINATE_NUM]; /**<The interface numbers of the subordinate interfaces*/

} USB_CDC_UNION_FUNCTIONAL_DESCRIPTOR_t;
#endif

/**
 * @ingroup usb_cdc
 * @struct USB_CDC_COUNTRY_SELECTION_FUNCTIONAL_DESCRIPTOR_t
 * @brief Type define for the CDC country selection functional descriptor subtype.
 */
typedef struct USB_CDC_COUNTRY_SELECTION_FUNCTIONAL_DESCRIPTOR_struct
{
    uint8_t bLength;             /**<Size of this descriptor in bytes*/
    uint8_t bDescriptorType;     /**<CDC functional descriptor type*/
    uint8_t bDescriptorSubtype;  /**<CDC functional descriptor subtype*/
    uint8_t iCountryCodeRelDate; /**<Index of the release date in ISO 3166 Country Codes*/
    uint16_t wCountryCode0;      /**<First country code*/

} USB_CDC_COUNTRY_SELECTION_FUNCTIONAL_DESCRIPTOR_t;

// Request:

/**
 * @ingroup usb_cdc
 * @enum USB_CDC_LINE_CODING_STOP_BITS_t
 * @brief Type define for the CDC Line Encoding stop bits formats.
 */
typedef enum USB_CDC_LINE_CODING_STOP_BITS_enum
{
    USB_CDC_LINE_CODING_ONE_STOP_BIT = 0x00,              /**<Number of stop bits: one*/
    USB_CDC_LINE_CODING_ONE_AND_ONE_HALF_STOP_BIT = 0x01, /**<Number of stop bits: one and a half*/
    USB_CDC_LINE_CODING_TWO_STOP_BITS = 0x02,             /**<Number of stop bits: two*/

} USB_CDC_LINE_CODING_STOP_BITS_t;

/**
 * @ingroup usb_cdc
 * @enum USD_CDC_LINE_CODING_PARITY_t
 * @brief Type define for CDC Line Encoding parity.
 */
typedef enum USD_CDC_LINE_CODING_PARITY_enum
{
    USB_CDC_LINE_CODING_PARITY_NONE = 0x00,  /**<Parity mode: none*/
    USB_CDC_LINE_CODING_PARITY_ODD = 0x01,   /**<Parity mode: odd*/
    USB_CDC_LINE_CODING_PARITY_EVEN = 0x02,  /**<Parity mode: even*/
    USB_CDC_LINE_CODING_PARITY_MARK = 0x03,  /**<Parity mode: mark*/
    USB_CDC_LINE_CODING_PARITY_SPACE = 0x04, /**<Parity mode: space*/

} USD_CDC_LINE_CODING_PARITY_t;

/**
 * @ingroup usb_cdc
 * @enum USD_CDC_LINE_CODING_DATA_BITS_t
 * @brief Type define for the CDC Line Encoding data bits.
 */
typedef enum USD_CDC_LINE_CODING_DATA_BITS_enum
{
    USB_CDC_LINE_CODING_5_DATA_BITS = 0x05,  /**<Data transmission size: five bits*/
    USB_CDC_LINE_CODING_6_DATA_BITS = 0x06,  /**<Data transmission size: six bits*/
    USB_CDC_LINE_CODING_7_DATA_BITS = 0x07,  /**<Data transmission size: seven bits*/
    USB_CDC_LINE_CODING_8_DATA_BITS = 0x08,  /**<Data transmission size: eight bits*/
    USB_CDC_LINE_CODING_16_DATA_BITS = 0x10, /**<Data transmission size: sixteen bits*/

} USD_CDC_LINE_CODING_DATA_BITS_t;

/**
 * @ingroup usb_cdc
 * @struct USB_CDC_LINE_CODING_t
 * @brief Type define for CDC Line Encoding.
 */
typedef struct USB_CDC_LINE_CODING_struct
{
    uint32_t dwDTERate;                          /**<Data terminal rate, in bits per second*/
    USB_CDC_LINE_CODING_STOP_BITS_t bCharFormat; /**<Number of stop bits*/
    USD_CDC_LINE_CODING_PARITY_t bParityType;    /**<Parity control mode*/
    USD_CDC_LINE_CODING_DATA_BITS_t bDataBits;   /**<Number of data bits*/

} USB_CDC_LINE_CODING_t;

/**
 * @ingroup usb_cdc
 * @enum USD_CDC_CONTROL_LINE_STATE_t
 * @brief Type define for CDC Control Line State.
 */
typedef enum USD_CDC_CONTROL_LINE_STATE_enum
{
    USB_CDC_DATA_TERMINAL_READY_bm = 0x0001, /**<Indicates to DCE if DTE is present or not. This signal corresponds to V.24 signal 108/2 and RS-232 signal DTR.*/
    USB_CDC_REQUEST_TO_SEND_bm = 0x0002,     /**<Carrier control for half duplex modems. This signal corresponds to V.24 signal 105 and RS-232 signal RTS.*/

} USD_CDC_CONTROL_LINE_STATE_t;

#endif /* USB_PROTOCOL_CDC_H */