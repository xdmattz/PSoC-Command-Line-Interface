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

#include "Processes.h"
#include <project.h>
#include <stdio.h>

#include "U_HW.h"

extern uint32_t STATUS_FLAG1;

static uint16_t C_Count;
static uint16_t SecCount;

void InitCountProcess(void)
{
    C_Count = 0;
    SecCount = 1000;
}
void CountProcess(void)
{
    char msg[20];
    if((--SecCount) == 0)
    {
        SecCount = 1000; // reset the counter
        sprintf(msg, "Count = %d\r", C_Count++);
        PutStr(msg);
//        Pin_LED_Write(~(Pin_LED_Read()));    // toggle the LED
    }
}

static uint8 A_Count;
static uint16 S_Count;

void InitAlphaProcess(void)
{
    A_Count = 0;
    S_Count = 1000;
}

void AlphaProcess(void)
{

    char msg[20];
    if((--S_Count) == 0)
    {
        S_Count = 1000u; // reset the counter
        sprintf(msg, "Alpha = %c\r", (A_Count + 'A'));
        PutStr(msg);
        if(A_Count++ > 56) A_Count = 0;
//        Pin_LED_Write(~(Pin_LED_Read()));    // toggle the LED
    }
}


/* [] END OF FILE */
