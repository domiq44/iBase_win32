/*---------------------------------------------------------------------------
 *  ggpcre.c - GSL/regexp package
 *
 *  Generated on 2010/10/06, 19:32:56 from ggpcre
 *  by ggobjt.gsl using GSLgen.
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/

#include "ggpriv.h"                     /*  Project header file              */
#include "ggpcre.h"                     /*  Include header file              */


/*- Macros ------------------------------------------------------------------*/

#define REGEXP_NAME "regexp"            /*  Regular Expression Functions     */

/*- Function prototypes -----------------------------------------------------*/

static EVAL_FUNCTION eval_regexp_match;

/*- Global variables --------------------------------------------------------*/

static PARM_LIST parm_list_vvr          = { PARM_VALUE,
                                            PARM_VALUE,
                                            PARM_REFERENCE };

static GSL_FUNCTION regexp_functions [] = 
{
    {"match",       2, 0, 3, (void *) &parm_list_vvr, 1, eval_regexp_match}
};

#include "pcre.h"

/*- Functions for object "regexp" - Regular Expression Functions             */

int register_regexp_functions (void)
{
    return object_register (REGEXP_NAME,
                            regexp_functions,
                            tblsize (regexp_functions),
                            NULL);
}

static int
eval_regexp_match (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *pattern = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *subject = argc > 1 ? argv [1] : NULL;

    if (pattern && (pattern-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = pattern-> culprit;
        return 0;
      }
    if (subject && (subject-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = subject-> culprit;
        return 0;
      }

  {
    GGCODE_TCB
        *tcb = gsl_thread-> tcb;
    pcre
        *re;
    char
        *error;
    int 
        erroffset;
    int 
        *ovector;
    int
        oveccount,
        rc,
        i,
        start,
        len;
    RESULT_NODE
        *substr;
    VALUE
        value;

    re = pcre_compile (string_value (&pattern-> value),
                       0,
                       (const char **) &error,
                       &erroffset,
                       NULL);
    if (! re)
      {
        sprintf (object_error, "Regular expression pattern error: %s\n%s\n%*c",
                               error,
                               pattern-> value. s,
                               erroffset + 1, '^');
        return -1;
      }

    rc = pcre_fullinfo (re,
                        NULL,
                        PCRE_INFO_CAPTURECOUNT,
                        &oveccount);
    oveccount = (oveccount + 1) * 3;
    ovector   = mem_alloc (oveccount * sizeof (int));

    rc = pcre_exec (re,
                    NULL,
                    string_value (&subject-> value),
                    (int) strlen (subject-> value. s),
                    0,
                    0,
                    ovector,
                    oveccount);

    (pcre_free) (re);

    if (rc == PCRE_ERROR_NOMATCH)
        rc = 0;
    else if (rc < 0)
      {
        sprintf (object_error, "Regular expression matching error: %d", rc);
        mem_free (ovector);
        return -1;
      }
    else if (rc == 1)
        rc = -1;
    else
        rc -= 1;

    result-> value. type = TYPE_NUMBER;
    result-> value. n    = rc;

    i = 1;
    while (i <= rc &&i + 1 < argc)
      {
        start = ovector [i * 2];
        len   = ovector [i * 2 + 1] - start;

        substr = argv [i + 1];
        value. type = TYPE_STRING;
        value. s    = mem_alloc (len + 1);
        memcpy (value. s, subject-> value. s + start, len);
        value. s [len] = 0;
        if (! store_symbol_definition (&tcb-> scope_stack,
                                       tcb-> ignorecase,
                                       substr,
                                       &value,
                                       &error))
          {
            strncpy (object_error, error, LINE_MAX);
            mem_free (value.s);
            mem_free (ovector);
            return -1;
          }
        mem_free (value.s);

        i++;
      }

    mem_free (ovector);
  }

    return 0;
}


