!============================================================================*
!                                                                            *
!   lrschema.c - Schema for C programming                                    *
!                                                                            *
!   Copyright (c) 1991-2009 iMatix Corporation                               *
!                                                                            *
!   Usage:      Generates two include files with extensions '.d' and '.i'.   *
!                                                                            *
!               Accepts these options:                                       *
!               -opt:stack_max=nnn - size of subdialog stack (20)            *
!               -opt:template=xxxx - template file (template.c)              *
!                                                                            *
!   ------------------ GPL Licensed Source Code ------------------           *
!   iMatix makes this software available under the GNU General               *
!   Public License (GPL) license for open source projects.  For              *
!   details of the GPL license please see www.gnu.org or read the            *
!   file license.gpl provided in this package.                               *
!                                                                            *
!   This program is free software; you can redistribute it and/or            *
!   modify it under the terms of the GNU General Public License as           *
!   published by the Free Software Foundation; either version 2 of           *
!   the License, or (at your option) any later version.                      *
!                                                                            *
!   This program is distributed in the hope that it will be useful,          *
!   but WITHOUT ANY WARRANTY; without even the implied warranty of           *
!   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
!   GNU General Public License for more details.                             *
!                                                                            *
!   You should have received a copy of the GNU General Public                *
!   License along with this program in the file 'license.gpl'; if            *
!   not, write to the Free Software Foundation, Inc., 59 Temple              *
!   Place - Suite 330, Boston, MA 02111-1307, USA.                           *
!                                                                            *
!   You can also license this software under iMatix's General Terms          *
!   of Business (GTB) for commercial projects.  If you have not              *
!   explicitly licensed this software under the iMatix GTB you may           *
!   only use it under the terms of the GNU General Public License.           *
!                                                                            *
!   For more information, send an email to info@imatix.com.                  *
!   --------------------------------------------------------------           *
!============================================================================*

!   You can use the template file to include project-specific code in the
!   generated code at various points.  This is a (better) alternative to
!   changing the schema in order to add your own project code.
!
!   The template file should contain these sections (each starts with a
!   keyword on a line, and ends with <END> on a line).  These sections may
!   be included in newly-generated code (keywords are case-sensitive):
!
!   <HEADER>                    - program header comment
!   <DATA>                      - data definitions
!   <Initialise-The-Program>    - in Initialise-The-Program
!   <Get-External-Event>        - in Get-External-Event
!   <Terminate-The-Program>     - in Terminate-The-Program
!   <Any-Dialog-Module>         - any dialog module
!
:declare string $template = "template.c"

:if not exist $source.c
:echo "lr I: creating skeleton program $source.c..."
:output $source.c
/*===========================================================================*
 *                                                                           *
 *  $source.c   description...                                               *
 *                                                                           *
 *  Written:    $date       $author                                          *
 *  Revised:    $date                                                        *
 *                                                                           *
:include optional $template "<HEADER>" "<END>"
 *  Skeleton generated by LIBERO $version on $fulldate, $time.               *
 *===========================================================================*/

#include "prelude.h"                    /*  Universal include file           */
#include "$dialog.d"                    /*  Include dialog data              */

/*- Function prototypes -----------------------------------------------------*/

/*- Global variables used in this source file only --------------------------*/

static int
    $"feedback";                        /*  Feedback for calling program     */

static char
    *$"some_param";                     /*  Example of parameter             */

:include optional $template "<DATA>" "<END>"

/********************************   M A I N   ********************************/

int my_funct (char *$"p_some_param")
{
    $"feedback" = 0;                    /*  No errors so far                 */
    some_param = $"p_some_param";       /*  Local copy of parameters         */

#   include "$dialog.i"                 /*  Include dialog interpreter       */
}


/*************************   INITIALISE THE PROGRAM   ************************/

MODULE $"initialise_the_program" (void)
{
    $"the_next_event" = $"ok_event";
:include optional $template "<Initialise-The-Program>" "<END>"
}


/***************************   GET EXTERNAL EVENT   **************************/

MODULE $"get_external_event" (void)
{
:include optional $template "<Get-External-Event>" "<END>"
}


/*************************   TERMINATE THE PROGRAM    ************************/

MODULE $"terminate_the_program" (void)
{
    $"the_next_event" = $"terminate_event";
:include optional $template "<Terminate-The-Program>" "<END>"
}

:close
:endif

:output $dialog.d
:echo "lr I: building $dialog.d..."
/*---------------------------------------------------------------------------*
 *  $dialog.d - LIBERO dialog data definitions for $source.c.                *
 *  Generated by LIBERO $version on $fulldate, $time.                        *
 *  Schema file used: $schema.                                               *
 *---------------------------------------------------------------------------*/

