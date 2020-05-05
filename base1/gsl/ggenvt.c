/*---------------------------------------------------------------------------
 *  ggenvt.c - GSL/environment package
 *
 *  Generated on 2010/10/06, 19:32:56 from ggenvt
 *  by ggobjt.gsl using GSLgen.
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/

#include "ggpriv.h"                     /*  Project header file              */
#include "ggenvt.h"                     /*  Include header file              */


/*- Macros ------------------------------------------------------------------*/

#define ENV_NAME "env"                  /*  Environment Functions            */

/*- Function prototypes -----------------------------------------------------*/

static EVAL_FUNCTION eval_env_get;
static EVAL_FUNCTION eval_env_set;

/*- Global variables --------------------------------------------------------*/

static PARM_LIST parm_list_v            = { PARM_VALUE };

static GSL_FUNCTION env_functions [] = 
{
    {"get",         1, 1, 1, (void *) &parm_list_v, 1, eval_env_get},
    {"set",         1, 2, 1, (void *) &parm_list_v, 1, eval_env_set}
};

/*- Functions for object "env" - Environment Functions                       */

int register_env_functions (void)
{
    return object_register (ENV_NAME,
                            env_functions,
                            tblsize (env_functions),
                            NULL);
}

static int
eval_env_get (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *name    = argc > 0 ? argv [0] : NULL;

    if (name && (name-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = name-> culprit;
        return 0;
      }

  {
    result-> value. s = mem_strdup (getenv (string_value (& name-> value)));
    if (result-> value. s)
        result-> value. type = TYPE_STRING;

    return 0;
  }

    return 0;
}

static int
eval_env_set (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *name    = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *value   = argc > 1 ? argv [1] : NULL;

    if (name && (name-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = name-> culprit;
        return 0;
      }

  {
    result-> value. type = TYPE_NUMBER;
    if (value
    &&  value-> value. type != TYPE_UNDEFINED)
        result-> value. n = env_set (string_value (& name-> value),
                                     string_value (& value-> value),
                                     1);
    else
      {
        env_clear (string_value (& name-> value));
        result-> value. n = 0;
      }
    return 0;
  }

    return 0;
}


