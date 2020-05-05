/*---------------------------------------------------------------------------
 *  ggfile.c - GSL/file package
 *
 *  Generated on 2010/10/06, 19:32:56 from ggfile
 *  by ggobjt.gsl using GSLgen.
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/

#include "ggpriv.h"                     /*  Project header file              */
#include "ggfile.h"                     /*  Include header file              */


/*- Macros ------------------------------------------------------------------*/

#define FILE_NAME "file"                /*  File Functions                   */

/*- Function prototypes -----------------------------------------------------*/

static EVAL_FUNCTION eval_file_exists;
static EVAL_FUNCTION eval_file_timestamp;
static EVAL_FUNCTION eval_file_rename;
static EVAL_FUNCTION eval_file_delete;
static EVAL_FUNCTION eval_file_error;
static EVAL_FUNCTION eval_file_locate;
static EVAL_FUNCTION eval_file_open;
static EVAL_FUNCTION eval_file_read;
static EVAL_FUNCTION eval_file_write;
static EVAL_FUNCTION eval_file_tell;
static EVAL_FUNCTION eval_file_seek;
static EVAL_FUNCTION eval_file_close;
static EVAL_FUNCTION eval_file_copy;
static EVAL_FUNCTION eval_file_basename;

/*- Global variables --------------------------------------------------------*/

static PARM_LIST parm_list_v            = { PARM_VALUE };

static GSL_FUNCTION file_functions [] = 
{
    {"basename",    1, 1, 1, (void *) &parm_list_v, 1, eval_file_basename},
    {"close",       1, 1, 1, (void *) &parm_list_v, 1, eval_file_close},
    {"copy",        2, 3, 1, (void *) &parm_list_v, 1, eval_file_copy},
    {"delete",      1, 1, 1, (void *) &parm_list_v, 1, eval_file_delete},
    {"error",       0, 0, 0, (void *) &parm_list_v, 1, eval_file_error},
    {"exists",      1, 1, 1, (void *) &parm_list_v, 1, eval_file_exists},
    {"locate",      1, 2, 1, (void *) &parm_list_v, 1, eval_file_locate},
    {"open",        1, 2, 1, (void *) &parm_list_v, 1, eval_file_open},
    {"read",        1, 1, 1, (void *) &parm_list_v, 1, eval_file_read},
    {"rename",      2, 2, 1, (void *) &parm_list_v, 1, eval_file_rename},
    {"seek",        1, 2, 1, (void *) &parm_list_v, 1, eval_file_seek},
    {"tell",        1, 1, 1, (void *) &parm_list_v, 1, eval_file_tell},
    {"timestamp",   1, 1, 1, (void *) &parm_list_v, 1, eval_file_timestamp},
    {"write",       2, 2, 1, (void *) &parm_list_v, 1, eval_file_write}
};

#define MAX_FILES 1024 
static FILE 
    *file_ptr [MAX_FILES];

static int
    fileerrno;

static char
    line_buffer [LINE_MAX + 1];

/*- Functions for object "file" - File Functions                             */

int register_file_functions (void)
{

  {
    int i;

    for (i = 0; i < MAX_FILES; i++)
        file_ptr [i] = NULL;
    fileerrno  = 0;
  }

    return object_register (FILE_NAME,
                            file_functions,
                            tblsize (file_functions),
                            NULL);
}

