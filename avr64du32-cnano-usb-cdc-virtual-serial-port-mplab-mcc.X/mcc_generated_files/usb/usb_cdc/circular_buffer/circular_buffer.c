/**
 * CIRCULARBUFFER CDC Circular Buffer Source File
 * @file circular_buffer.c
 * @ingroup usb_cdc
 * @brief This file contains the implementation for a circular buffer.
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

#include "circular_buffer.h"

BUFFER_RETURN_CODE_t CIRCBUF_Enqueue(CIRCULAR_BUFFER_t *buffer, uint8_t data)
{
    BUFFER_RETURN_CODE_t status = BUFFER_SUCCESS;

    // Finds next buffer head
    uint16_t nextHead = buffer->head + 1U;

    // Checks if next head at end of array reached, wraps around
    if (buffer->maxLength <= nextHead)
    {
        nextHead = 0;
    }

    // Checks if buffer is full
    if (buffer->tail == nextHead)
    {
        status = BUFFER_FULL;
    }
    else
    {
        // Writes data to buffer
        buffer->content[buffer->head] = data;
        // Updates head
        buffer->head = nextHead;
    }

    return status;
}

BUFFER_RETURN_CODE_t CIRCBUF_Dequeue(CIRCULAR_BUFFER_t *buffer, uint8_t *data)
{
    BUFFER_RETURN_CODE_t status = BUFFER_SUCCESS;

    uint16_t nextTail;

    // Checks if buffer is empty
    if (buffer->head == buffer->tail)
    {
        status = BUFFER_EMPTY;
    }
    else
    {
        // Finds next buffer tail
        nextTail = buffer->tail + 1U;

        // Checks if next tail at end of array reached, wraps around
        if (buffer->maxLength <= nextTail)
        {
            nextTail = 0;
        }

        // Reads data from buffer
        *data = buffer->content[buffer->tail];
        // Updates tail
        buffer->tail = nextTail;
    }

    return status;
}

bool CIRCBUF_Empty(CIRCULAR_BUFFER_t *buffer)
{
    // Checks if buffer is empty
    return (buffer->head == buffer->tail);
}

bool CIRCBUF_Full(CIRCULAR_BUFFER_t *buffer)
{
    // Finds next buffer head
    uint16_t nextHead = buffer->head + 1U;

    // Checks if next head at end of array reached, wraps around
    if (buffer->maxLength <= nextHead)
    {
        nextHead = 0;
    }

    // Returns if buffer is full
    return (buffer->tail == nextHead);
}

uint16_t CIRCBUF_FreeSpace(CIRCULAR_BUFFER_t *buffer)
{
    uint16_t freeSpace = 0;
    if (buffer->head >= buffer->tail)
    {
        freeSpace = buffer->tail + buffer->maxLength - buffer->head - 1U;
    }
    else // Tail > head: buffer wrapped around
    {
        freeSpace = buffer->tail - buffer->head - 1U;
    }
    return freeSpace;
}