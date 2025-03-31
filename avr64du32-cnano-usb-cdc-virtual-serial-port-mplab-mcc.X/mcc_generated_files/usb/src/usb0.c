/**
 * USB0 Generated Driver File
 * 
 * @file usb0.c
 * 
 * @ingroup usb0
 * 
 * @brief This file contains the API implementations for the USB0 driver.
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

#include <stddef.h>
#include "../usb0.h"
#include "../../system/syscfg.h"
#include "../../system/utils/compiler.h"

static void USB0_DefaultTrnComplCallback(void);
static void USB0_DefaultBusEventCallback(void);
static void (*USB0_TrnCompl_isr_cb)(void) = &USB0_DefaultTrnComplCallback;
static void (*USB0_BusEvent_isr_cb)(void) = &USB0_DefaultBusEventCallback;

void USB0_Initialize(void)
{    
    // OVF disabled; RESET disabled; RESUME disabled; SOF disabled; STALLED disabled; SUSPEND disabled; UNF disabled; 
    USB0.INTCTRLA = 0x0;
    // GNDONE disabled; SETUP disabled; TRNCOMPL disabled; 
    USB0.INTCTRLB = 0x0;
    SYSCFG_UsbVregDisable();
}

void USB0_TrnComplCallbackRegister(USB_cb_t cb)
{
    USB0_TrnCompl_isr_cb = cb;
}

void USB0_BusEventCallbackRegister(USB_cb_t cb)
{
    USB0_BusEvent_isr_cb = cb;
}

static void USB0_DefaultTrnComplCallback(void)
{
    // Clear the interrupt Flags
    USB0.INTFLAGSB = USB_TRNCOMPL_bm | USB_GNDONE_bm | USB_SETUP_bm;    
}

static void USB0_DefaultBusEventCallback(void)
{
    // Clear the interrupt Flags
    USB0.INTFLAGSA = USB_SOF_bm | USB_SUSPEND_bm | USB_RESUME_bm | USB_RESET_bm | USB_STALLED_bm | USB_UNF_bm | USB_OVF_bm;
}

ISR(USB0_TRNCOMPL_vect) {
    if (USB0_TrnCompl_isr_cb != NULL)
    {
        (*USB0_TrnCompl_isr_cb)();
    }
}

ISR(USB0_BUSEVENT_vect) {
    if (USB0_BusEvent_isr_cb != NULL) {
        (*USB0_BusEvent_isr_cb)();
    }
}

/**
 End of File
*/
