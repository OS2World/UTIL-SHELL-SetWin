/*****************************************************************************
    TITLE:      SetWin.C
    AUTHOR:     Michael Thompson (Graduate Software)
    CIS ID:     76500,2037
    DATE:       02-20-1994
    VERSION:    1.1
    
    One of the major deficiencies in OS/2's windowed command prompts has 
    been the lack of commands to allow the window to be sized and moved 
    from the command line, or batch procedures.  This program overcomes
    this restriction, albeit, in a kludgy sort of way.  
    
    The main kludge in this program is caused by the fact that I could not
    find a way to write a VIO program which has access to the necessary 
    Win functions to perform the desired sizing and moving functions.
    For this, it seems one needs a message queue, and the use of a
    message queue is only valid when the program is linked as PM.  A PM 
    program tells the command processor to minimize itself after the
    program starts, so it is not acceptable as the solution.  The way
    I got around the problem was to have two programs, a VIO program
    which determines the PID of the windowed command prompt, and a PM
    program, which is detached by the VIO program, to perform the Win
    functions to move and size.  If anyone can think of a better way
    to get around this apparent problem, please feel free to do so, or
    e-mail me with your idea.
    
    I release this program into the public domain in the hope that this 
    functionality eventually makes its way into IBM's command processor.
    
    ----  Maybe this will eventually make it onto Hobbes CD-ROM!!  ----
    ----  That would be an honor.                                  ----        

    Other enhancements to consider:
        Selection of windowed session font
        Screen print of windowed session
        
        
    REVISIONS:    
    
    Version 1.0   02-19-94
    
        Initial release.
    
    Version 1.1   02-20-94
    
        Removed SLEEP from SetWin.C.
        Added ability to combine multiple actions.
        Added ACTIVATE DEACTIVATE TOP BOTTOM SLEEP to actions.
        Removed MOVESIZE action.
        Added example usage to Read.ME.
        
*****************************************************************************/

#define INCL_DOS
#define INCL_WIN

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
    {
    CHAR CommandLine[512];
    HSWITCH SwitchHandle;
    SWCNTRL SwitchData;
    PPIB ProcessInfo;
    PTIB ThreadInfo;
    CHAR *Arguments;
    PID ParentPID;
    
    /**********************************************************
        Get the process id for the parent process to this
        program.  If this program is run from the command
        line, then the parent PID will be that of CMD.EXE.
    **********************************************************/
        DosGetInfoBlocks(&ThreadInfo,&ProcessInfo);
        ParentPID=ProcessInfo->pib_ulppid;

    /**********************************************************
        Get the pointer to the command line and skip the 
        executable name at the start.  The arguments to
        this program will be passed "as is" to the SetWinPM
        program.
    **********************************************************/
        Arguments=ProcessInfo->pib_pchcmd;
        Arguments+=strlen(Arguments)+1;
        while(*Arguments==' ')
            Arguments++;

    /**********************************************************
        Display help if no options were specified.
    **********************************************************/
        if(*Arguments==0) {
            printf("\n");
            printf("Syntax:  SETWIN action [params]\n\n");
            printf("Valid Actions:\n\n");
            printf("    MINIMIZE\n");
            printf("    MAXIMIZE\n");
            printf("    RESTORE\n");
            printf("    HIDE\n");
            printf("    SHOW\n");
            printf("    MOVE x y\n");
            printf("    SIZE w h\n");
            printf("    FLASHON\n");
            printf("    FLASHOFF\n");
            printf("    ACTIVATE\n");
            printf("    DEACTIVATE\n");
            printf("    TOP\n");
            printf("    BOTTOM\n");
            printf("    SLEEP ms\n");
            printf("\n");
            return 0;
        }
        
    /**********************************************************
        Locate the parent's PID in the switch list.  This
        program will terminate if there is no entry in the 
        switch list for the parent process.
    **********************************************************/
        SwitchHandle=WinQuerySwitchHandle(NULLHANDLE,ParentPID);
        if(SwitchHandle==NULLHANDLE) {
            printf("No switch list entry for the parent process.\n");
            return 0;
        }
        
    /**********************************************************
        Determine the window handle associated with the 
        parent process.  This program will terminate if 
        there is no window associated with the parent 
        process.
    **********************************************************/
        WinQuerySwitchEntry(SwitchHandle,&SwitchData);
        if(SwitchData.hwnd==NULLHANDLE) {
            printf("No window associated with the parent process.\n");
            return 0;
        }
        
    /**********************************************************
        Build the command line for the SetWinPM program.
        The first parameter passed is the window handle.
        The remaining parameters are the arguments passed
        to this program.  The SetWinPM program is detached
        so that window size changes don't get reset on
        return from the PM program.  The "2>NUL" causes
        stderr to be rerouted, which keeps the PID number
        from being displayed for the detached process.
    **********************************************************/
        sprintf(CommandLine,"DETACH SetWinPM %p %s 2>NUL",SwitchData.hwnd,Arguments);
        system(CommandLine);
        return 0;
    }

