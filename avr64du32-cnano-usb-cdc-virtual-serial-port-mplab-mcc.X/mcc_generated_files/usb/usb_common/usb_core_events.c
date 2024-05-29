/**
 * USBCOREEVENTS USB Core Events Source File
 * @file usb_core_events.h
 * @ingroup usb_core_events
 * @brief Event handling for the USB Core Stack.
 * @version USB Device Core Version 1.0.0
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

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <usb_common_elements.h>
#include <usb_config.h>
#include <usb_core.h>
#include <usb_core_events.h>
#include <usb_peripheral.h>
#include <usb_protocol_headers.h>

USB_EVENT_HANDLERS_t event;

RETURN_CODE_t USB_EventHandler(void)
{
    RETURN_CODE_t status = SUCCESS;

    if (USB_EventSOFIsReceived() == true)
    {
        USB_EventSOFClear();
        if (NULL != event.SOFCallback)
        {
            event.SOFCallback();
        }
    }
    if (USB_EventResetIsReceived() == true)
    {
        USB_EventResetClear();
        if (NULL != event.ResetCallback)
        {
            event.ResetCallback();
        }
        USB_PIPE_t pipe = { .address = 0 };
        while (pipe.address < USB_EP_NUM)
        {
            pipe.direction = USB_EP_DIR_IN;
            if (SUCCESS == status)
            {
                status = USB_TransferAbort(pipe);
            }
            pipe.direction = USB_EP_DIR_OUT;
            if (SUCCESS == status)
            {
                status = USB_TransferAbort(pipe);
            }
            pipe.address++;
        }
        status = USB_Reset();
    }
    uint8_t eventOverUnderflow = USB_EventOverUnderflowIsReceived();
    if (0u < eventOverUnderflow)
    {
        USB_EventOverUnderflowClear();
        uint8_t controlOverUnderflow = USB_ControlOverUnderflowIsReceived();
        if (0u < controlOverUnderflow)
        {
            status = USB_ControlProcessOverUnderflow(controlOverUnderflow);
        }
        else
        {
            // Non-control overunderflows currently ignored by event handler
            status = SUCCESS;
        }
    }
    if (USB_EventSuspendIsReceived() == true)
    {
        USB_EventSuspendClear();
        if (NULL != event.SuspendCallback)
        {
            event.SuspendCallback();
        }
    }
    if (USB_EventResumeIsReceived() == true)
    {
        USB_EventResumeClear();
        if (NULL != event.ResumeCallback)
        {
            event.ResumeCallback();
        }
    }
    if (USB_EventStalledIsReceived() == true)
    {
        USB_EventStalledClear();
        USB_PIPE_t pipe = { .address = 0x00, .direction = USB_EP_DIR_OUT };
        status = USB_HandleEventStalled(pipe);
    }
    return status;
}

void USB_SetConfigurationCallbackRegister(USB_SETUP_EVENT_CALLBACK_t callback)
{
    event.SetConfiguration = callback;
}

void USB_SetInterfaceCallbackRegister(USB_SETUP_EVENT_CALLBACK_t callback)
{
    event.SetInterface = callback;
}

void USB_InterfaceDisabledCallbackRegister(USB_EVENT_CALLBACK_t callback)
{
    event.InterfaceDisabled = callback;
}

void USB_VendorRequestCallbackRegister(USB_SETUP_PROCESS_CALLBACK_t callback)
{
    event.VendorRequest = callback;
}

void USB_ClassRequestCallbackRegister(USB_SETUP_PROCESS_CALLBACK_t callback)
{
    event.ClassRequest = callback;
}

void USB_OtherRequestCallbackRegister(USB_SETUP_PROCESS_CALLBACK_t callback)
{
    event.OtherRequest = callback;
}

void USB_SOFCallbackRegister(USB_EVENT_CALLBACK_t callback)
{
    event.SOFCallback = callback;
}

void USB_ResetCallbackRegister(USB_EVENT_CALLBACK_t callback)
{
    event.ResetCallback = callback;
}

void USB_SuspendCallbackRegister(USB_EVENT_CALLBACK_t callback)
{
    event.SuspendCallback = callback;
}

void USB_ResumeCallbackRegister(USB_EVENT_CALLBACK_t callback)
{
    event.ResumeCallback = callback;
}
