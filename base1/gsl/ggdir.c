/*---------------------------------------------------------------------------
 *  ggdir.c - GSL/dir package
 *
 *  Generated on 2010/10/06, 19:32:56 from ggdir
 *  by ggobjt.gsl using GSLgen.
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/

#include "ggpriv.h"                     /*  Project header file              */
#include "ggdir.h"                      /*  Include header file              */


/*- Macros ------------------------------------------------------------------*/

#define DIR_NAME "dir"                  /*  Directory Functions              */

/*- Function prototypes -----------------------------------------------------*/

static EVAL_FUNCTION eval_dir_load;
static EVAL_FUNCTION eval_dir_create;
static EVAL_FUNCTION eval_dir_delete;
static EVAL_FUNCTION eval_dir_cwd;
static EVAL_FUNCTION eval_dir_setcwd;
static EVAL_FUNCTION eval_dir_files;

/*- Global variables --------------------------------------------------------*/

static PARM_LIST parm_list_xv           = { PARM_EXTENDED_SCOPE,
                                            PARM_VALUE };
static PARM_LIST parm_list_v            = { PARM_VALUE };

static GSL_FUNCTION dir_functions [] = 
{
    {"create",      1, 1, 1, (void *) &parm_list_v, 1, eval_dir_create},
    {"cwd",         0, 0, 0, (void *) &parm_list_v, 1, eval_dir_cwd},
    {"delete",      1, 2, 1, (void *) &parm_list_v, 1, eval_dir_delete},
    {"files",       1, 2, 1, (void *) &parm_list_v, 1, eval_dir_files},
    {"load",        0, 3, 2, (void *) &parm_list_xv, 1, eval_dir_load},
    {"setcwd",      1, 1, 1, (void *) &parm_list_v, 1, eval_dir_setcwd}
};

static long dir_list    (XML_ITEM *xml_parent, const char *path, Bool recurse);
static long dir_unlink  (const char *path, Bool recurse);

static long
dir_list (XML_ITEM *xml_parent, const char *path, Bool recurse)
{
    DIRST
        dir;
    Bool
        dir_rc;
    long
        count = 0;
    char
        *full_dir;
    XML_ITEM
        *xml_item;
    char
        char9 [9];

    dir_rc = open_dir (&dir, path);
    while (dir_rc)
      {
        xml_item = xml_new (xml_parent, "file", NULL);
        xml_put_attr (xml_item, "name",  dir. file_name);
        xml_put_attr (xml_item, "size",  strprintf ("%lu", dir. file_size));
        sprintf (char9, "%8.8lu", timer_to_date (dir. file_time));
        xml_put_attr (xml_item, "date", char9);
        sprintf (char9, "%8.8lu", timer_to_time (dir. file_time));
        xml_put_attr (xml_item, "time", char9);
        xml_put_attr (xml_item, "mode",  strprintf ("%u", dir. file_mode));
        xml_put_attr (xml_item, "attrs", strprintf ("%u", dir. file_attrs));
        xml_put_attr (xml_item, "links", strprintf ("%u", dir. file_nlink));
        xml_put_attr (xml_item, "owner", dir. owner);
        xml_put_attr (xml_item, "group", dir. group);
        xml_put_attr (xml_item, "path", path);
        xml_put_attr (xml_item, "directory", (dir. file_attrs &ATTR_SUBDIR) != 0 ? "1" : "0");

        if (recurse
        &&(dir. file_attrs &ATTR_SUBDIR) != 0)
          {
            full_dir = locate_path (path, dir.file_name);

            count += dir_list (xml_parent, full_dir, TRUE);

            mem_free (full_dir);
          }
        else
            count += 1;

        dir_rc = read_dir (&dir);
      }
    close_dir (&dir);

    return (count);
}

static long
dir_unlink (const char *path, Bool recurse)
{
    DIRST
        dir;
    Bool
        dir_rc;
    long
        count = 0;
    char
        *old_dir;

    old_dir = get_curdir ();
    if (set_curdir (path) == 0) {
        dir_rc = open_dir (&dir, ".");
        while (dir_rc)
          {
            if (recurse
            &&(dir. file_attrs &ATTR_SUBDIR) != 0)
              {
                count += dir_unlink (dir. file_name, TRUE);
                remove_dir (dir. file_name);
              }
            else
              {
                file_delete (dir. file_name);
                count += 1;
              }
            dir_rc = read_dir (&dir);
          }
        close_dir (&dir);

        set_curdir (old_dir);
    }
    mem_free (old_dir);
    remove_dir (path);

    return (count);
}

/*- Functions for object "dir" - Directory Functions                         */

int register_dir_functions (void)
{
    return object_register (DIR_NAME,
                            dir_functions,
                            tblsize (dir_functions),
                            NULL);
}

static int
eval_dir_load (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *scope   = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *path    = argc > 1 ? argv [1] : NULL;
    RESULT_NODE *recurse = argc > 2 ? argv [2] : NULL;


  {
    GGCODE_TCB
        *tcb = gsl_thread-> tcb;
    char
        *error_text;
    XML_ITEM
        *xml_parent;

    xml_parent = extended_scope_xml (&tcb-> scope_stack,
                                     scope ? scope-> scope : NULL,
                                     tcb-> ignorecase,
                                     &error_text);
    if (! xml_parent)
      {
        if (error_text)
            strcpy (object_error, error_text);
        else
            sprintf (object_error, "Unknown data scope: %s",
                                    extended_scope_string (scope-> scope));
        return -1;
      }

    if (path &&path-> value.type == TYPE_UNDEFINED)
      {
        result-> culprit = path-> culprit;
        return 0;
      }

    result-> value.type = TYPE_NUMBER;
    result-> value.n    = (long) dir_list (xml_parent, 
        path ? string_value (&path-> value) : ".",
        (Bool) (recurse? number_value (&recurse-> value): 0));
  }

    return 0;
}

static int
eval_dir_create (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *path    = argc > 0 ? argv [0] : NULL;

    if (path && (path-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = path-> culprit;
        return 0;
      }

  {
    result-> value.n    = make_dir (string_value (&path-> value));
    result-> value.type = TYPE_NUMBER;
  }

    return 0;
}

static int
eval_dir_delete (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *path    = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *recurse = argc > 1 ? argv [1] : NULL;

    if (path && (path-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = path-> culprit;
        return 0;
      }

  {
    result-> value.n = (long) dir_unlink (
        string_value (&path-> value),
        (Bool) (recurse? number_value (&recurse-> value): 0));
    result-> value.type = TYPE_NUMBER;
  }

    return 0;
}

static int
eval_dir_cwd (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{


  {
    char
        * strptr = get_curdir ();

    result-> value.s    = mem_strdup (strptr);
    result-> value.type = TYPE_STRING;
    mem_free (strptr);
  }

    return 0;
}

static int
eval_dir_setcwd (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *path    = argc > 0 ? argv [0] : NULL;

    if (path && (path-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = path-> culprit;
        return 0;
      }

  {
    result-> value.n    = set_curdir (string_value (&path-> value));
    result-> value.type = TYPE_NUMBER;
  }

    return 0;
}

static int
eval_dir_files (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *path    = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *recurse = argc > 1 ? argv [1] : NULL;

    if (path && (path-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = path-> culprit;
        return 0;
      }

  {
    result-> value.n    = (long) dir_files (string_value (&path-> value),
        (Bool) (recurse? number_value (&recurse-> value): 0));
    result-> value.type = TYPE_NUMBER;
  }

    return 0;
}


