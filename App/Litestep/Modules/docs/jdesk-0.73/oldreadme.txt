===================================================
===================================================
== jDesk.dll - an advanced desktop for LiteStep ===
===================================================
===================================================
====== Written by: ================================
================== Chris Rempel (jugg) ============
===================================================
================== http://jugg.logicpd.com/ =======
===================================================
===================================================
= Version: 0.70 = Release Date: 00.09.04 ==========
===================================================
===================================================

-=ToC=-
I. Introduction
II. Installation
III. Information
 A} Commands
 B} Changes
IV. Tips & Tricks
V. Disclaimer


=====================
== I. Introduction ==
=====================
===================================================

Welcome, and thank you for deciding to try out this
enhanced Desktop replacement module for Win32
Shells that support the LiteStep module standard.
jDesk features improved performance, stability, and
customization over the Desktop that comes with
LiteStep. For example, jDesk can execute programs,
LiteStep action (bang) commands, and combinations
of any number of commands from a single mouse
click, or mouse/keyboard combination. Also, jDesk
can set your intial Work Area (amount of screen
realestate that a maximized window covers) as well
as changing the Work Area on the fly.


=====================
== II. Istallation ==
=====================
===================================================

Extract "jDesk.dll" to your LiteStep directory
(c:\litestep\). Open up your step.rc (LiteStep
configuration file) and find the section where all
of your "LoadModule" lines are located. Remove or
comment out (using a semicolon) the "LoadModule"
line that contains "desktop.dll". Now, add a new
line that looks like this:

LoadModule c:\litestep\jdesk.dll

Of course, adjust the path as necessary. Save your
step.rc and issue the LiteStep Recycle command
(!Recycle).

NOTE 1: You MUST have a CVS (Dev) build dated
99.08.25 or later, even LiteStep 0.24.5 is NOT
recent enough, as jDesk 0.50+ requires new
functionality in the lsapi.dll. You can get this
from http://lsdev.litestep.net/

NOTE 2: jDesk does not contain a TaskBar or System
Tray. You will need to utilize a specific LiteStep
Module for those features. Please read the section
"IV. Tips & Tricks" for more information.


======================
== III. Information ==
======================
===================================================
= A} Commands =
===============

jDeskWorkArea "0,0,0,0"
  - Sets the initial Work Area (amount of screen
    realestate that a maximized window covers) of
    your Desktop.

  - Accepts negative and positive decimal values,
    which combined create the WorkArea "box".
    Opposite sides must have a difference greater
    then 200. The order of values are:
        "<left>,<right>,<top>,<bottom>"

    *Note: If ".none" is specified for any of the
    values, then that value is unchanged from its
    previous state.

  - Defaults to: "0,0,0,0"
    *Note: This sets the WorkArea to full screen.


jDeskDesktopFolder ""
  - If used and set to a valid directory, it will
    enable drag and drop of files onto the jDesk
    desktop area. Any file dropped on the desktop
    will be automatically copied into the folder
    specified. If the file exists, you will be
    prompted to overwrite. You can not move files,
    or create shortcuts. Currently dragging folders
    do not work.

  - Defaults to: No default. If not specified,
                 Drag&Drop is not enabled.

jDeskDoubleClickTime "750"
  - Sets the time jDesk waits to see if a double
    click happens after the first click is
    received.

  - Defaults to: System DoubleClick time.
    *Note: It is suggested to not set this value.


jDeskClearWorkAreaOnExit
  - If set, Work Area will be restored to full
    screen when jDesk is unloaded.
  - boolean value: true if set, otherwise false.


jDeskRecycleOnRezChange
  - If set, jDesk requests are recycle of the shell
    after a Screen resolution change.
  - boolean value: true if set, otherwise false.


jDeskDisableMButton1
  - If set, all jDesk Mouse Button 1 functionality
    is disabled.
  - boolean value: true if set, otherwise false.


jDeskDisableMButton2
  - If set, all jDesk Mouse Button 2 functionality
    is disabled.
  - boolean value: true if set, otherwise false.


jDeskDisableMButton3
  - If set, all jDesk Mouse Button 3 functionality
    is disabled.
  - boolean value: true if set, otherwise false.


jDeskDisableMButtonX1
  - If set, all jDesk Mouse Button X1 functionality
    is disabled.
  - boolean value: true if set, otherwise false.


jDeskDisableMButtonX2
  - If set, all jDesk Mouse Button X2 functionality
    is disabled.
  - boolean value: true if set, otherwise false.


jDeskDisableMWheelScroll
  - If set, all jDesk Mouse Wheel Scroll
    functionality is disabled.
  - boolean value: true if set, otherwise false.


jDeskDisableDoubleClick
  - If set, all jDesk ignores Double Click actions and
    immediately executes the up action command instead
    of waiting to see if a double click is being
    executed.
  - boolean value: true if set, otherwise false.


