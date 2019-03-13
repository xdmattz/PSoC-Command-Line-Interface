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

#ifndef CMDS_H
#define CMDS_H
    
#include <stdint.h>
    
#define CLI_CMD(X) int X(int argc, char **argv)     // define the CLI command data type
    
#define  UNUSED_ARG(X) (void)(X)
    
// All the commands that the CLI will handle
    
// CLI_CMD(Echo_Cmd);
CLI_CMD(Ver_Cmd);
CLI_CMD(Comment_Cmd);
CLI_CMD(Count_Cmd);
CLI_CMD(Alpha_Cmd);

#endif
/* [] END OF FILE */
