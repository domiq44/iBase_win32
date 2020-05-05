/*---------------------------------------------------------------------------
 *  ggtime.c - GSL/time package
 *
 *  Generated on 2010/10/06, 19:32:56 from ggtime
 *  by ggobjt.gsl using GSLgen.
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/

#include "ggpriv.h"                     /*  Project header file              */
#include "ggtime.h"                     /*  Include header file              */


/*- Macros ------------------------------------------------------------------*/

#define TIME_NAME "time"                /*  Time Functions                   */

/*- Function prototypes -----------------------------------------------------*/

static EVAL_FUNCTION eval_time_picture;
static EVAL_FUNCTION eval_time_number;
static EVAL_FUNCTION eval_time_now;

/*- Global variables --------------------------------------------------------*/

static PARM_LIST parm_list_v            = { PARM_VALUE };

static GSL_FUNCTION time_functions [] = 
{
    {"now",         0, 0, 0, (void *) &parm_list_v, 1, eval_time_now},
    {"number",      1, 1, 1, (void *) &parm_list_v, 1, eval_time_number},
    {"picture",     0, 2, 1, (void *) &parm_list_v, 1, eval_time_picture}
};

/*- Functions for object "time" - Time Functions                             */

int register_time_functions (void)
{
    return object_register (TIME_NAME,
                            time_functions,
                            tblsize (time_functions),
                            NULL);
}

static int
eval_time_picture (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *time    = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *picture = argc > 1 ? argv [1] : NULL;


  {
    char
        *strptr = conv_time_pict (
            time ? (long) number_value (&time-> value) : time_now (),
            picture ? string_value (&picture-> value) : "hh:mm:ss");

    /*  input time format : HHMMSSCC    */

    if (strptr)
      {
    result-> value. type = TYPE_STRING;
    result-> value. s    = mem_strdup (strptr);
      }
  }
  
    return 0;
}

static int
eval_time_number (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *time    = argc > 0 ? argv [0] : NULL;

    if (time && (time-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = time-> culprit;
        return 0;
      }

  {
    long
        ltime = conv_str_time (string_value (&time-> value));
        
    result-> value. type = TYPE_NUMBER;
    result-> value. n    = ltime;
}
  
    return 0;
}

static int
eval_time_now (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{


    result-> value. type = TYPE_NUMBER;
    result-> value. n    = time_now ();
  
    return 0;
}


