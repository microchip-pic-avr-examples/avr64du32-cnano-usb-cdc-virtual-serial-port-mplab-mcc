/**
 * MAIN
 * @file main.c
 * @defgroup main MAIN
 * @brief This file contain an example for running Virtual Serial Port communication over USB for AVR DU
 * @version MAIN Driver Version 1.0.0
 */
/*
ï¿½ [2024] Microchip Technology Inc. and its subsidiaries.

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

// MCC includes
#include "mcc_generated_files/system/system.h"
#include "usb_cdc.h"
#include "usb_cdc_virtual_serial_port.h"

// Standard library includes
#include <stdbool.h>
#include <util/delay.h>

// Number of consecutive equal AC measurements before power is seen as stable
#define AC_MEASUREMENT_STABLE_COUNT 5U

// USB status variables
volatile RETURN_CODE_t status = SUCCESS;
volatile CDC_RETURN_CODE_t cdcStatus = CDC_SUCCESS;

// Interrupt variable
volatile bool vbusFlag = false;

// Private function declarations
void USB_ConnectionHandler(void);
void USB_PowerHandler(void);

int main(void)
{
    // Data variable
    uint8_t cdcData;

    SYSTEM_Initialize();

    // Set callbacks
    RTC_SetPITIsrCallback(USB_PowerHandler);

    while (1)
    {
        USB_ConnectionHandler();

        // If USB error detected
        if (SUCCESS != status)
        {
            while (1)
            {
                LED_Toggle();
                _delay_ms(500);
            }
        }
        else
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
                }

                // Running CDC Virtual Serial Port handler
                status = USB_CDCVirtualSerialPortHandler();
            }
        }
    }
}

/**
 * Routine that checks the connectivity of the USB peripheral and start/stops the USB driver when connected/disconnected
 */
void USB_ConnectionHandler(void)
{
    static volatile bool prevVbusState = false;
    // Check if VBUS was true last check, indicating that USB was connected
    if (prevVbusState == true)
    {
        // Handle USB Transfers
        status = USBDevice_Handle();
    }
    // Get current status of VBUS
    bool currentVbusState = vbusFlag;
    // If changes to USB VBUS state
    if (currentVbusState != prevVbusState)
    {
        // If USB has been connected
        if (currentVbusState == true)
        {
            // Start USB operations
            status = USB_Start();
            LED_SetHigh();
        }
        else
        {
            // Stop USB operations
            status = USB_Stop();
            LED_SetLow();
        }
        // Save state
        prevVbusState = currentVbusState;
    }
}

/**
 * Interrupt routine used to check VBUS status using the Real-Time Counter overflow interrupt and Analog Comparator
 */
void USB_PowerHandler(void)
{
    // Helper variables for RTC and AC
    static volatile uint8_t acStateCounter = 0U;
    static volatile uint8_t acPrevState = 0U;

    uint8_t acCurrentState = AC0_Read(); // Saves the current state of the AC status register ('1' means above threshold)

    // Makes sure that the AC state has been the same for a certain number of PIT interrupts
    if (acStateCounter == AC_MEASUREMENT_STABLE_COUNT)
    {
        if (acCurrentState) // When CMPSTATE is high, the AC output is high which means the VBUS is above the threshold and the pull-up on data+ should be enabled.
        {
            vbusFlag = true;
        }
        else
        {
            vbusFlag = false;
        }
        acStateCounter++; // Increment the counter to not run start/stop multiple times without an actual state change
    }
    // Increments a counter if the AC has been in the same state for a certain number of PIT interrupts
    else if (acCurrentState == acPrevState)
    {
        if (acStateCounter < AC_MEASUREMENT_STABLE_COUNT)
        {
            acStateCounter++;
        }
        else
        {
            ; // Stops counting if the AC has been in the same state for a while.
        }
    }
    else
    {
        acStateCounter = 0; // Resets the PIT counter if a state change has occurred.
    }
    acPrevState = acCurrentState;
}