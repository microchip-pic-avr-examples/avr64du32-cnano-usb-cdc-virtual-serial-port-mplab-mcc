/**
 * CIRCULARBUFFER CDC Circular Buffer Header File
 * @file circular_buffer.h
 * @ingroup usb_cdc
 * @brief This file contains prototypes and datatypes for a circular buffer.
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

#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

#include <stdint.h>
#include <stdbool.h>
#include <usb_common_elements.h>

/**
 * @ingroup usb_cdc
 * @enum BUFFER_RETURN_CODE_t
 * @brief Type define for circular buffer return codes.
 */
typedef enum BUFFER_RETURN_CODE_enum
{
    BUFFER_SUCCESS = 0, /**<Action successfully executed*/
    BUFFER_FULL = -1,   /**<Error triggered by full buffer*/
    BUFFER_EMPTY = -2   /**<Error triggered by empty buffer*/
} BUFFER_RETURN_CODE_t;

/**
 * @ingroup usb_cdc
 * @struct CIRCULAR_BUFFER_t
 * @brief Type define for circular buffers of varying length.
 */
typedef struct CIRCULAR_BUFFER_struct
{
    uint8_t *content;         /**<Actual buffer data*/
    uint16_t head;            /**<Index of first empty slot in buffer*/
    uint16_t tail;            /**<Index of first occupied buffer slot*/
    const uint16_t maxLength; /**<Maximum length of buffer*/
} CIRCULAR_BUFFER_t;

/**
 * @ingroup usb_cdc
 * @brief Adds input data to circular buffer if there is space available.
 * @param buffer - Circular buffer address
 * @param data - Intput data
 * @return status - Result of the addition process
 */
BUFFER_RETURN_CODE_t CIRCBUF_Enqueue(CIRCULAR_BUFFER_t *buffer, uint8_t data);

/**
 * @ingroup usb_cdc
 * @brief Pulls data from the circular buffer if it's available.
 * @param buffer - Circular buffer address
 * @param data - Output data variable address
 * @return status - Result of the retrieval process
 */
BUFFER_RETURN_CODE_t CIRCBUF_Dequeue(CIRCULAR_BUFFER_t *buffer, uint8_t *data);

/**
 * @ingroup usb_cdc
 * @brief Checks if the circular buffer is empty.
 * @param buffer - Circular buffer address
 * @retval 0 - Buffer not full
 * @retval 1 - Buffer full
 */
bool CIRCBUF_Empty(CIRCULAR_BUFFER_t *buffer);

/**
 * @ingroup usb_cdc
 * @brief Checks if the circular buffer is full.
 * @param buffer - Circular buffer address
 * @retval 0 - Buffer not full
 * @retval 1 - Buffer full
 */
bool CIRCBUF_Full(CIRCULAR_BUFFER_t *buffer);

/**
 * @ingroup usb_cdc
 * @brief Returns the number of available bytes in the circular buffer.
 * @param buffer - Circular buffer address
 * @return freeSpace - Available bytes
 */
uint16_t CIRCBUF_FreeSpace(CIRCULAR_BUFFER_t *buffer);

#endif /* CIRCULAR_BUFFER_H_ */