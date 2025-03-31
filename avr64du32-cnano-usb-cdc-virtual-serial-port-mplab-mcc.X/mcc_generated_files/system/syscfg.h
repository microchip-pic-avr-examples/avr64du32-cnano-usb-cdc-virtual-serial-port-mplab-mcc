/**
 * SYSCFG Generated Driver API Header File
 * 
 * @file syscfg.h
 * 
 * @defgroup  syscfg SYSCFG
 * 
 * @brief This is the generated header file for the SYSCFG driver
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

#ifndef SYSCFG_H
#define SYSCFG_H

/**
  Section: Included Files
*/

#include <stdbool.h>
#include <stdint.h>

/**
  Section: SYSCFG APIs
*/

/**
 * @ingroup syscfg
 * @brief  Initializes the SYSCFG driver. This routine is called only once during system initialization, before calling other APIs.
 * @param None.
 * @return None.
 */ 
void SYSCFG_Initialize(void);

/**
 * @ingroup syscfg
 * @brief  Returns the SYSCFG Revision ID.
 * @param None.
 * @return uint8_t
 */ 
uint8_t SYSCFG_GetRevId(void);

/**
 * @ingroup syscfg
 * @brief  Enables the SYSCFG USB voltage regulator.
 * @param None.
 * @return None.
 */ 
 void SYSCFG_UsbVregEnable(void);

/**
 * @ingroup syscfg
 * @brief  Disables the SYSCFG USB voltage regulator.
 * @param None.
 * @return None.
 */ 
void SYSCFG_UsbVregDisable(void);


#endif // SYSCFG_H
/**
 End of File
*/
