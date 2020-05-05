/*---------------------------------------------------------------------------
 *  ggconv.c - GSL/conv package
 *
 *  Generated on 2010/10/06, 19:32:56 from ggconv
 *  by ggobjt.gsl using GSLgen.
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/

#include "ggpriv.h"                     /*  Project header file              */
#include "ggconv.h"                     /*  Include header file              */


/*- Macros ------------------------------------------------------------------*/

#define CONV_NAME "conv"                /*  Conversion Functions             */

/*- Function prototypes -----------------------------------------------------*/

static EVAL_FUNCTION eval_conv_chr;
static EVAL_FUNCTION eval_conv_number;
static EVAL_FUNCTION eval_conv_ord;
static EVAL_FUNCTION eval_conv_string;

/*- Global variables --------------------------------------------------------*/

static PARM_LIST parm_list_v            = { PARM_VALUE };

static GSL_FUNCTION conv_functions [] = 
{
    {"chr",         0, 1, 1, (void *) &parm_list_v, 1, eval_conv_chr},
    {"number",      0, 1, 1, (void *) &parm_list_v, 1, eval_conv_number},
    {"ord",         0, 1, 1, (void *) &parm_list_v, 1, eval_conv_ord},
    {"string",      0, 1, 1, (void *) &parm_list_v, 1, eval_conv_string}
};

/*- Functions for object "conv" - Conversion Functions                       */

int register_conv_functions (void)
{
    return object_register (CONV_NAME,
                            conv_functions,
                            tblsize (conv_functions),
                            NULL);
}

static int
eval_conv_chr (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *arg     = argc > 0 ? argv [0] : NULL;


  {
    number_value (&arg-> value);
    
    if (arg-> value. type == TYPE_NUMBER)
      {
        result-> value. type  = TYPE_STRING;
        result-> value. s = mem_alloc (2);

        ASSERT (result-> value. s);
        
        if (arg-> value. n > 0
        && arg-> value. n < 256)
            result-> value. s [0] = (char) arg-> value. n;
        else
            result-> value. s [0] = '\0';

        result-> value. s [1] = '\0';
      }
    else
        result-> culprit = arg-> culprit;
  }

    return 0;
}

static int
eval_conv_number (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *arg     = argc > 0 ? argv [0] : NULL;


  {
    number_value (&arg-> value);
    
    if (arg-> value. type == TYPE_NUMBER)
        copy_value (&result-> value, &arg-> value);
  }

    return 0;
}

static int
eval_conv_ord (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *arg     = argc > 0 ? argv [0] : NULL;


  {
    string_value (&arg-> value);
    
    if (arg-> value. type == TYPE_STRING)
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = arg-> value. s [0];
      }
    else
        result-> culprit = arg-> culprit;
  }

    return 0;
}

static int
eval_conv_string (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *arg     = argc > 0 ? argv [0] : NULL;


  {
    if (arg-> value. type != TYPE_UNDEFINED)
      {
        string_value (&arg-> value);
        copy_value (&result-> value, &arg-> value);
      }
  }

    return 0;
}


