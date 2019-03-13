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

#include <project.h>

#include "Cmds.h"
#include "CLI.h"
#include "U_HW.h"
#include "State_Machine.h"
#include "Processes.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern func_ptr FastProcess[];
extern func_ptr MsProcess[];
extern func_ptr SlowProcess[];


CLI_CMD(Ver_Cmd)
{
    UNUSED_ARG(argc);UNUSED_ARG(argv);
    
    PutStr("\r** PSOC-5 CLI Test **\r");
	PutStr("  Version 1.00\r");
	PutStr(__DATE__" "__TIME__"\r");
	return 0;
}

CLI_CMD(Comment_Cmd)
{
    UNUSED_ARG(argc);UNUSED_ARG(argv);
    
    return 0;
}

CLI_CMD(Count_Cmd)
{
    if(argc < 2)
    {
        PutStr("usage: count {on/off}\r");
        return 0;
    }
   if(strcmp(argv[1], "on") == 0)
    {
        if(Process_Running(MsProcess, CountProcess))
        {
            PutStr("Count already running!\r");
        } else {
            Add_Process(MsProcess, &(CountProcess));
            InitCountProcess();
            PutStr("Count is ON!\r");
        }
    }
    if(strcmp(argv[1], "off") == 0)
    {
        Del_Process(MsProcess, &(CountProcess));
        PutStr("Count is OFF!\r");

    }
    return 0;
}

CLI_CMD(Alpha_Cmd)
{
        if(argc < 2)
    {
        PutStr("usage: alpha {on/off}\r");
        return 0;
    }
   if(strcmp(argv[1], "on") == 0)
    {
        if(Process_Running(MsProcess, AlphaProcess))
        {
            PutStr("Alpha already running!\r");
        } else {
            Add_Process(MsProcess, &(AlphaProcess));
            InitAlphaProcess();
            PutStr("Alpha is ON!\r");
        }
    }
    if(strcmp(argv[1], "off") == 0)
    {
        Del_Process(MsProcess, &(AlphaProcess));
        PutStr("Alpha is OFF!\r");
    }
    return 0;
}




/* [] END OF FILE */
