/**
 * MAIN
 * @file main.c
 * @defgroup main MAIN
 * @brief This file contain an example for running Virtual Serial Port communication over USB for AVR DU
 * @version MAIN Driver Version 1.0.0
 */

/*
� [2024] Microchip Technology Inc. and its subsidiaries.

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

#include "mcc_generated_files/system/system.h"
#include "usb_cdc.h"
#include "usb_cdc_virtual_serial_port.h"

// Status variables
volatile RETURN_CODE_t status = SUCCESS;
volatile CDC_RETURN_CODE_t cdcStatus = CDC_SUCCESS;

// Data variable
uint8_t cdcData;

int main(void)
{
    SYSTEM_Initialize();

    while (1)
    {
        // Running USB handle
        status = USBDevice_Handle();

        if (SUCCESS == status)
        {
            // Tests if DTE is set and USB ready for transfer
            if (true == USB_CDCDataTerminalReady())
            {
                // Checks that CDC TX buffer is not full or pipe is busy
                if (false == USB_CDCTxBusy())
                {
                    // Retrieves CDC data if available and writes it back over CDC
                    cdcStatus = USB_CDCRead(&cdcData);
                    if (CDC_SUCCESS == cdcStatus)
                    {
                        cdcStatus = USB_CDCWrite(cdcData);
                    }
                    else
                    {
                        // CDC buffer empty no data to transmit
                        cdcStatus = CDC_SUCCESS;
                    }
                }

                // Running CDC Virtual Serial Port handler
                status = USB_CDCVirtualSerialPortHandler();
            }
            else
            {
                ; // No terminal session active
            }
        }
        else
        {
            ; // USB handle error
        }
    }
}