*jDeskMButton1
  - parameters:
    [<modkey>;<down-cmd>;<up-cmd>;<dblclick-cmd>]

    <modkey> can be one of the following
      SHIFT
      CTRL
      CTRL+SHIFT

    <down-cmd>
    <up-cmd>
    <dblclick-cmd>
      can be any !Bang command or executable that
      is to be executed.

  - Multiple settings of this definition are
    allowed, but only one definition using the same
    modkey is allowed.

  - If no definitions are specified, Button is
    disabled.


*jDeskMButton2
  - parameters:
    [<modkey>;<down-cmd>;<up-cmd>;<dblclick-cmd>]

    <modkey> can be one of the following
      SHIFT
      CTRL
      CTRL+SHIFT

    <down-cmd>
    <up-cmd>
    <dblclick-cmd>
      can be any !Bang command or executable that
      is to be executed.

  - Multiple settings of this definition are
    allowed, but only one definition using the same
    modkey is allowed.

  - If no definitions are specified, Button is
    disabled.


*jDeskMButton3
  - parameters:
    [<modkey>;<down-cmd>;<up-cmd>;<dblclick-cmd>]

    <modkey> can be one of the following
      SHIFT
      CTRL
      CTRL+SHIFT

    <down-cmd>
    <up-cmd>
    <dblclick-cmd>
      can be any !Bang command or executable that
      is to be executed.

  - Multiple settings of this definition are
    allowed, but only one definition using the same
    modkey is allowed.

  - If no definitions are specified, Button is
    disabled.


*jDeskMButtonX1
  - parameters:
    [<modkey>;<down-cmd>;<up-cmd>;<dblclick-cmd>]

    <modkey> can be one of the following
      SHIFT
      CTRL
      CTRL+SHIFT

    <down-cmd>
    <up-cmd>
    <dblclick-cmd>
      can be any !Bang command or executable that
      is to be executed.

  - Multiple settings of this definition are
    allowed, but only one definition using the same
    modkey is allowed.

  - If no definitions are specified, Button is
    disabled.


*jDeskMButtonX2
  - parameters:
    [<modkey>;<down-cmd>;<up-cmd>;<dblclick-cmd>]

    <modkey> can be one of the following
      SHIFT
      CTRL
      CTRL+SHIFT

    <down-cmd>
    <up-cmd>
    <dblclick-cmd>
      can be any !Bang command or executable that
      is to be executed.

  - Multiple settings of this definition are
    allowed, but only one definition using the same
    modkey is allowed.

  - If no definitions are specified, Button is
    disabled.


*jDeskMWheelScroll
  - parameters:
    [<modkey>;<down-cmd>;<up-cmd>]

    <modkey> can be one of the following
      SHIFT
      CTRL
      CTRL+SHIFT

    <down-cmd>
    <up-cmd>
      can be any !Bang command or executable that
      is to be executed.

  - Multiple settings of this definition are
    allowed, but only one definition using the same
    modkey is allowed.

  - If no definitions are specified, Wheel Scroll
    is disabled.


!jDeskSetWorkArea "0,0,0,0"
  - Sets the WorkArea. Same as "jDeskWorkArea"
    setting, accept in a !Bang command version.

  - Accepts negative and positive decimal values,
    which combined create the WorkArea "box".
    Opposite sides must have a difference greater
    then 200. The order of values are:
        "<left>,<right>,<top>,<bottom>"

    *Note: If ".none" is specified for any of the
    values, then that value is unchanged from its
    previous state.

  - If no parameters are specified, the WorkArea is
    set to full screen.


!jDeskResetWorkArea
  - Resets the WorkArea to the initial values
    specified by "jDeskWorkArea".



===================================================
= B} Changes =
==============

- 0.70 -
--------

  + Complete code/settings rewrite.
  + Added ability to leave any of the work area
    dimensions unaffected when setting the work
    area by specifying ".none" in its place.

  ! Fixed multiple issues dealing with focus/zorder

  ^ Basically you should start with a clean setup
    and build your settings from scratch, just
    about everything has changed. Enjoy.


- 0.61 -
--------

  ! Fixed background refresh problems.
  ! Fixed desktop window from not resizing when the
    screen resolution is changed.
  ! Fixed WorkArea from not updating when the
    screen rosolution is changed.

- 0.60 -
--------

  + Added jDeskDesktopFolder (drag & drop) command.

  - Removed "jDeskSwapMButtons" (too much extra
    code, just change your commands instead).

  * Changed the mouse button configuration. Now
    both Down and Up commands are on the same line
    seperated by brackets [].

  * Changed the way the desktop background/ refresh
    is handled. Using WS_EX_TRANSPARENT now.

