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
#include "project.h"

#include "U_HW.h"
#include "CLI.h"
#include "State_Machine.h"

int main(void)
{
    Init_HW();
    Init_StateMachine();
    CyGlobalIntEnable; /* Enable global interrupts. */
    Init_CLI();

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        CLI();
        State_Machine();
    }
}

/* [] END OF FILE */
