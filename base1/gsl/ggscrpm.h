/*---------------------------------------------------------------------------
 *  ggscrpm.h - prototypes for ggscrp messages.
 *
 *  Generated from ggscrp.xml by smtmesg.gsl using GSL.
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/
#ifndef INCLUDE_GGSCRPM
#define INCLUDE_GGSCRPM

/*---------------------------------------------------------------------------
 *  Definitions and prototypes for ggscrp - GSL parser agent.
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 *  Definitions and prototypes for file - Load script file.
 *---------------------------------------------------------------------------*/

extern char *GGSCRP_FILE;

#define declare_ggscrp_file(_event, _priority)                                 \
    method_declare (agent, GGSCRP_FILE, _event, _priority)

/*  Send event - file                                                        */

#define lsend_ggscrp_file(_to, _from,                                          \
    _accept, _reject, _expire, _timeout)                                     \
        event_send (_to,                                                     \
                    _from,                                                   \
                    GGSCRP_FILE,                                               \
                    NULL, 0,                                                 \
                    _accept, _reject, _expire, _timeout)
#define send_ggscrp_file(_to)                                                  \
        event_send (_to,                                                     \
                    &thread-> queue-> qid,                                   \
                    GGSCRP_FILE,                                               \
                    NULL, 0,                                                 \
                    NULL, NULL, NULL, 0)


/*---------------------------------------------------------------------------
 *  Definitions and prototypes for text - Load script text.
 *---------------------------------------------------------------------------*/

extern char *GGSCRP_TEXT;

#define declare_ggscrp_text(_event, _priority)                                 \
    method_declare (agent, GGSCRP_TEXT, _event, _priority)

/*  Send event - text                                                        */

#define lsend_ggscrp_text(_to, _from,                                          \
    _accept, _reject, _expire, _timeout)                                     \
        event_send (_to,                                                     \
                    _from,                                                   \
                    GGSCRP_TEXT,                                               \
                    NULL, 0,                                                 \
                    _accept, _reject, _expire, _timeout)
#define send_ggscrp_text(_to)                                                  \
        event_send (_to,                                                     \
                    &thread-> queue-> qid,                                   \
                    GGSCRP_TEXT,                                               \
                    NULL, 0,                                                 \
                    NULL, NULL, NULL, 0)


/*---------------------------------------------------------------------------
 *  Definitions and prototypes for wait - Wait request.
 *---------------------------------------------------------------------------*/

extern char *GGSCRP_WAIT;

#define declare_ggscrp_wait(_event, _priority)                                 \
    method_declare (agent, GGSCRP_WAIT, _event, _priority)

/*  Send event - wait                                                        */

#define lsend_ggscrp_wait(_to, _from,                                          \
    _accept, _reject, _expire, _timeout)                                     \
        event_send (_to,                                                     \
                    _from,                                                   \
                    GGSCRP_WAIT,                                               \
                    NULL, 0,                                                 \
                    _accept, _reject, _expire, _timeout)
#define send_ggscrp_wait(_to)                                                  \
        event_send (_to,                                                     \
                    &thread-> queue-> qid,                                   \
                    GGSCRP_WAIT,                                               \
                    NULL, 0,                                                 \
                    NULL, NULL, NULL, 0)


typedef struct {
    void *job;                          /*  Job id                           */
    void *script_source;                /*  Script structure                 */
} struct_ggscrp_done;

int
put_ggscrp_done (
          byte **_buffer,
    const void *job,                    /*  Job id                           */
    const void *script_source);         /*  Script structure                 */

int
get_ggscrp_done (
    byte *_buffer,
    struct_ggscrp_done **params);

void
free_ggscrp_done (
    struct_ggscrp_done **params);

/*---------------------------------------------------------------------------
 *  Definitions and prototypes for done - Done reply.
 *---------------------------------------------------------------------------*/

extern char *GGSCRP_DONE;

#define declare_ggscrp_done(_event, _priority)                                 \
    method_declare (agent, GGSCRP_DONE, _event, _priority)

/*  Send event - done                                                        */

int 
lsend_ggscrp_done (
    const QID  *_to,
    const QID  *_from,
          char *_accept,
          char *_reject,
          char *_expire,
          word _timeout,
    const void *job,                /*  Job id                           */
    const void *script_source);     /*  Script structure                 */

#define send_ggscrp_done(_to,                                                  \
            job,                                                             \
            script_source)                                                   \
       lsend_ggscrp_done(_to,                                                  \
            &thread-> queue-> qid,                                           \
            NULL, NULL, NULL, 0,                                             \
            job,                                                             \
            script_source)


typedef struct {
    void *job;                          /*  Job id                           */
    char *error_name;                   /*  Error file name                  */
    word  error_line;                   /*  Error line                       */
    char *error_text;                   /*  Error message text               */
} struct_ggscrp_error;

int
put_ggscrp_error (
          byte **_buffer,
    const void *job,                    /*  Job id                           */
    const char *error_name,             /*  Error file name                  */
    const word  error_line,             /*  Error line                       */
    const char *error_text);            /*  Error message text               */

int
get_ggscrp_error (
    byte *_buffer,
    struct_ggscrp_error **params);

void
free_ggscrp_error (
    struct_ggscrp_error **params);

/*---------------------------------------------------------------------------
 *  Definitions and prototypes for error - Error reply.
 *---------------------------------------------------------------------------*/

extern char *GGSCRP_ERROR;

#define declare_ggscrp_error(_event, _priority)                                \
    method_declare (agent, GGSCRP_ERROR, _event, _priority)

/*  Send event - error                                                       */

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
    const char *error_text);        /*  Error message text               */

#define send_ggscrp_error(_to,                                                 \
            job,                                                             \
            error_name,                                                      \
            error_line,                                                      \
            error_text)                                                      \
       lsend_ggscrp_error(_to,                                                 \
            &thread-> queue-> qid,                                           \
            NULL, NULL, NULL, 0,                                             \
            job,                                                             \
            error_name,                                                      \
            error_line,                                                      \
            error_text)



#endif                                  /*  Included                         */
