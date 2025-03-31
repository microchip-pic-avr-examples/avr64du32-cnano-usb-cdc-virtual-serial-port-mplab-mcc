
/**
 * SYSCFG Generated Driver File
 * 
 * @file syscfg.c
 * 
 * @ingroup syscfg
 * 
 * @brief This is the generated driver implementation file for the SYSCFG driver.
 *
 * @version SYSCFG Driver Version 1.0.0
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

/**
  Section: Included Files
*/

#include "../../system/utils/compiler.h"
#include "../syscfg.h"

/**
  Section: SYSCFG APIs
*/

void SYSCFG_Initialize(void)
{
  SYSCFG.VUSBCTRL = (0 << SYSCFG_USBVREG_bp);  // USBVREG DISABLE;  
}
uint8_t SYSCFG_GetRevId(void)
{
  return SYSCFG.REVID;
}
inline void SYSCFG_UsbVregEnable(void)
{
  SYSCFG.VUSBCTRL = SYSCFG_USBVREG_bm;
}
inline void SYSCFG_UsbVregDisable(void)
{
  SYSCFG.VUSBCTRL = ~SYSCFG_USBVREG_bm;
}

/**
 End of File
*/