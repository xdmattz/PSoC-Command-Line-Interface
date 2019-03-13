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

#ifndef TESTMESSAGES_H
#define TESTMESSAGES_H

#include "Cmds.h"
#include "CLI.h"
    
// #define NUMOFCMDS (sizeof(CMD_Parse_Table) / sizeof(CMD_Parse_Table[0]))
#define ARRAY_SIZE(X) (sizeof(X) / sizeof(X[0]))
    
#define NUMOFCMDS ARRAY_SIZE(CMD_Parse_Table)
    
const char BadMsgString[] = "Unrecognized Command!";
const char CmdTooLong[] = "*** Command was too long! ***";
const char Prompt[] = "\r>";

struct CmdDesc {
    const char* name;
    const char* args;
    const char* desc;
    int (*func)(int, char*[]);
};
    
// Parse Table structure
//  "cmd", "arguments", "help screen message", Command Function 
struct CmdDesc const CMD_Parse_Table[] = 
{
    {"help",    0,          "This menu", HelpScreen},
    {"?",       0,          "Same as 'help'", HelpScreen},
    {"test",    0,          "Echo the arguments", CLI_Test},
    {"echo",    "{on/off}", "Toggle the character echo", Echo_Cmd},
    {"ver",     0,          "Software Version", Ver_Cmd},
    {"!",       0,          "Comment delimiter up to 78 characters", Comment_Cmd},
    {"count",   "{on/off}", "Count up every second", Count_Cmd},
    {"alpha",   "{on/off}", "Alphabet up every second", Alpha_Cmd}
};
    
const char HelpDiv[] = "************************";

const char* const HelpHeader[] =
{
    "",
    HelpDiv,
    "* USB CLI *",
    HelpDiv,
    "",
    "%d=decimal, %x=hex, %n=decimal or hex with '0x' prefix",
    "Available Commands:",
    0   // always terminate with NULL
};

#endif // End of TESTMESSAGES_H

/* [] END OF FILE */
