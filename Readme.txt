The files included in this directory form a basis for state machine with command line control for the PSOC5 processors

main.c contains a minimimal ammout of code to demonstrate the functionality.

The files CLI.c and its associated header CLI.h constitute the command line interpreter and should be usable with out making any modifications.

State_Machine.c and State_Machine.h implement a state machine with three levels of time control, and multiple states per level. It also should 
also be useable with out any changes.


The other files mentioned here will require application specific modifications.

U_HW.c and U_HW.h are the hardware specific controls. The user can decide to use either the USBUART or the UART_1 interface selectable with a #define. Note that if 
communications component name is changed then the corresponding names in these files must be changed to match it. These files should only require minimal modification 
to suit specific hardware needs. Be very careful modifing anything associated with the communicaitons function. These funcitons are Init_Com(), U_CheckForRx(),
GetChar(), PutChar() and PutStr().

The files that define the application are TestMessages1.h, Cmds.c and Cmds.h and Processes.c and Processes.h

TestMessages.h defines a structure, CMD_Parse_Table with a command list, argument list, help screen information and command function used in the Command Line Interface (CLI).
For every new command that goes into Cmds.c and Cmds.h an entry needs to be added to the CMD_Parse_Table.

There are three CLI commands that are included in CLI.c and CLI.h because it is expected that they will not be modified. These are:
CLI_Test - A simple test command that just echos back the arguments - really usefull for making sure that the CLI is working.
HelpScreen - Prints out the command list, also very useful! especially if other documentation for the application is sparce.
Echo_Cmd - Toggles the command line echo feature. This can be useful if the application is slaved to automated PC control. It makes parsing return messages easier.


Cmds.c and Cmds.h contain the code for the actual commands. Commands can be as simple as a text response, like the Ver_Cmd, or do essentially nothing like the Comment_Cmd. 
Which can be a suprisingly useful command when generating scripts of other commands. Or a command may do something more complex like change the state of the state machine.
Two examples of commands that modifiy the state machine are included. Count_Cmd and Alpha_Cmd. These examples show how processes can be managed for the state machine. 
It is expected that these files will be modified heavily. The commands and processes really form the basis of the specific application

Processes.c and Processes.h contain processes for the state machine the two example processes here are CountProcess and AlphaProcess. CountProcess just increments every
second and prints out the count, AlphaProcess is similar except that it puts out the alphabet which makes it easy to tell when both are running.

