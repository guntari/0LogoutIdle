/* 0LogoutIdle.c,v 0.01 2014/03/01  */
/*
 * Idle time logout tool for Microsoft Windows
 *
 * ----------------------------------------------------------------------------
 *  This program was designed to force logoff of the inactive session under which it runs.
 *  The inactivity period was arbitrarily set to 4 hours (see SLEEP_TIME variable)
 *
 *
 *  TODO:* Accept an argument to set specific time period,
 *         and default to 4 hours if no arguments are present.
 *       #DONE * limit to only one instance.
 *       * create /? argument case to dispaly help/explanation
 *        Binary files has been placed here:
 *        http://kapu.devio.us/0LogoutIdle.exe
 *        \\skyshare01\RootShare\DAT\Public\0LogoutIdle.exe
 *        * add process killer into the loop to kill procexp.exe after 10 min of inactivity
 *
 * ----------------------------------------------------------------------------
 *  0.0.3 Notes:
 *              Issues with mutex if more than one user is using the program.
 *              Get rid of the mutex for limiting execution to one instance in favor
 *              of a moveing the logic into the logon script.
 */

/*
 *
 * *************************
 * **** COMPILING NOTES ****
 * **** ********************
 * windres 0LogoutIdle.rc 0LogoutIdle.o
 * gcc 0LogoutIdle.o -o 0LogoutIdle.exe 0LogoutIdle.c -mwindows
 *                                                    -mwindows
 *                                                    used to flag as gui app and stops console flash
 */

#include <windows.h>             // Needed for Windows Get*()
#include <ShellApi.h>            // Needed for shellexecute()

//----- Defines -------------------------------------------------------------
#define SLEEP_TIME       3000      // Sleep time in milliseconds
    //  1 second = 1000 milliseconds
    //  1 minute = 60000 milliseconds
    //  10 minutes = 600000 milliseconds
    //  1 hour = 3600000 milliseconds
    //  8 hours = 2.88e+7 milliseconds
//----- Functions -----------------------------------------------------------



//===========================================================================
//=  Main program                                                           =
//===========================================================================
void main()
{
  long int      newTicks;        // time value for new ticks
  long int      lastTicks;       // time value for last ticks
  long int      inputTicks;      // time value for current time
  long int      elapsedTicks;    // time value for elapsed time
  LASTINPUTINFO lii;             // Structure for Windows time stuff

  // Set size of lii.cbsize
  lii.cbSize = sizeof(lii);

  // Get the time of last user input
  GetLastInputInfo(&lii);
  lastTicks = lii.dwTime;

  // Loop forever
  while(1)
  {

    // Delay for a sleep time
    Sleep(SLEEP_TIME);

    // Get the time of the most recent (new) user input
    GetLastInputInfo(&lii);
    newTicks = lii.dwTime;

    //myNotes:
    //  GetTickCount()
    //    milliseconds that have elapsed since the system was started.
    //  lii.dwTime
    //    A 'snapshot' of GetTickCount that represents the last user input
    //  1 second = 1000 milliseconds
    //  1 minute = 60000 milliseconds
    //  1 hour = 3600000 milliseconds
    //  8 hours = 2.88e+7 28800000 milliseconds


    // If have a new input since last time around, output the elapsed time
      inputTicks = GetTickCount();
      elapsedTicks = inputTicks - lastTicks;
      //8 Hours
      //if (elapsedTicks >= 28800000)
      //4 Hours
      //if (elapsedTicks >= 14400000)
      if (elapsedTicks >= 14400000)
      {
        // #### SYSTEM CALL METHOD (a console is briefly visible) ####
          //OPEN INTERNET EXPLORER
            //system("\"\"c:\\program files\\internet explorer\\iexplore.exe\" \"www.grc.com\"\"");
          //FORCE LOGOFF
            //system("\"\"c:\\windows\\system32\\shutdown.exe\" /l /f\"");
          //OPEN NOTEPAD
            //system("\"start \"\" /B c:\\windows\\system32\\notepad.exe\"");
          //OPEN NETWORK CONNECTIONS
            //system("\"start \"\" /B ncpa.cpl\"");

        // #### SHELLEXECUTE METHOD (does not flash a console on launch) ####
          //OPEN NOTEPAD
            //ShellExecute(NULL, NULL, "c:\\windows\\system32\\notepad.exe", NULL, NULL, SW_SHOWNORMAL);
          //FORCE LOGOFF
            ShellExecute(NULL, NULL, "c:\\windows\\system32\\shutdown.exe", "/l /f", NULL, SW_SHOWNORMAL);
          //BLUETOOTH FILE TRANSFER
            //ShellExecute(NULL, NULL, "c:\\windows\\system32\\fsquirt.exe", NULL, NULL, SW_SHOWNORMAL);
        //PLAY SOUND (BROKEN FIXME)
            //PlaySound("C:\\Windows\\WinSxS\\amd64_microsoft-windows-shell-sounds_31bf3856ad364e35_6.3.9600.16384_none_07d0dc3d89809d9b", NULL, SND_ASYNC);

        exit(0);
      }

    // Assign lastTicks to newTicks
    lastTicks = newTicks;

  }
}
