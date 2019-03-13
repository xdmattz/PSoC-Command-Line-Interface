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

// commands consist of a key word followed by numbers or other words separated by spaces, and ending with a CR (0x0d)
// commands are processed upon receipt of the CR character.
// the first line word (words are separated by white space) is assumed to be the key word. It is compared against the 
// key word table and the appropriate command function is called with the argc and argv variables containing values indicating
// the number of additional words and a pointer to their locations. (with each white space being replaced by a 0 to properly terminate the strings)

// parse the command line
//
#include <CLI.h>

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "U_HW.h"
#include "TestMessages.h"

#define NUM_OF_ARGS 30  // maximum number of arguments
#define IN_BUFF_LEN 80

char InBuff[IN_BUFF_LEN];
uint8_t InBuffCnt;  // line buffer position

static bool cliEcho = true;
static bool cliOn = true;



static inline void SetCliEcho(bool on) {
    cliEcho = on;
}

static inline bool GetCliEcho() {
    return cliEcho;
}

void Init_CLI(void)
{
    ClearInputBufferN(IN_BUFF_LEN);
    // set the ECHO flag 
    cliEcho = true;
    // HelpScreen(0, NULL);     
}

void CLI(void)
{
    if(U_CheckForRx())
    {
        char data = GetChar();
        if(cliEcho) PutChar(data);      // if in ECHO mode then echo the character
        switch (data)
        {
            case '\n'   : break; // newline - ignore
            case '\r'   : // CR save the count and return
                ParseCommand(InBuff);
                ClearInputBufferN(InBuffCnt);
                break;
            case 0x7f   :   // alt back space
            case 0x08   :   // back space - back up one space 
                if(InBuffCnt > 0)
                {
                    InBuffCnt--;  
                    InBuff[InBuffCnt] = 0;  // back fill with zeros
                    break;
                }
            default     :
                if(InBuffCnt >= IN_BUFF_LEN)    // Message is too long! 
                {
                    PutStr(CmdTooLong);
                    ClearInputBufferN(InBuffCnt);
                }
                InBuff[InBuffCnt] = data;
                InBuffCnt++;
                break;
        }
    }
}

void ClearInputBufferN(uint8_t N)
{
    
    for(uint8_t i = 0; i < N; i++)
    {
        InBuff[i] = 0;
    }
    InBuffCnt = 0;
}

static inline char *getWord(char *buf)
{
    static char *ptr = NULL;    // static variable  is rememberd from call to call
    char *start, *scan;
    char term = ' ';
    
    if(buf != NULL)     // takes care of the command (key) word
    {
        ptr = buf;
    }
    while (((*ptr == ' ') || (*ptr == '\t')) && (*ptr != '\0')) // skip through spaces and tabs while not hitting \0
    {
        ptr++;
    }
    if(*ptr == '\0')    // if we get a \0 then done
    {
        return NULL;
    }
    if((*ptr == '"') || (*ptr == '\''))     // parse stuff between quotes "" or ''
    {
        term = *ptr;
        ptr++;
    }
    start = ptr;
    while (*ptr != '\0')        
    {
        if(*ptr == '\\')
        {
            for(scan = ptr; *scan != '\0'; scan++)
            {
                *scan = *(scan+1);
            }
            ptr++;
            continue;
        }
        if((*ptr == term) || ((term == ' ') && (*ptr == '\t')))
        {
            *ptr = '\0';        // put the null termination in the argument list (this is how the argv[x] are separated)
            ptr++;
            return start;
        }
        ptr++;
    }
    if (ptr == start)       // there were no arguments
    {
        return NULL;
    }
    return start;
}

int ParseCommand(char *buf)
{
	int argc;
	char *argv[NUM_OF_ARGS];
	char *w;
	
	if(buf[0] == 0)
	{
        PutStr(Prompt);
		return 0;	// no command or arguments
	}

	argc = 0;
	w = getWord(buf);
	while((argc < NUM_OF_ARGS) && (w != NULL))
	{
        argv[argc++] = w;
		w = getWord(NULL);
	}

	const char*  PstrPtr;
	
	// compare the first word with the CmdName Key word in the CMD Parse Table
	for(uint8_t i = 0; i < NUMOFCMDS; i++)
	{
		PstrPtr = CMD_Parse_Table[i].name;
		if(strcmp(argv[0], PstrPtr) == 0)
		{
			int rval = CMD_Parse_Table[i].func(argc, argv);	// call the command function

            PutStr(Prompt);
            return rval;
		}
	}
	PutStr(BadMsgString);
    PutStr(Prompt);
	return -1;
}

CLI_CMD(CLI_Test)
{
    PutChar('\r');
    for(uint8_t i = 0; i < argc; i++)
    {
        PutStr(argv[i]);
    }
    return 0;
}

CLI_CMD(HelpScreen)
{
    UNUSED_ARG(argc);UNUSED_ARG(argv);
    
    const char * const *pc = HelpHeader;
    for (; *pc; pc++)
    {
        PutStr(*pc);
        PutChar('\r');
    }
    const struct CmdDesc *pcd = CMD_Parse_Table;
    for(uint8_t i = 0;i < NUMOFCMDS; pcd++, i++)
    {
//        uint16_t clen = strlen(pcd->name);
//        maybe add the "tab" spacing so the help message looks nice...        
        PutStr(pcd->name);
        if(pcd->args) 
        {
            PutChar(' ');
            PutStr(pcd->args);
        }
        if(pcd->desc)
        {
            PutStr(" - ");
            PutStr(pcd->desc);
        }
        PutChar('\r');
    }
    return 0;
 }

CLI_CMD(Echo_Cmd)
{
        if (argc < 2)
    {
        PutStr("Echo is ");
        PutStr(GetCliEcho() ? "ON" : "OFF");
        PutChar('\r');
    }
    else {
        if(strcmp(argv[1], "off") == 0) SetCliEcho(false);
        else if(strcmp(argv[1], "on") == 0) SetCliEcho(true);
        else 
        {            // error message
            PutStr("Usage echo 'on'/'off'");
        }
    }
    return 0;
}
/* [] END OF FILE */