/*- Symbolic constants and event numbers ------------------------------------*/

#define _LR_STOP                        0xFFFFL
#define _LR_NULL_EVENT                  -2
enum {
    $"terminate_event" = -1,
:do event
    $name = $number$comma
:enddo
};

enum {
:if defaults
    _LR_defaults_state = $defaults,
:endif
:do state
    _LR_STATE_$name = $number$comma
:enddo
};


/*- Variables used by dialog interpreter ------------------------------------*/

typedef int event_t;                    /*  Type for dialog entity           */
typedef int state_t;                    /*  Type for dialog entity           */
typedef void (fsmfunct) (void);         /*  Address of FSM function          */

static event_t
    _LR_event,                          /*  Event for state transition       */
    $"the_next_event",                  /*  Next event from module           */
    $"the_exception_event";             /*  Exception event from module      */

static state_t
    _LR_state,                          /*  Current dialog state             */
    _LR_savest;                         /*  Saved dialog state               */

static int
    _LR_index,                          /*  Index into vector table          */
    _LR_number;                         /*  Number of next module            */

:if animate
static event_t
    _LR_prev_event;                     /*  Current dialog state             */

static state_t
    _LR_prev_state;                     /*  Current dialog state             */

static int
    _LR_prev_number;                    /*  Number of next module            */

:endif
static Bool
    $"exception_raised";                /*  TRUE if exception raised         */

:if module "Dialog-Return"
:    declare int $stack_max = 256
static state_t
    _LR_state_stack [$stack_max];       /*  Subdialog call stack             */
static event_t
    _LR_event_stack [$stack_max];       /*  Subdialog call stack             */
static int
    _LR_number_stack [$stack_max];      /*  Subdialog call stack             */

static int
    _LR_stack_size;                     /*  Subdialog stack size; 0=empty    */
:endif
:if module "Dialog-Call"
:  if not event "Return"
:     echo "lr E: you must define the 'Return' event"
:     exit 1
:  endif
:endif
/*- Function prototypes -----------------------------------------------------*/

#ifndef MODULE
#define MODULE  static void             /*  Libero dialog modules            */
#endif

static void $"raise_exception"          (event_t event);
MODULE $"initialise_the_program"        (void);
MODULE $"get_external_event"            (void);
:do module
MODULE $name                            (void);
:enddo

/*- Static areas ------------------------------------------------------------*/

static dbyte _LR_nextst [][$events] =
{
:do nextst
:  if $overflow = 0
    { $row }$comma
:  else
    { $row
:    do overflow
     $row
:    enddo
    }$comma
:  endif
:enddo
};

static dbyte _LR_action [][$events] =
{
:set array_base=1
:do action
:  if $overflow = 0
    { $row }$comma
:  else
    { $row
:    do overflow
     $row
:    enddo
    }$comma
:  endif
:enddo
:set array_base=0
};

static dbyte _LR_vector [][$maxaction+1] =
{
    {0},
:do vector
:  if "$row" = ""
    {_LR_STOP}$comma
:  else
    {$row,_LR_STOP}$comma
:  endif
:enddo
};

static fsmfunct *_LR_module [] =
{
:do module
    $name$comma
:enddo
};

:if animate
:push $style
:option -style=normal
static char *_LR_mname [$modules] =
{
:  do module
     "$name"$comma
:  enddo
};

static char *_LR_sname [$states] =
{
:  do state
     "$name"$comma
:  enddo
};

static char *_LR_ename [$events] =
{
:  do event
     "$name"$comma
:  enddo
};
:pop $style
:option -style=$style
:endif
:close

:output $dialog.i
:echo "lr I: building $dialog.i..."
/*---------------------------------------------------------------------------*
 *  $dialog.i - LIBERO dialog interpreter for $source.c.                     *
 *  Generated by LIBERO $version on $fulldate, $time.                        *
 *---------------------------------------------------------------------------*/

    _LR_state = 0;                      /*  First state is always 0          */
:if module "Dialog-Return"
    _LR_stack_size = 0;                 /*  Clear subdialog stack            */
