
    One of the major deficiencies in OS/2's windowed command prompts has 
    been the lack of commands to allow the window to be sized and moved 
    from the command line, or batch procedures.  SetWin and SetWinPM
    overcome this restriction.  Please refer to the inline documentation
    for more information.
    
    I release this program into the public domain in the hope that this 
    functionality eventually makes its way into IBM's command processor.
    
    ----  Maybe this will eventually make it onto Hobbes CD-ROM!!  ----
    ----  That would be an honor.                                  ----        


    Example usage:
    
        I use the following .CMD file when I startup an OS/2 windowed
        command prompt to put the window in 40 line mode.  I start the
        window minimized (setting on the session page of the notebook)
        to keep it from displaying in 25 line mode first.  The .CMD file
        takes care of resizing, repositioning, and finally activating 
        the window.  You can specify /K xxxxxxx.CMD in the parameters
        field on the program page of the notebook to start your batch
        file.

    Batch file contents:
    
    -----------------------------------------------------------------------
        @echo off
        prompt [37;44;1m$P$G[0;1m
        mode co80,40
        setwin hide restore move 200 50 size 9999 9999 top show activate
    -----------------------------------------------------------------------
    
    The window is started minimized, so the mode change is done without
    any screen update.  The window is then hidden.  In order for the MOVE
    and SIZE commands to work on the restored window, the window needs
    to be restored before they are called.  If the window isn't first 
    hidden, then the screen may flash during all the updates.  The window
    is then made the topmost window before being made visible and then
    activated (given the focus).

    Note:  Using MOVE and SIZE when the window is minimized moves and
           sizes the icon.  You can also MOVE and SIZE the maximized
           window.
           
    Note:  Attempting to size the window beyond its maximum allowed size
           will cause the maximum size to be applied.  This is why I use
           the 9999 9999 for the SIZE command in the example above.
           
    Note:  All positions and sizes are in screen pixels.  My values are
           for a 1024x768 mode display.

    Michael Thompson
    Graduate Software
    76500,2037
    
    02-20-1994
    
