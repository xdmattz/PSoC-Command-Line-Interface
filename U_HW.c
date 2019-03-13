/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <stdint.h>
#include <project.h>
#include "U_HW.h"
#include <stdio.h>



// using the ARM SysTick
#define SYSTICK_INTERRUPT_VECTOR_NUMBER  15u /* Cortex-M3 hard vector */
/* clock and interrupt rates, in Hz */
#define CLOCK_FREQ     BCLK__BUS_CLK__HZ
#define INTERRUPT_FREQ 1000u


CY_ISR(SysTick_ISR)
{
    // set the flag here so we know we got the tick
        Set_FLAG(MS_TICK);
}


// USB Interface stuff
#ifdef USB_COM
#define USBFS_DEVICE 0
#define USBUART_BUFFER_SIZE 64

uint8_t usb_buff[USBUART_BUFFER_SIZE];
int16_t usb_buff_cnt;

char msg[64];

void Init_USB(void)
{
    USBUART_Start(USBFS_DEVICE, USBUART_5V_OPERATION);  // make sure to change this to USBUART_3V_OPERATION if necessary!
    usb_buff_cnt = 0;
}

// need the following functions for USB connectivity
// U_CheckForRx()
// GetChar()
// PutChar()
// PutStr()

bool Check_USB(void)
{
    if(USBUART_IsConfigurationChanged() != 0)   // manage when the USB settings are changed, or if it is disconnected.
    {
        if(USBUART_GetConfiguration() != 0)
        {
            USBUART_CDC_Init();
        }
    }
    
    if(USBUART_GetConfiguration() !=0)
    {
        if(usb_buff_cnt != 0)
        {
            return true;  // still have data in the buffer. 
        }
        if(USBUART_DataIsReady())
        {
            usb_buff_cnt = USBUART_GetAll(usb_buff);

// test buffer for the reverse routine
//            for(usb_buff_cnt = 0; usb_buff_cnt < 11;usb_buff_cnt++)
//            {
//                usb_buff[usb_buff_cnt] = usb_buff_cnt + 48;
//            }
            
            if(usb_buff_cnt == 1)
            {   
                return true;
            }
            else if (usb_buff_cnt > 1)
            {
               // *** To Do !!! ***
               // reverse the data order in the buffer   
                int16 fwd = 0;
                int16 rev = usb_buff_cnt-1;
                uint8_t tmp_val;
                while(fwd < rev)
                {
                    tmp_val = usb_buff[fwd];
                    usb_buff[fwd++] = usb_buff[rev];
                    usb_buff[rev--] = tmp_val;
                }
                return true;   
            }
        }

    }
    return false;
}

uint8_t USB_Buff_GetChar(void)
{
    usb_buff_cnt--;
    return usb_buff[usb_buff_cnt]; // get the character out of the buffer and decrement the index
}

void USB_PutChar(char8 x)
{
    while(USBUART_CDCIsReady() == 0)    // wait for USB to send data
    {
    }
    USBUART_PutChar(x);    
}

void USB_PutString(const char8* str)
{
    while(USBUART_CDCIsReady() == 0)    // wait for USB to send data
    {
    }
    USBUART_PutString(str);
}
#endif

#ifdef UART_COM
void Init_UART(void)
{
    UART_1_ClearRxBuffer();
    UART_1_ClearTxBuffer();
    UART_1_Start();
}
#endif

void Init_HW(void)
{
    Init_Com();     // initialize the serial communications for the CLI
    
    CyIntSetSysVector(SYSTICK_INTERRUPT_VECTOR_NUMBER, SysTick_ISR);    // point the SysTick vector to the ISR in this file
   (void)SysTick_Config(CLOCK_FREQ/INTERRUPT_FREQ);

    Clr_All_FLAG();
    Set_FLAG(ECHO); // except turn the echo on!
      
    // Initialize the LED PIN
}



/*
void PutChar(char ch)
{
    UART_1_PutChar(ch);
}


uint16_t U_CheckForRx(void)
{
    return(UART_1_GetRxBufferSize());

}

char GetChar(void)
{
    return (UART_1_GetChar());
}

void PutStr(char *str)
{
    UART_1_PutString(str);
}
*/




/* [] END OF FILE */
