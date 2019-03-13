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
#ifndef CLI_H
#define CLI_H
    
#include <stdint.h>    
#define CLI_CMD(X) int X(int argc, char **argv)     // define the CLI command data type
    
#define  UNUSED_ARG(X) (void)(X)
    
void Init_CLI(void);  
void CLI(void);
void ClearInputBufferN(uint8_t N);
int ParseCommand(char *buf);
CLI_CMD(CLI_Test);
CLI_CMD(HelpScreen); 
CLI_CMD(Echo_Cmd);

#endif
/* [] END OF FILE */