- 0.51 -
--------
  ! Fixed "jDeskSwapMButtons" bug that made it not
    work.

- 0.50 -
--------
  + Added the ability to assign functionality to
    _both_ mouse UP and mouse DOWN events.

  + Added the ability to swap First and Second
    mouse buttons

  + Added ability to disable the Third (middle)
    mouse button.

  - Removed obsolete commands

  * Changed the way programs/commands are executed.
    It now conforms to the LiteStep standards.

  * Improved performance of the !jDeskSetWorkArea
    and !jDeskResetWorkArea actions.

  ! Fixed bug when changing resolutions the DeskTop
    window did not resize to the new screen size.

  ! Fixed bug that messed up the WorkArea when
    putting quotation marks around the
    !jDeskSetWorkArea parameters.

  ! Fixed bug when not using the "jDeskWorkArea"
    command, and then using the combination of
    "!jDeskWorkArea" and "!jDeskResetWorkArea"
    action commands, it would set the WorkArea to
    the hardcoded settings.

- 0.40 -
--------
  + Added the ability to specify executing events
    on mouse DOWN or mouse UP.

  + Added ability to execute programs, folders
    and the like, and not just LS actions (bangs).

  + Added ability to allow parameters to be passed
    to a program or LS Action command.

  + Added ability to execute different events
    depending if the SHIFT or CTRL key is held down.

  + Added !jDeskSetWorkArea and !jDeskResetWorkArea.

  * Changed all of the step.rc command format.

  * Several other misc changes/ fixes

- 0.30 -
--------
  + Initial release. Supports running single LS
    action commands for each mouse button, and
    defining application Work Area (DesktopArea).


=====================
= IV. Tips & Tricks =
=====================
===================================================

---------------------------------------------------
- To get the Wheel Scroll to work, you need to
click on the desktop to activate it first. To be
able to do this, set the following (or similar):
*jDeskMButton3 [.none;!none;!none;!none]
Then after you click on the Desktop with Button3,
you will be able to execute your wheel scroll
commands.

---------------------------------------------------
-Sample commands:
*jDeskMButton1 [.none;!TasksHide;!TasksMove !TasksShow;!none]
*jDeskMButton2 [.none;!TasksHide;!Popup;!none]
*jDeskMButton3 [CTRL;!none;!about;!about detailed]

---------------------------------------------------
- If you want to have a System Tray, download
"systray.dll", created by Maduin, from
http://maduin.dasoft.org/  This is a fully featured
skinnable System Tray that can be placed anywhere
on your Desktop. Other alternatives are grdTray
and the systray2.dll bundled with recent LiteStep
builds.

---------------------------------------------------
- If you want a Task Manager to have access to your
currently running applications you can use
"tasks.dll" available from
http://jugg.logicpd.com/software/

Or you can get "traytasks.dll", created by Sergey
Trofimov (requires "systray.dll" to run with jDesk)
TrayTasks is available from:
http://www.tv4studios.com/st/litestep/modules.html

There are other alternatives including several
Task Managers for the Wharf and Popups.

---------------------------------------------------
- If you want to have AutoRun capabilities you need
to get "autorun.dll", created by Visigoth, from
http://visigoth.litestep.com/

---------------------------------------------------
- If you are having trouble with "application bars"
showing up along the bottom of your screen when you
minimize an application, this is because you need
to get a Task Manager that supports hiding
Minimized Application Bars. If you are running
"tasks.dll" you can hide those bars by adding the
command "TasksHideMinAppBar".

---------------------------------------------------
- If you are running Windows NT, and you change the
Left side of the WorkArea from zero "0" to any
other value, it may mess up the rest of the
settings. This is not a jDesk specific bug. All
modules that use SystemParametersInfo/
SPI_SETWORKAREA functionality has this problem. A
solution is being looked into.

---------------------------------------------------
- If you are using the Wharf with jDesk, and you
do NOT want the Wharf to resize the WorkArea when
it docks to the side of the screen add the command
"SetDesktopArea" to your "step.rc" file.


=================
= V. Disclaimer =
=================
===================================================

Copyright (C) 1999, Chris Rempel

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT  WARRANTY
OF ANY KIND, EXPRESS OR  IMPLIED, INCLUDING BUT NOT
LIMITED  TO  THE   WARRANTIES  OF  MERCHANTABILITY,
FITNESS  FOR   A   PARTICULAR   PURPOSE   AND  NON-
INFRINGEMENT.  IN  NO  EVENT  SHALL THE  AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,  DAMAGES
OR  OTHER  LIABILITY,   WHETHER  IN  AN  ACTION  OF
CONTRACT,  TORT OR OTHERWISE,  ARISING FROM, OUT OF
OR IN CONNECTION  WITH  THE  SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
