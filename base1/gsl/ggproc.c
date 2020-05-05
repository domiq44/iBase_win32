/*---------------------------------------------------------------------------
 *  ggproc.c - GSL/proc package
 *
 *  Generated on 2010/10/06, 19:32:56 from ggproc
 *  by ggobjt.gsl using GSLgen.
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/

#include "ggpriv.h"                     /*  Project header file              */
#include "ggproc.h"                     /*  Include header file              */


/*- Macros ------------------------------------------------------------------*/

#define PROC_NAME "proc"                /*  Process Management               */

/*- Function prototypes -----------------------------------------------------*/

static EVAL_FUNCTION eval_proc_version;
static EVAL_FUNCTION eval_proc_run;
static EVAL_FUNCTION eval_proc_sleep;

/*- Global variables --------------------------------------------------------*/

static PARM_LIST parm_list_v            = { PARM_VALUE };

static GSL_FUNCTION proc_functions [] = 
{
    {"run",         1, 2, 1, (void *) &parm_list_v, 1, eval_proc_run},
    {"sleep",       1, 1, 1, (void *) &parm_list_v, 1, eval_proc_sleep},
    {"version",     0, 1, 1, (void *) &parm_list_v, 1, eval_proc_version}
};

#define GSLPROC_VERSION       "GSL/PROC/1.0"

#define STRING_VALUE(arg,default)   (arg? string_value (&arg-> value): default)
#define NUMBER_VALUE(arg,default)   (arg? number_value (&arg-> value): default)

#define RETURN_STATUS(status) \
    { \
    result-> value.type = TYPE_NUMBER;\
    result-> value.n    = (status);\
    return (0); \
    }


/*  Local function prototypes                                                */

static XML_ITEM *open_xml_item (THREAD *gsl_thread, RESULT_NODE *scope, char *name);


/*  ---------------------------------------------------------------------------
    open_xml_item

    Prepares a new XML item ready to receive data.  Returns the new XML item
    if successful, else returns NULL.  Any existing items with the specified
    name are deleted before the new empty item is created.
    The following is black magic, unless you know how the GSL internals work.
 */

static XML_ITEM *
open_xml_item (THREAD *gsl_thread, RESULT_NODE *scope, char *name)
{
    XML_ITEM
        *xml_scope,                     /*  Parent scope                     */
        *xml_item = NULL,               /*  Created item                     */
        *xml_next;                      /*  Next item, for walking list      */
    GGCODE_TCB
        *tcb;                           /*  Thread control block             */
    char
        *gg_error;                      /*  Possible error from ggcomm       */

    tcb = gsl_thread-> tcb;
    xml_scope = extended_scope_xml (&tcb-> scope_stack,
                                    scope? scope-> scope: NULL,
                                    tcb-> ignorecase, &gg_error);
    if (xml_scope) {
        /*  Look for, delete any record items present as children of scope   */
        xml_item = xml_first_child (xml_scope);
        while (xml_item) {
            xml_next = xml_next_sibling (xml_item);
            if (streq (xml_item_name (xml_item), name))
                xml_free (xml_item);
            xml_item = xml_next;
        }
        xml_item = xml_new (xml_scope, name, NULL);
    }
    else {
        if (gg_error)
            strcpy (object_error, gg_error);
        else
            sprintf (object_error, "Unknown data scope: %s",
                                    extended_scope_string (scope-> scope));
    }
    return (xml_item);
}

/*- Functions for object "proc" - Process Management                         */

int register_proc_functions (void)
{
    return object_register (PROC_NAME,
                            proc_functions,
                            tblsize (proc_functions),
                            NULL);
}

static int
eval_proc_version (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *type    = argc > 0 ? argv [0] : NULL;


{
    char
        *my_type,
        *version;
        
    my_type = STRING_VALUE (type, "obj");
    if (streq (my_type, "obj")) {
        version = GSLPROC_VERSION;
    }
    else
        version = "(illegal type argument)";    

    result-> value.type = TYPE_STRING;
    result-> value.s    = mem_strdup (version);
}

    return 0;
}

static int
eval_proc_run (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *command = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *workdir = argc > 1 ? argv [1] : NULL;

    if (command && (command-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = command-> culprit;
        return 0;
      }

{
    char
        *my_command,
        *my_workdir;
    PROCESS
        process;                        /*  Created process id               */
    char
        *my_stdout,                     /*  Capture output from command      */
        *my_stderr;
    XML_ITEM
        *xml_item;                      /*  Where we return data             */
    DESCR
        *file_data;                     /*  Slurped data                     */
    int
        status;                         /*  Status to return                 */

    my_command = STRING_VALUE (command, "");
    my_workdir = STRING_VALUE (workdir, ".");
    my_stderr  = get_tmp_file_name (".", NULL, "tmp");
    my_stdout  = get_tmp_file_name (".", NULL, "tmp");
    if ((xml_item = open_xml_item (gsl_thread, NULL, "process")) == NULL)
        return (-1);
                     
    process = process_create (
        my_command,                     /*  Name of file to execute          */
        NULL,                           /*  Arguments for process, or NULL   */
        my_workdir,                     /*  Working directory, or NULL       */
        NULL,                           /*  Stdin device, or NULL            */
        my_stdout,                      /*  Stdout device, or NULL           */
        my_stderr,                      /*  Stderr device, or NULL           */
        NULL,                           /*  Environment variables, or NULL   */
        TRUE                            /*  Wait for process to end          */
    );
    if (process == NULL_PROCESS)
        status = -1;
    else {
        file_data = file_slurp (my_stdout);
        if (file_data && file_data-> size > 0) {
            xml_put_attr (xml_item, "stdout", (char *) file_data-> data);
            mem_free (file_data);
        }
        file_data = file_slurp (my_stderr);
        if (file_data && file_data-> size > 0) {
            xml_put_attr (xml_item, "stderr", (char *) file_data-> data);
            mem_free (file_data);
        }
        status = 0;
    }
    file_delete (my_stdout);
    file_delete (my_stderr);
    mem_free (my_stdout);
    mem_free (my_stderr);
    RETURN_STATUS (status);
}

    return 0;
}

static int
eval_proc_sleep (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *delay   = argc > 0 ? argv [0] : NULL;

    if (delay && (delay-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = delay-> culprit;
        return 0;
      }

{
    long
        my_delay;

     my_delay = (long) NUMBER_VALUE (delay, 1);
     sleep (my_delay);
}

    return 0;
}


