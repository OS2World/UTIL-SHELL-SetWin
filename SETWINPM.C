/*****************************************************************************
    TITLE:      SetWinPM.C
    AUTHOR:     Michael Thompson (Graduate Software)
    CIS ID:     76500,2037
    DATE:       02-19-1994
    VERSION:    1.0
    
    Refer to SetWin.C for information about this program.
*****************************************************************************/

#define INCL_DOS
#define INCL_WIN

#include <os2.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[])
    {
    HAB AnchorBlock;
    HMQ MessageQueue;
    HWND Window;
    CHAR Buffer[256];
    CHAR *Action;
    SWP Position;
    LONG i,X,Y,CX,CY;
    ULONG Delay;

    /**********************************************************
        Create the anchor block and message queue.
    **********************************************************/
        AnchorBlock=WinInitialize(0);
        MessageQueue=WinCreateMsgQueue(AnchorBlock,64);
        
    /**********************************************************
        Display an error if the program is started without
        the window handle and action parameters.
    **********************************************************/
        if(argc<3) {
            WinMessageBox(HWND_DESKTOP,HWND_DESKTOP,
                          "This program is meant to be called by SETWIN.EXE.  "
                          "Run SETWIN with no parameters for a list of options.",
                          "SetWinPM Error",0,MB_CANCEL);
            return 0;
        }
        
    /**********************************************************
        Get the window handle from the argument list.
        Ignore requests with a NULL window handle.
    **********************************************************/
        sscanf(argv[1],"%p",&Window);
        if(Window==NULLHANDLE)
            return 0;
            
    /**********************************************************
        Determine what actions are to be performed and then
        perform them.
    **********************************************************/
        for(i=2;i<argc;i++) {
            Action=argv[i];
    
            if(stricmp(Action,"MINIMIZE")==0)
                WinSetWindowPos(Window,NULLHANDLE,0,0,0,0,SWP_MINIMIZE);
                
            else if(stricmp(Action,"MAXIMIZE")==0)
                WinSetWindowPos(Window,NULLHANDLE,0,0,0,0,SWP_MAXIMIZE);
                
            else if(stricmp(Action,"RESTORE")==0)
                WinSetWindowPos(Window,NULLHANDLE,0,0,0,0,SWP_RESTORE);
    
            else if(stricmp(Action,"MOVE")==0) {
                if(argc<i+3) {
                    WinMessageBox(HWND_DESKTOP,HWND_DESKTOP,
                                  "Supply horizontal and vertical positions.",
                                  "SetWinPM Error",0,MB_CANCEL);
                    return 0;
                }
                WinQueryWindowPos(Window,&Position);
                sscanf(argv[++i],"%d",&X);
                sscanf(argv[++i],"%d",&Y);
                WinSetWindowPos(Window,NULLHANDLE,X,Y,Position.cx,Position.cy,SWP_MOVE);
            } 
    
            else if(stricmp(Action,"SIZE")==0) {
                if(argc<i+3) {
                    WinMessageBox(HWND_DESKTOP,HWND_DESKTOP,
                                  "Supply horizontal and vertical sizes.",
                                  "SetWinPM Error",0,MB_CANCEL);
                    return 0;
                }
                sscanf(argv[++i],"%d",&CX);
                sscanf(argv[++i],"%d",&CY);
                WinSetWindowPos(Window,NULLHANDLE,0,0,CX,CY,SWP_SIZE);
            } 
    
            else if(stricmp(Action,"HIDE")==0)
                WinSetWindowPos(Window,NULLHANDLE,0,0,0,0,SWP_HIDE);
    
            else if(stricmp(Action,"SHOW")==0)
                WinSetWindowPos(Window,NULLHANDLE,0,0,0,0,SWP_SHOW);
    
            else if(stricmp(Action,"FLASHON")==0)
                WinFlashWindow(Window,TRUE);
    
            else if(stricmp(Action,"FLASHOFF")==0)
                WinFlashWindow(Window,FALSE);

            else if(stricmp(Action,"ACTIVATE")==0)
                WinSetWindowPos(Window,NULLHANDLE,0,0,0,0,SWP_ACTIVATE);

            else if(stricmp(Action,"DEACTIVATE")==0)
                WinSetWindowPos(Window,NULLHANDLE,0,0,0,0,SWP_DEACTIVATE);

            else if(stricmp(Action,"TOP")==0)
                WinSetWindowPos(Window,HWND_TOP,0,0,0,0,SWP_ZORDER);

            else if(stricmp(Action,"BOTTOM")==0)
                WinSetWindowPos(Window,HWND_BOTTOM,0,0,0,0,SWP_ZORDER);

            else if(stricmp(Action,"SLEEP")==0) {
                if(argc<i+2) {
                    WinMessageBox(HWND_DESKTOP,HWND_DESKTOP,
                                  "Supply delay in milliseconds.",
                                  "SetWinPM Error",0,MB_CANCEL);
                    return 0;
                }
                sscanf(argv[++i],"%u",&Delay);
                DosSleep(Delay);
            }

            else {
                sprintf(Buffer,"Invalid action [%s] specified.",Action);
                WinMessageBox(HWND_DESKTOP,HWND_DESKTOP,Buffer,"SetWinPM Error",0,MB_CANCEL);
                return 0;
            }
        }
        
    /**********************************************************
        Destroy the message queue and anchor block.
    **********************************************************/
        WinDestroyMsgQueue(MessageQueue);
        WinTerminate(AnchorBlock);
        return 0;
    }