static int
eval_file_exists (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *filename = argc > 0 ? argv [0] : NULL;

    if (filename && (filename-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = filename-> culprit;
        return 0;
      }

{
    result-> value. type = TYPE_NUMBER;
    result-> value. n    = file_exists (string_value (&filename-> value));
    if (result-> value. n == -1)
        fileerrno = errno;
}

    return 0;
}

static int
eval_file_timestamp (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *filename = argc > 0 ? argv [0] : NULL;

    if (filename && (filename-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = filename-> culprit;
        return 0;
      }

  {
    time_t
        timer = get_file_time (string_value (&filename-> value));
    if (timer)
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n = (double) timer_to_date (timer) * 1000000
                          + (double) timer_to_time (timer);
      }
    else
        fileerrno = errno;
  }

    return 0;
}

static int
eval_file_rename (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *oldname = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *newname = argc > 1 ? argv [1] : NULL;

    if (oldname && (oldname-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = oldname-> culprit;
        return 0;
      }
    if (newname && (newname-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = newname-> culprit;
        return 0;
      }

{
    result-> value. type = TYPE_NUMBER;
    result-> value. n    = file_rename (string_value (&oldname-> value), 
                                        string_value (&newname-> value));
    if (result-> value. n == -1)
        fileerrno = errno;
}

    return 0;
}

static int
eval_file_delete (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *filename = argc > 0 ? argv [0] : NULL;

    if (filename && (filename-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = filename-> culprit;
        return 0;
      }

{
    result-> value. type = TYPE_NUMBER;
    result-> value. n    = file_delete (string_value (&filename-> value));
    if (result-> value. n == -1)
        fileerrno = errno;
}

    return 0;
}

static int
eval_file_error (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{


{
    result-> value. type = TYPE_STRING;
    result-> value. s    = mem_strdup (strerror (fileerrno));
}

    return 0;
}

static int
eval_file_locate (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *filename = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *path    = argc > 1 ? argv [1] : NULL;

    if (filename && (filename-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = filename-> culprit;
        return 0;
      }

  {
    char
        *found;

    found = file_where ('r',
            path? string_value (&path-> value): "PATH",
            string_value (&filename-> value), NULL);
    
    result-> value. type = TYPE_STRING;
    result-> value. s    = mem_strdup (found? found: "");
  }

    return 0;
}

static int
eval_file_open (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *filename = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *mode    = argc > 1 ? argv [1] : NULL;

    if (filename && (filename-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = filename-> culprit;
        return 0;
      }

  {
    FILE
        *file;
    int
        handle;
    char
        mode_char;

    /*  Find a free handle.  */
    for (handle = 0; handle < MAX_FILES; handle++)
        if (file_ptr [handle] == NULL)
            break;

    if (handle >= MAX_FILES)
      {
        fileerrno = EMFILE;             /*  Too many open files.             */
        return 0;                       /*  GSL function returns undefined.  */
      }
    if (mode)
        mode_char = *string_value (&mode-> value);
    else
        mode_char = 'r';                /*  If mode unspecified, use 'r'     */
    file = file_open (string_value (&filename-> value), mode_char);
    if (file)
      {
        file_ptr [handle]    = file;
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = handle;
      }
    else
        fileerrno = errno;
  }

    return 0;
}

static int
eval_file_read (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *handle  = argc > 0 ? argv [0] : NULL;

    if (handle && (handle-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = handle-> culprit;
        return 0;
      }

  {
    int
        handle_n;
    Bool
        rc;
    handle_n = (int) number_value (&handle-> value);
    if ((handle_n < 0 || handle_n > MAX_FILES)
    ||  (! file_ptr [handle_n]))
      {
        fileerrno = EBADF;              /*  Bad file descriptor.             */
        return 0;
      }
    rc = file_read (file_ptr [handle_n], line_buffer);
    if (rc)
      {
        result-> value. type = TYPE_STRING;
        result-> value. s    = mem_strdup (line_buffer);
      }
  }

    return 0;
}

static int
eval_file_write (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *handle  = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *string  = argc > 1 ? argv [1] : NULL;

    if (handle && (handle-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = handle-> culprit;
        return 0;
      }
    if (string && (string-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string-> culprit;
        return 0;
      }

  {
    int
        handle_n;
    char
        *rc;
    handle_n = (int) number_value (&handle-> value);
    if ((handle_n < 0 || handle_n > MAX_FILES)
    ||  (! file_ptr [handle_n]))
      {
        fileerrno = EBADF;              /*  Bad file descriptor.             */
        return 0;
      }
    rc = file_write (file_ptr [handle_n], string_value (&string-> value));
    result-> value. type = TYPE_NUMBER;
    if (rc)
        result-> value. n = 0;
    else
      {
        result-> value. n = -1;
        fileerrno = errno;
      }
  }

    return 0;
}

static int
eval_file_tell (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *handle  = argc > 0 ? argv [0] : NULL;

    if (handle && (handle-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = handle-> culprit;
        return 0;
      }

  {
    int
        handle_n;
    handle_n = (int) number_value (&handle-> value);
    if ((handle_n < 0 || handle_n > MAX_FILES)
    ||  (! file_ptr [handle_n]))
      {
        fileerrno = EBADF;              /*  Bad file descriptor.             */
        return 0;
      }
    result-> value. type = TYPE_NUMBER;
    result-> value. n    = ftell (file_ptr [handle_n]);
  }

    return 0;
}

static int
eval_file_seek (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *handle  = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *offset  = argc > 1 ? argv [1] : NULL;

    if (handle && (handle-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = handle-> culprit;
        return 0;
      }

  {
    int
        handle_n;
    long
        offset_n;
        
    handle_n = (int)   number_value (&handle-> value);
    if ((handle_n < 0 || handle_n > MAX_FILES)
    ||  (! file_ptr [handle_n]))
      {
        fileerrno = EBADF;              /*  Bad file descriptor.             */
        return 0;
      }
    if (offset)
        offset_n = (qbyte) number_value (&offset-> value);
    else
        offset_n = 0;

    if (offset_n == -1)
        fseek (file_ptr [handle_n], 0, SEEK_END);
    else
        fseek (file_ptr [handle_n], offset_n, SEEK_SET);
        
    result-> value. type = TYPE_NUMBER;
    result-> value. n    = 0;
  }

    return 0;
}

static int
eval_file_close (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *handle  = argc > 0 ? argv [0] : NULL;

    if (handle && (handle-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = handle-> culprit;
        return 0;
      }

  {
    int
        handle_n;
    handle_n = (int) number_value (&handle-> value);
    if ((handle_n < 0 || handle_n > MAX_FILES)
    ||  (! file_ptr [handle_n]))
        return 0;
    result-> value. type = TYPE_NUMBER;
    result-> value. n    = file_close (file_ptr [handle_n]);
    file_ptr [handle_n]  = NULL;

    if (result-> value. n == -1)
        fileerrno = errno;
  }

    return 0;
}

static int
eval_file_copy (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *src     = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *dest    = argc > 1 ? argv [1] : NULL;
    RESULT_NODE *mode    = argc > 2 ? argv [2] : NULL;

    if (src && (src-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = src-> culprit;
        return 0;
      }
    if (dest && (dest-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = dest-> culprit;
        return 0;
      }

  {
    result-> value. type = TYPE_NUMBER;
    result-> value. n    = (double) file_copy (
        string_value (&dest-> value), 
        string_value (&src -> value),
        (char) (mode? *string_value (&mode-> value): 'b')
    );
    if (result-> value. n == -1)
        fileerrno = errno;
  }

    return 0;
}

static int
eval_file_basename (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *filename = argc > 0 ? argv [0] : NULL;

    if (filename && (filename-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = filename-> culprit;
        return 0;
      }

  {
    char
        *strptr = strip_extension (string_value (&filename-> value));
    result-> value. s    = mem_strdup (strptr);
    result-> value. type = TYPE_STRING;
  }

    return 0;
}


