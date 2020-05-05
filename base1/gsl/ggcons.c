/*---------------------------------------------------------------------------
 *  ggcons.c - GSL/console package
 *
 *  Generated on 2010/10/06, 19:32:56 from ggcons
 *  by ggobjt.gsl using GSLgen.
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/

#include "ggpriv.h"                     /*  Project header file              */
#include "ggcons.h"                     /*  Include header file              */


/*- Macros ------------------------------------------------------------------*/

#define CONSOLE_NAME "console"          /*  Console i/o                      */

/*- Function prototypes -----------------------------------------------------*/

static EVAL_FUNCTION eval_console_version;
static EVAL_FUNCTION eval_console_put;
static EVAL_FUNCTION eval_console_get;

/*- Global variables --------------------------------------------------------*/

static PARM_LIST parm_list_v            = { PARM_VALUE };

static GSL_FUNCTION console_functions [] = 
{
    {"get",         0, 1, 1, (void *) &parm_list_v, 1, eval_console_get},
    {"put",         1, 1, 1, (void *) &parm_list_v, 1, eval_console_put},
    {"version",     0, 1, 1, (void *) &parm_list_v, 1, eval_console_version}
};

#define GSLCONS_VERSION       "GSL/CONSOLE/1.0"

#define STRING_VALUE(arg,default)   (arg? string_value (&arg-> value): default)
#define NUMBER_VALUE(arg,default)   (arg? number_value (&arg-> value): default)

#define RETURN_STATUS(status) \
    { \
    result-> value.type = TYPE_NUMBER;\
    result-> value.n    = (status);\
    return (0); \
    }

/*- Functions for object "console" - Console i/o                             */

int register_console_functions (void)
{
    return object_register (CONSOLE_NAME,
                            console_functions,
                            tblsize (console_functions),
                            NULL);
}

static int
eval_console_version (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *type    = argc > 0 ? argv [0] : NULL;


{
    char
        *my_type,
        *version;
        
    my_type = STRING_VALUE (type, "obj");
    if (streq (my_type, "obj")) {
        version = GSLCONS_VERSION;
    }
    else
        version = "(illegal type argument)";    

    result-> value.type = TYPE_STRING;
    result-> value.s    = mem_strdup (version);
}

    return 0;
}

static int
eval_console_put (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *text    = argc > 0 ? argv [0] : NULL;

    if (text && (text-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = text-> culprit;
        return 0;
      }

{
    fprintf (stderr, STRING_VALUE (text, ""));
    fprintf (stderr, "\n");
    fflush  (stderr);
    RETURN_STATUS (0);
}

    return 0;
}

static int
eval_console_get (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *prompt  = argc > 0 ? argv [0] : NULL;


{
    static char
        buffer [2048 + 1];
        
    printf (STRING_VALUE (prompt, ""));
    fflush (stderr);
    fgets (buffer, 1024, stdin);

    buffer [strlen (buffer) - 1] = '\0';
    result-> value.type = TYPE_STRING;
    result-> value.s    = mem_strdup (buffer);
    return (0);
}

    return 0;
}