:endif
    $"initialise_the_program" ();
    while ($"the_next_event" != $"terminate_event") {
        _LR_event = $"the_next_event";
:if check
        if (_LR_event >= $events || _LR_event < 0) {
            printf ("State %d - event %d is out of range\n",
                     _LR_state, _LR_event);
            break;
        }
:endif
        _LR_savest = _LR_state;
        _LR_index  = _LR_action [_LR_state][_LR_event];
:if defaults
        /*  If no action for this event, try the defaults state              */
        if (_LR_index == 0) {
            _LR_state = _LR_defaults_state;
            _LR_index = _LR_action [_LR_state][_LR_event];
        }
:endif
:if animate
        printf ("\n%s:\n", _LR_sname [_LR_state]);
        printf ("    (--) %s\n", _LR_ename [_LR_event]);
:endif
:if check
        if (_LR_index == 0) {
            printf ("State %d - event %d is not accepted\n",
                     _LR_state, _LR_event);
            break;
        }
        $"the_next_event"       = _LR_NULL_EVENT;
:endif
        $"the_exception_event"  = _LR_NULL_EVENT;
        $"exception_raised"     = FALSE;

        _LR_number = 0;
        while ((_LR_vector [_LR_index] [_LR_number] != _LR_STOP)
           && (! $"exception_raised")) {
:if animate
            printf ("          + %s\n", _LR_mname [_LR_vector [_LR_index] [_LR_number]]);
            _LR_prev_number = _LR_number;
            _LR_prev_event  = _LR_event;
            _LR_prev_state  = _LR_state;
:endif
            (*_LR_module [_LR_vector [_LR_index] [_LR_number++]]) ();

:if animate

            if ((_LR_number != _LR_prev_number + 1)
            ||  (_LR_event  != _LR_prev_event)
            ||  (_LR_state  != _LR_prev_state)) {
                if (_LR_state  != _LR_prev_state)
                    printf ("\n%s:\n", _LR_sname [_LR_state]);
                printf ("    (..) %s\n", _LR_ename [_LR_event]);
            }
:endif
            _LR_index  = _LR_action [_LR_state][_LR_event];
        }
        if ($"exception_raised") {
            if ($"the_exception_event" != _LR_NULL_EVENT)
                _LR_event = $"the_exception_event";
            $"the_next_event" = _LR_event;
:if animate
            printf ("    (=>) %s\n", _LR_ename [_LR_event]);
:endif
        }
        else
            _LR_state = _LR_nextst [_LR_state][_LR_event];

:if defaults
        if (_LR_state == _LR_defaults_state)
            _LR_state = _LR_savest;
:endif
        if ($"the_next_event" == _LR_NULL_EVENT) {
            $"get_external_event" ();
:if check
            if ($"the_next_event" == _LR_NULL_EVENT) {
                printf ("No event set after event %d in state %d\n",
                         _LR_event, _LR_state);
                break;
            }
:endif
        }
    }
    return ($"feedback");
}

:if module "Dialog-Call"
MODULE $"dialog_call" (void)
{
    if (_LR_stack_size < $stack_max) {
        _LR_state_stack  [_LR_stack_size] = _LR_state;
        _LR_event_stack  [_LR_stack_size] = return_event;
        _LR_number_stack [_LR_stack_size] = 0;
        _LR_stack_size++;
    }
    else {
        printf ("State %d - Dialog-Call overflow\n", _LR_state);
        exit (1);
    }
}

:endif
:if module "Dialog-Return"
MODULE $"dialog_return" (void)
{
    if (_LR_stack_size > 0) {
        _LR_stack_size--;
        _LR_state  = _LR_state_stack [_LR_stack_size];
        _LR_event  = _LR_event_stack [_LR_stack_size];
        _LR_number = _LR_number_stack [_LR_stack_size];
    }
    else {
        printf ("State %d - Dialog-Return underflow\n", _LR_state);
        exit (1);
    }
}

:endif
/*- Standard dialog routines ------------------------------------------------*/

:if module "Dialog-Return"
static void $"call_exception" (event_t event)
{
    $"exception_raised" = TRUE;
    if (_LR_stack_size < $stack_max) {
        _LR_state_stack  [_LR_stack_size] = _LR_state;
        _LR_event_stack  [_LR_stack_size] = _LR_event;
        _LR_number_stack [_LR_stack_size] = _LR_number;
        _LR_stack_size++;
    }
    else {
        printf ("State %d - Dialog-Call overflow\n", _LR_state);
        exit (1);
    }
    if (event >= 0)
        $"the_exception_event" = event;
}

:endif
static void $"raise_exception" (event_t event)
{
    $"exception_raised" = TRUE;
    if (event >= 0)
        $"the_exception_event" = event;
:close

!   Generate stubs for all modules not yet defined in source file

:internal initialise_the_program
:internal get_external_event
:do stubs $source.c $dialog.i

MODULE $name (void)
{
:include optional $template "<$module_name>" "<END>"
}

:enddo