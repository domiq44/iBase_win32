/*---------------------------------------------------------------------------
 *  ggdate.c - GSL/date package
 *
 *  Generated on 2010/10/06, 19:32:56 from ggdate
 *  by ggobjt.gsl using GSLgen.
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/

#include "ggpriv.h"                     /*  Project header file              */
#include "ggdate.h"                     /*  Include header file              */


/*- Macros ------------------------------------------------------------------*/

#define DATE_NAME "date"                /*  Date Functions                   */

/*- Function prototypes -----------------------------------------------------*/

static EVAL_FUNCTION eval_date_picture;
static EVAL_FUNCTION eval_date_number;
static EVAL_FUNCTION eval_date_now;

/*- Global variables --------------------------------------------------------*/

static PARM_LIST parm_list_v            = { PARM_VALUE };

static GSL_FUNCTION date_functions [] = 
{
    {"now",         0, 0, 0, (void *) &parm_list_v, 1, eval_date_now},
    {"number",      1, 1, 1, (void *) &parm_list_v, 1, eval_date_number},
    {"picture",     0, 2, 1, (void *) &parm_list_v, 1, eval_date_picture}
};

/*- Functions for object "date" - Date Functions                             */

int register_date_functions (void)
{
    return object_register (DATE_NAME,
                            date_functions,
                            tblsize (date_functions),
                            NULL);
}

static int
eval_date_picture (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *date    = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *picture = argc > 1 ? argv [1] : NULL;


  {
    char
        *strptr = conv_date_pict (
            date ? (long) number_value (&date-> value) : date_now (),
            picture ? string_value (&picture-> value) : "yyyy/mm/dd");

    /*  input date format : YYYYMMDD    */

    if (strptr)
      {
        result-> value. type = TYPE_STRING;
        result-> value. s    = mem_strdup (strptr);
      }
  }

    return 0;
}

static int
eval_date_number (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *date    = argc > 0 ? argv [0] : NULL;

    if (date && (date-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = date-> culprit;
        return 0;
      }

  {
    long
        ldate = conv_str_date (string_value (&date-> value),
            FLAG_D_ORDER_YMD, DATE_YMD_COMPACT, DATE_ORDER_YMD);
        
    result-> value. type = TYPE_NUMBER;
    result-> value. n    = ldate;
}

    return 0;
}

static int
eval_date_now (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{


    result-> value. type = TYPE_NUMBER;
    result-> value. n    = date_now ();
  
    return 0;
}


