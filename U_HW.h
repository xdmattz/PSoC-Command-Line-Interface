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
#ifndef U_HW_H
#define U_HW_H

#include <project.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
    
// Bit definitions for STATUS_FLAG1     
#define MS_TICK 0   //
#define ECHO    1
#define SOMETHING 2
    
     
//     
#define _BV(X) (1 << X)
    

    
// Bitbanding stuff Cortex M3 only!
#define BITBAND_SRAM_REF   0x20000000
#define BITBAND_SRAM_BASE  0x22000000
#define BITBAND_SRAM(a,b) ((BITBAND_SRAM_BASE + (a-BITBAND_SRAM_REF)*32 + (b*4)))  // Convert SRAM address
#define BITBAND_PERI_REF   0x40000000
#define BITBAND_PERI_BASE  0x42000000
#define BITBAND_PERI(a,b) ((BITBAND_PERI_BASE + (a-BITBAND_PERI_REF)*32 + (b*4)))  // Convert PERI address
 
//
//  hardcoded status flag memory location. should probably try to figure out how to put this at the very top of memory and then
// push the stack pointer down a few locations that the status flag variables are not sitting in the middle of the memory space.
//  
//
// I am thinking there should be some way to put the status flag at the very top of memory and then move the 
// stack pointer down one or two addresses so the status flag will never get written over by the rest of the code
// and I wont have to modify the linker file.
//  
    

#define StackTop 0x20007fec   
// #define STATUS_F1 0x20000008    // HARDCODED STATUS FLAG ADDRESS!
#define STATUS_F1  StackTop   // HARDCODED STATUS FLAG ADDRESS!    
#define Get_FLAG(a) *((volatile uint32 *) (BITBAND_SRAM(STATUS_F1,a)))
#define Set_FLAG(a) Get_FLAG(a) = 1
#define Clr_FLAG(a) Get_FLAG(a) = 0
// initialize all the flag bits to zero
#define Clr_All_FLAG() *(volatile uint32 *) STATUS_F1 = (uint32)0u

#define USB_COM    

#ifdef USB_COM    
    // These macros refer to the USB_UART - if you change the USBUART name you must change the name in these functions!
    #define Init_Com() Init_USB()
    #define U_CheckForRx() Check_USB()
    #define GetChar() USB_Buff_GetChar()
    #define PutChar(X) USB_PutChar(X)    
    #define PutStr(X) USB_PutString(X)
    
    // USBUART Functions
    void Init_USB(void);    
    bool Check_USB(void);
    uint8_t USB_Buff_GetChar(void);
    void USB_PutChar(char8 x);
    void USB_PutString(const char8* str);
   
#endif

// #define UART_COM
#ifdef UART_COM
    // These macros refer to the UART - if you change the UART name you must change the name here! 
    #define Init_Com() Init_UART()
    #define U_CheckForRx() UART_1_GetRxBufferSize()
    #define GetChar() UART_1_GetChar()
    #define PutChar(X) UART_1_PutChar(X)
    #define PutStr(X) UART_1_PutString(X)
    
    // UART Functions
    void Init_UART(void);
    
#endif    

// replaced the functions below with the macros above
/*
void PutChar(char ch);
uint16_t U_CheckForRx(void);
char GetChar(void);
void PutStr(char *str);
*/
    
// Other Hardware specific functions

void Init_HW(void);    


#endif


/* [] END OF FILE */
