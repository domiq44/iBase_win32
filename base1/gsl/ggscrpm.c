/*---------------------------------------------------------------------------
 *  ggscrpm.c - functions for ggscrp messages.
 *
 *  Generated from ggscrp.xml by smtmesg.gsl using GSL
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/

#include "sfl.h"                        /*  SFL header file                  */
#include "smtlib.h"                     /*  SMT header file                  */
#include "ggscrpm.h"                    /*  Definitions & prototypes         */

/*---------------------------------------------------------------------------
 *  Message functions for ggscrp - GSL parser agent.
 *---------------------------------------------------------------------------*/

char *GGSCRP_FILE = "GGSCRP FILE";

char *GGSCRP_TEXT = "GGSCRP TEXT";

char *GGSCRP_WAIT = "GGSCRP WAIT";


/*  ---------------------------------------------------------------------[<]-
    Function: put_ggscrp_done

    Synopsis: Formats a done message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_ggscrp_done (
    byte **_buffer,
    const void *job,                    /*  Job id                           */
    const void *script_source)          /*  Script structure                 */
{
    struct_ggscrp_done
        *_struct_ptr;

    _struct_ptr = mem_alloc (sizeof (struct_ggscrp_done));
    *_buffer = (byte *) _struct_ptr;
    if (_struct_ptr)
      {
        _struct_ptr-> job               = (void *) job;
        _struct_ptr-> script_source     = (void *) script_source;

        return sizeof (*_struct_ptr);
      }
    else
        return 0;
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_ggscrp_done

    Synopsis: Accepts a buffer containing a done message,
    and unpacks it into a new struct_ggscrp_done structure. Free the
    structure using free_ggscrp_done() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_ggscrp_done (
    byte *_buffer,
    struct_ggscrp_done **params)
{
    struct_ggscrp_done
        *_struct_ptr;

    _struct_ptr = (struct_ggscrp_done *) _buffer;
    *params = mem_alloc (sizeof (struct_ggscrp_done));
    if (*params)
      {
        (* params)-> job                = _struct_ptr-> job;
        (* params)-> script_source      = _struct_ptr-> script_source;
        return 0;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_ggscrp_done

    Synopsis: frees a structure allocated by get_ggscrp_done().
    ---------------------------------------------------------------------[>]-*/

void
free_ggscrp_done (
    struct_ggscrp_done **params)
{
    mem_free (*params);
    *params = NULL;
}

char *GGSCRP_DONE = "GGSCRP DONE";

/*  ---------------------------------------------------------------------[<]-
    Function: lsend_ggscrp_done

    Synopsis: Sends a done - Done reply
              event to the ggscrp agent
    ---------------------------------------------------------------------[>]-*/

int 
lsend_ggscrp_done (
    const QID  *_to,
    const QID  *_from,
          char *_accept,
          char *_reject,
          char *_expire,
          word _timeout,
    const void *job,                /*  Job id                           */
    const void *script_source)      /*  Script structure                 */
{
    byte *_body;
    int   _size,
          _rc;
    _size = put_ggscrp_done
                (&_body,
                 job,
                 script_source);
    if (_size)
      {
        _rc = event_send (_to, _from, GGSCRP_DONE,
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_ggscrp_error

    Synopsis: Formats a error message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_ggscrp_error (
    byte **_buffer,
    const void *job,                    /*  Job id                           */
    const char *error_name,             /*  Error file name                  */
    const word  error_line,             /*  Error line                       */
    const char *error_text)             /*  Error message text               */
{
    struct_ggscrp_error
        *_struct_ptr;
    int
        _total_size = sizeof (struct_ggscrp_error);
    char
        *_ptr;

    _total_size += error_name ? strlen (error_name) + 1 : 0;
    _total_size += error_text ? strlen (error_text) + 1 : 0;
    _struct_ptr = mem_alloc (_total_size);
    *_buffer = (byte *) _struct_ptr;
    if (_struct_ptr)
      {
        _ptr = (char *) _struct_ptr + sizeof (struct_ggscrp_error);
        _struct_ptr-> job               = (void *) job;
        if (error_name)
          {
            _struct_ptr-> error_name        = (char *) _ptr;
            strcpy ((char *) _ptr, error_name);
            _ptr += strlen (error_name) + 1;
          }
        else
            _struct_ptr-> error_name        = NULL;
        _struct_ptr-> error_line        = error_line;
        if (error_text)
          {
            _struct_ptr-> error_text        = (char *) _ptr;
            strcpy ((char *) _ptr, error_text);
            _ptr += strlen (error_text) + 1;
          }
        else
            _struct_ptr-> error_text        = NULL;

        return _total_size;
      }
    else
        return 0;
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_ggscrp_error

    Synopsis: Accepts a buffer containing a error message,
    and unpacks it into a new struct_ggscrp_error structure. Free the
    structure using free_ggscrp_error() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_ggscrp_error (
    byte *_buffer,
    struct_ggscrp_error **params)
{
    struct_ggscrp_error
        *_struct_ptr;
    char
        *_ptr;

    _struct_ptr = (struct_ggscrp_error *) _buffer;
    *params = mem_alloc (sizeof (struct_ggscrp_error));
    if (*params)
      {
        _ptr = (char *) _struct_ptr + sizeof (struct_ggscrp_error);
        (* params)-> job                = _struct_ptr-> job;
        if (_struct_ptr-> error_name)
          {
            (* params)-> error_name         = mem_strdup (_ptr);
            _ptr += strlen ((* params)-> error_name) + 1;
          }
        else
            (* params)-> error_name         = NULL;
        (* params)-> error_line         = _struct_ptr-> error_line;
        if (_struct_ptr-> error_text)
          {
            (* params)-> error_text         = mem_strdup (_ptr);
            _ptr += strlen ((* params)-> error_text) + 1;
          }
        else
            (* params)-> error_text         = NULL;
        return 0;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_ggscrp_error

    Synopsis: frees a structure allocated by get_ggscrp_error().
    ---------------------------------------------------------------------[>]-*/

void
free_ggscrp_error (
    struct_ggscrp_error **params)
{
    mem_free ((*params)-> error_name);
    mem_free ((*params)-> error_text);
    mem_free (*params);
    *params = NULL;
}

char *GGSCRP_ERROR = "GGSCRP ERROR";

/*  ---------------------------------------------------------------------[<]-
    Function: lsend_ggscrp_error

    Synopsis: Sends a error - Error reply
              event to the ggscrp agent
    ---------------------------------------------------------------------[>]-*/

int 
lsend_ggscrp_error (
    const QID  *_to,
    const QID  *_from,
          char *_accept,
          char *_reject,
          char *_expire,
          word _timeout,
    const void *job,                /*  Job id                           */
    const char *error_name,         /*  Error file name                  */
    const word  error_line,         /*  Error line                       */
    const char *error_text)         /*  Error message text               */
{
    byte *_body;
    int   _size,
          _rc;
    _size = put_ggscrp_error
                (&_body,
                 job,
                 error_name,
                 error_line,
                 error_text);
    if (_size)
      {
        _rc = event_send (_to, _from, GGSCRP_ERROR,
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


