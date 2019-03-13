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

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
    
typedef void (* func_ptr)(void);

void Init_Process(func_ptr *function);
int Add_Process(func_ptr *function, func_ptr process);
void Del_Process(func_ptr *function, func_ptr process);
unsigned char Process_Running(func_ptr *function, func_ptr process);

// state machine

void Init_StateMachine(void);
void State_Machine(void);
    
#endif

/* [] END OF FILE */
