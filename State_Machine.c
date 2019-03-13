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

#include "State_Machine.h"
#include "U_HW.h"   // include the hardware communication header file
#include <stdlib.h>
#include <stdint.h>

#define NUM_OF_CONCURRENT_STATES 20

// State Machine variables
// These are the function pointer tables. The value in the table must be NULL if it is empty
func_ptr FastProcess[NUM_OF_CONCURRENT_STATES] = {NULL};
func_ptr MsProcess[NUM_OF_CONCURRENT_STATES] = {NULL};
func_ptr SlowProcess[NUM_OF_CONCURRENT_STATES] = {NULL};

uint8_t SlowTickCnt;
uint8_t SlowProcCnt;

extern uint32_t STATUS_FLAG1;

#define SLOWTICKPERIOD 40

// Init_StateMachine - call this function once at the beginning of the program
void Init_StateMachine(void)
{
    SlowTickCnt = SLOWTICKPERIOD;   // Initialize the slow process counter - how many ms for the slow process
    SlowProcCnt = 0;
    Init_Process(FastProcess);
    Init_Process(MsProcess);
    Init_Process(SlowProcess);
  
}
// Init_Process -  this fills the process table with Nulls
void Init_Process(func_ptr *function)
{
    for(int i = 0; i < NUM_OF_CONCURRENT_STATES; i++)
    {
        function[i] = NULL;     // fill the process tables with NULL values
    }
}

// Add_Process
// adds a process to the state machine
int Add_Process(func_ptr *function, func_ptr process)
{
    uint32 fCnt;
    for(fCnt = 0; function[fCnt]; fCnt++)
    {
        if(fCnt >= NUM_OF_CONCURRENT_STATES -1)
        {
            PutStr("\rToo Many Processes\r");
            return -1;
        }
    }
    function[fCnt] = process;
    return 0;
}

void Del_Process(func_ptr *function, func_ptr process)
{
    uint32 fCnt = 0;
    if(function[fCnt] == NULL) return; // if there are no processes running then return

    while (fCnt < NUM_OF_CONCURRENT_STATES -1)  // has to be -1 here!!!
    {
        if(function[fCnt] == process) 
        {
            break;  // when it finds the process in the process array then break out of the while loop 
                    // and shift the rest of the processes up one position - this will only delete the 
                    // first instance of a running process
        } 
        fCnt++;
    }
    while (fCnt < NUM_OF_CONCURRENT_STATES -1)
    {
        function[fCnt] = function[fCnt+1];
        fCnt++;
    }
    function[fCnt] = NULL;      // always end with a NULL in the last place! - because we took something out
}


// Process_Running - returns a 1 (true) if the process is found in the process list otherwise it returns false
unsigned char Process_Running(func_ptr *function, func_ptr process)
{
    uint32 fCnt = 0;
    while(fCnt < NUM_OF_CONCURRENT_STATES -1)
    {
        if (function[fCnt] == process) return 1;
        if (function[fCnt] == NULL) return 0;
        fCnt++;
    }
    return 0;
        
}

void State_Machine(void)
{
    for(uint8_t i = 0; FastProcess[i];(*FastProcess[i++])());    // call all the fast processes!
    
    // Ms Processes caller
    
//    if((STATUS_FLAG1 & (1 << MS_TICK)) != 0)    // if the MS_TICK flag is set.
    if(Get_FLAG(MS_TICK) !=0)
    {
        // STATUS_FLAG1 &= ~(1 << MS_TICK);    // clear the MS_TICK Flag
        Clr_FLAG(MS_TICK);
        

        
        
        for(uint8_t j = 0; MsProcess[j];(*MsProcess[j++])());
        if(-- SlowTickCnt == 0)
        {
            SlowTickCnt = SLOWTICKPERIOD;
            if(SlowProcess[SlowProcCnt] == NULL)
            {
                SlowProcCnt = 0;
                return;
            }
            (*SlowProcess[SlowProcCnt++])();
        }
    }
    
    
}
/* [] END OF FILE */
