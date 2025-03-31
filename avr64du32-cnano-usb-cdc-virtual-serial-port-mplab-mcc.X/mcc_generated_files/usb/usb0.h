/**
 * USB0 Generated Driver API Header File
 * 
 * @file usb0.h
 * 
 * @defgroup  usb0 USB0
 * 
 * @brief This file contains the API prototypes for the USB0 driver.
 *
 * @version USB0 Driver Version 1.0.0
*/
/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef USB0_H
#define USB0_H

/**
 * @ingroup usb0
 * @typedef void *USB_cb_t
 * @brief Data type for the interrupt handlers called by USB. The default value is set to NULL which means that no callback function will be used.
 */  
typedef void (*USB_cb_t)(void);

/**
  Section: USB0 APIs
*/

/**
 * @ingroup usb0
 * @brief Initializes USB0.
 * @param None.
 * @return None.
 */ 
void USB0_Initialize(void);

/**
 * @ingroup usb0
 * @brief Registers a callback function handling the Interrupt Service Routine (ISR) if a Transaction Complete interrupt flag is set.
 * @param USB_cb_t cb - Callback function for a transaction complete event
 * @return None.
 */ 
void USB0_TrnComplCallbackRegister(USB_cb_t cb);

/**
 * @ingroup usb0
 * @brief Registers a callback function handling the ISR if a Bus Event interrupt flag is set.
 * @param USB_cb_t cb - Callback function for a bus event
 * @return None.
 */ 
void USB0_BusEventCallbackRegister(USB_cb_t cb);

#endif // USB0_H
/**
 End of File
*/
