/**
 * AC0 Generated Driver API Header File
 * 
 * @file ac0.h
 * 
 * @defgroup  ac0 AC0
 * 
 * @brief Contains the API prototypes for the AC0 driver.
 *
 * @version AC0 Driver Version 1.0.0
*/
/*
© [2024] Microchip Technology Inc. and its subsidiaries.

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


#ifndef AC0_H_INCLUDED
#define AC0_H_INCLUDED
 
#include "../system/utils/compiler.h"

#ifdef __cplusplus  
extern "C" {
#endif

/**
 * @ingroup ac0
 * @brief Pointer to a function to be used as a callback handler when a comparator interrupt occurs.
 * @param None.
 * @return None.
 */
typedef void (*ac_cb_t)(void);

/**
 * @ingroup ac0
 * @brief Initializes the AC0. This routine is called only once during system initialization, before calling other APIs.
 * @param None.
 * @return None.
*/
int8_t AC0_Initialize(void);

/**
 * @ingroup ac0
 * @brief Controls the input signal to the positive and negative inputs of the AC0.
 * @pre Initialize the AC0 with AC0_Initialize() before calling this API.
 * @param uint8_t Mode.
 * @return None.
 */
void AC0_MuxSet(uint8_t);

/**
 * @ingroup ac0
 * @brief Returns the OUT signal state for the AC0.
 * @pre Initialize the AC0 with AC0_Initialize() before calling this API.
 * @param None.
 * @retval True - The AC OUT signal is high.
 * @retval False - the AC OUT signal is low.
 */
bool AC0_Read(void);

/**
 * @ingroup ac0
 * @brief Setter function for the AC0 comparator callback.
 * @pre None.
 * @param CallbackHandler - Pointer to custom callback.
 * @return None.
 */
void AC0_CallbackRegister(ac_cb_t);

/**
 * @ingroup ac0
 * @brief Sets the DAC voltage reference (DACREF) data value for the AC0.
 * @pre Initialize the AC0 with AC0_Initialize() before calling this API.
 * @param uint8_t- Value to be written to the DACREF register.
 * @return None.
 */
void AC0_DACRefValueSet(uint8_t);

#ifdef __cplusplus
}
#endif

#endif  /* AC0_H_INCLUDED */