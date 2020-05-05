/*---------------------------------------------------------------------------
 *  ggstrn.c - GSL/string package
 *
 *  Generated on 2010/10/06, 19:32:56 from ggstrn
 *  by ggobjt.gsl using GSLgen.
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/

#include "ggpriv.h"                     /*  Project header file              */
#include "ggstrn.h"                     /*  Include header file              */


/*- Macros ------------------------------------------------------------------*/

#define STRING_NAME "string"            /*  String Functions                 */

/*- Function prototypes -----------------------------------------------------*/

static EVAL_FUNCTION eval_string_length;
static EVAL_FUNCTION eval_string_locate;
static EVAL_FUNCTION eval_string_substr;
static EVAL_FUNCTION eval_string_trim;
static EVAL_FUNCTION eval_string_justify;
static EVAL_FUNCTION eval_string_certify;
static EVAL_FUNCTION eval_string_replace;
static EVAL_FUNCTION eval_string_match;
static EVAL_FUNCTION eval_string_prefixed;
static EVAL_FUNCTION eval_string_prefix;
static EVAL_FUNCTION eval_string_defix;
static EVAL_FUNCTION eval_string_hash;
static EVAL_FUNCTION eval_string_convch;
static EVAL_FUNCTION eval_string_lexcmp;
static EVAL_FUNCTION eval_string_lexncmp;
static EVAL_FUNCTION eval_string_lexwcmp;
static EVAL_FUNCTION eval_string_matchpat;
static EVAL_FUNCTION eval_string_soundex;
static EVAL_FUNCTION eval_string_cntch;
static EVAL_FUNCTION eval_string_xml;
static EVAL_FUNCTION eval_string_html_encode;
static EVAL_FUNCTION eval_string_html_decode;

/*- Global variables --------------------------------------------------------*/

static PARM_LIST parm_list_v            = { PARM_VALUE };
static PARM_LIST parm_list_x            = { PARM_EXTENDED_SCOPE };

static GSL_FUNCTION string_functions [] = 
{
    {"certify",     1, 2, 1, (void *) &parm_list_v, 1, eval_string_certify},
    {"cntch",       2, 2, 1, (void *) &parm_list_v, 1, eval_string_cntch},
    {"convch",      3, 3, 1, (void *) &parm_list_v, 1, eval_string_convch},
    {"defix",       2, 2, 1, (void *) &parm_list_v, 1, eval_string_defix},
    {"hash",        1, 1, 1, (void *) &parm_list_v, 1, eval_string_hash},
    {"html_decode", 1, 1, 1, (void *) &parm_list_v, 1, eval_string_html_decode},
    {"html_encode", 1, 1, 1, (void *) &parm_list_v, 1, eval_string_html_encode},
    {"justify",     2, 3, 1, (void *) &parm_list_v, 1, eval_string_justify},
    {"length",      1, 1, 1, (void *) &parm_list_v, 1, eval_string_length},
    {"lexcmp",      2, 2, 1, (void *) &parm_list_v, 1, eval_string_lexcmp},
    {"lexncmp",     3, 3, 1, (void *) &parm_list_v, 1, eval_string_lexncmp},
    {"lexwcmp",     2, 2, 1, (void *) &parm_list_v, 1, eval_string_lexwcmp},
    {"locate",      2, 2, 1, (void *) &parm_list_v, 1, eval_string_locate},
    {"match",       2, 2, 1, (void *) &parm_list_v, 1, eval_string_match},
    {"matchpat",    2, 3, 1, (void *) &parm_list_v, 1, eval_string_matchpat},
    {"prefix",      2, 2, 1, (void *) &parm_list_v, 1, eval_string_prefix},
    {"prefixed",    2, 2, 1, (void *) &parm_list_v, 1, eval_string_prefixed},
    {"replace",     2, 2, 1, (void *) &parm_list_v, 1, eval_string_replace},
    {"soundex",     1, 1, 1, (void *) &parm_list_v, 1, eval_string_soundex},
    {"substr",      2, 4, 1, (void *) &parm_list_v, 1, eval_string_substr},
    {"trim",        1, 1, 1, (void *) &parm_list_v, 1, eval_string_trim},
    {"xml",         0, 1, 1, (void *) &parm_list_x, 1, eval_string_xml}
};

static Bool
node_is_countable (int argn, RESULT_NODE **argv, 
                   char *function, RESULT_NODE *result)
{
    if (argv [argn])
      {
        if (argv [argn]-> value. type != TYPE_UNDEFINED)
          {
            number_value (&argv [argn]-> value);
            if ((argv [argn]-> value. type == TYPE_NUMBER)
            && (argv [argn]-> value. n == floor (argv [argn]-> value. n))
            && (argv [argn]-> value. n >= 0))
                return TRUE;
            else
                sprintf (object_error, "Illegal argument %u to function %s.", 
                                       argn + 1, function);
          }
        else
            result-> culprit = argv [argn]-> culprit;
      }
    
    return FALSE;
}

/*- Functions for object "string" - String Functions                         */

int register_string_functions (void)
{
    return object_register (STRING_NAME,
                            string_functions,
                            tblsize (string_functions),
                            NULL);
}

static int
eval_string_length (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *string  = argc > 0 ? argv [0] : NULL;

    if (string && (string-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string-> culprit;
        return 0;
      }

    result-> value. type = TYPE_NUMBER;
    result-> value. n    = strlen (string_value (&string-> value));

    return 0;
}

static int
eval_string_locate (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *haystack = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *needle  = argc > 1 ? argv [1] : NULL;

    if (haystack && (haystack-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = haystack-> culprit;
        return 0;
      }
    if (needle && (needle-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = needle-> culprit;
        return 0;
      }

  {
    char
        *strptr = strstr (string_value (&haystack-> value),
                          string_value (&needle  -> value));
    if (strptr)
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = strptr - haystack-> value. s;
      }
  }

    return 0;
}

static int
eval_string_substr (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *string  = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *start   = argc > 1 ? argv [1] : NULL;
    RESULT_NODE *end     = argc > 2 ? argv [2] : NULL;
    RESULT_NODE *length  = argc > 3 ? argv [3] : NULL;

    if (string && (string-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string-> culprit;
        return 0;
      }

  {
    long
        start_n  = 0,
        end_n    = 0,
        length_n = 0;

    if (start  &&start -> value. type == TYPE_UNDEFINED)
        start = NULL;
    if (end    &&end   -> value. type == TYPE_UNDEFINED)
        end = NULL;
    if (length &&length-> value. type == TYPE_UNDEFINED)
        length = NULL;
  
    if (start &&end &&length)
      {
        strcpy (object_error, "Too many parameters for function 'substr'.");
        return -1;
      }
    if (!(start || end || length))
      {
        strcpy (object_error, "Too few parameters for function 'substr'.");
        return -1;
      }
    if (start)
      {
        if (node_is_countable (1, argv, "substr", result))
            start_n = (long) start-> value. n;
        else
            return -1;
      }
    if (end)
      {
        if (node_is_countable (2, argv, "substr", result))
            end_n = (long) end-> value. n;
        else
            return -1;
      }
    if (length)
      {
        if (node_is_countable (3, argv, "substr", result))
            length_n = (long) length-> value. n;
        else
            return -1;
      }
    if (start &&end &&(end_n < start_n))
      {
        strcpy (object_error, "'End' must be at least 'Start' in 'substr'");
        return -1;
      }
    if (length &&!start)
      {
        if (!end)
            end_n = strlen (string-> value. s) - 1;
        start_n = end_n - length_n + 1;
        if (start_n < 0)
            start_n = 0;
        length_n = end_n - start_n + 1;
      }
    else
      {
        if (!start)
            start_n = 0;
        if (!length)
          {
            if (end)
                length_n = end_n - start_n + 1;
            else
                length_n = strlen (string-> value. s);
          }
      }
    if (start_n >= (long) strlen (string-> value. s))
        result-> value. s = mem_strdup ("");
    else
      {
        result-> value. s = mem_alloc (length_n + 1);
        if (start_n >= 0)
            strncpy (result-> value. s, &string-> value. s [start_n], length_n);
        else
            strncpy (result-> value. s, string-> value. s, length_n);
        
        (result-> value. s) [length_n] = '\0';
      }
    result-> value. type = TYPE_STRING;
  }

    return 0;
}

static int
eval_string_trim (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *string  = argc > 0 ? argv [0] : NULL;

    if (string && (string-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string-> culprit;
        return 0;
      }

{
    result-> value. type = argv [0]-> value. type;
    if (argv [0]-> value. s)
      {
        result-> value. s = mem_strdup (strcrop (argv [0]-> value. s));
        ASSERT (result-> value. s);
      }
    result-> value. n = argv [0]-> value. n;
}

    return 0;
}

static int
eval_string_justify (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *string  = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *width   = argc > 1 ? argv [1] : NULL;
    RESULT_NODE *prefix  = argc > 2 ? argv [2] : NULL;

    if (string && (string-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string-> culprit;
        return 0;
      }
    if (width && (width-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = width-> culprit;
        return 0;
      }

{
    unsigned long
        width_n;

    if (node_is_countable (1, argv, "justify", result))
        width_n = (unsigned long) width-> value. n;
    else
        return -1;

    result-> value. s = strreformat (string_value (&string-> value),
                                     width_n,
                                     prefix ? string_value (&prefix-> value) : NULL);
    result-> value. type = TYPE_STRING;
  }

    return 0;
}

static int
eval_string_certify (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *number  = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *language = argc > 1 ? argv [1] : NULL;

    if (number && (number-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = number-> culprit;
        return 0;
      }

  {
    #define MAX_CHARS           512
    #define DEFAULT_LANGUAGE    "en-gb"

    static char
        buffer [MAX_CHARS + 1];

    if (language  &&language -> value. type == TYPE_UNDEFINED)
        language = NULL;
        
    certify_the_number (
        buffer,
        MAX_CHARS,
        (long) number_value (&number-> value),
        language ? string_value (&language-> value) : DEFAULT_LANGUAGE,
        850
    );

    result-> value. type = TYPE_STRING;
    result-> value. s    = mem_strdup (buffer);
  }

    return 0;
}

static int
eval_string_replace (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *strbuf  = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *strpattern = argc > 1 ? argv [1] : NULL;

    if (strbuf && (strbuf-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = strbuf-> culprit;
        return 0;
      }
    if (strpattern && (strpattern-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = strpattern-> culprit;
        return 0;
      }

  {
    char
        *original,
        *copy;
    size_t
        max_length;

    original = string_value (&strbuf->value);
    max_length = strlen (original) * 4;    //  Some random factor
    copy = mem_alloc (max_length + 1);
    strcpy (copy, original);

    stringreplace (copy, string_value (&strpattern->value), max_length);
    result-> value. s    = copy;
    result-> value. type = TYPE_STRING;
  }

    return 0;
}

static int
eval_string_match (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *string1 = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *string2 = argc > 1 ? argv [1] : NULL;

    if (string1 && (string1-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string1-> culprit;
        return 0;
      }
    if (string2 && (string2-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string2-> culprit;
        return 0;
      }

  {
    result-> value. n = strmatch (string_value (&string1-> value),
                                     string_value (&string2-> value));
    result-> value. type = TYPE_NUMBER;
  }

    return 0;
}

static int
eval_string_prefixed (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *string  = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *prefix  = argc > 1 ? argv [1] : NULL;

    if (string && (string-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string-> culprit;
        return 0;
      }
    if (prefix && (prefix-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = prefix-> culprit;
        return 0;
      }

  {
    result-> value. n = strprefixed (string_value (&string-> value),
                                        string_value (&prefix-> value));
    result-> value. type = TYPE_NUMBER;
  }

    return 0;
}

static int
eval_string_prefix (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *string  = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *delims  = argc > 1 ? argv [1] : NULL;

    if (string && (string-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string-> culprit;
        return 0;
      }
    if (delims && (delims-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = delims-> culprit;
        return 0;
      }

  {
    char
        *strptr = strprefix (string_value (&string-> value),
                             string_value (&delims-> value));
                             
    result-> value. s    = strptr;
    result-> value. type = TYPE_STRING;
  }

    return 0;
}

static int
eval_string_defix (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *string  = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *delims  = argc > 1 ? argv [1] : NULL;

    if (string && (string-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string-> culprit;
        return 0;
      }
    if (delims && (delims-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = delims-> culprit;
        return 0;
      }

  {
    char
        *strptr = strprefix (string_value (&string-> value),
                             string_value (&delims-> value));
    if (strptr)
        result-> value. s = mem_strdup (string_value (&string-> value) + strlen (strptr) + 1);
    else 
        result-> value. s = mem_strdup (string_value (&string-> value));

    result-> value. type = TYPE_STRING;
    mem_strfree (&strptr);
  }

    return 0;
}

static int
eval_string_hash (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *string  = argc > 0 ? argv [0] : NULL;

    if (string && (string-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string-> culprit;
        return 0;
      }

  {
    result-> value. n = strhash (string_value (&string-> value));
    result-> value. type = TYPE_NUMBER;
  }

    return 0;
}

static int
eval_string_convch (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *string  = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *from    = argc > 1 ? argv [1] : NULL;
    RESULT_NODE *to      = argc > 2 ? argv [2] : NULL;

    if (string && (string-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string-> culprit;
        return 0;
      }
    if (from && (from-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = from-> culprit;
        return 0;
      }
    if (to && (to-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = to-> culprit;
        return 0;
      }

  {
    char
        *strptr = strconvch (string_value (&string-> value),
                            *string_value (&from  -> value),
                            *string_value (&to    -> value));
    result-> value. s    = mem_strdup (strptr);
    result-> value. type = TYPE_STRING;
  }

    return 0;
}

static int
eval_string_lexcmp (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *string1 = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *string2 = argc > 1 ? argv [1] : NULL;

    if (string1 && (string1-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string1-> culprit;
        return 0;
      }
    if (string2 && (string2-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string2-> culprit;
        return 0;
      }

  {
    result-> value. n = lexcmp (string_value (&string1-> value),
                                   string_value (&string2-> value));
    result-> value. type = TYPE_NUMBER;
  }

    return 0;
}

static int
eval_string_lexncmp (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *string1 = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *string2 = argc > 1 ? argv [1] : NULL;
    RESULT_NODE *count   = argc > 2 ? argv [2] : NULL;

    if (string1 && (string1-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string1-> culprit;
        return 0;
      }
    if (string2 && (string2-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string2-> culprit;
        return 0;
      }
    if (count && (count-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = count-> culprit;
        return 0;
      }

  {
    result-> value. n = lexncmp (string_value (&string1-> value),
                                 string_value (&string2-> value),
                           (int) number_value (&count  -> value));
    result-> value. type = TYPE_NUMBER;
  }

    return 0;
}

static int
eval_string_lexwcmp (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *string1 = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *pattern = argc > 1 ? argv [1] : NULL;

    if (string1 && (string1-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string1-> culprit;
        return 0;
      }
    if (pattern && (pattern-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = pattern-> culprit;
        return 0;
      }

  {
    result-> value. n = lexwcmp (string_value (&string1-> value),
                                    string_value (&pattern-> value));
    result-> value. type = TYPE_NUMBER;
  }

    return 0;
}

static int
eval_string_matchpat (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *string1 = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *pattern = argc > 1 ? argv [1] : NULL;
    RESULT_NODE *ic      = argc > 2 ? argv [2] : NULL;

    if (string1 && (string1-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string1-> culprit;
        return 0;
      }
    if (pattern && (pattern-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = pattern-> culprit;
        return 0;
      }

  {
    Bool
        ignore_case;
        
    if (ic)
        ignore_case = (Bool) number_value (&ic-> value);
    else
        ignore_case = 0;                /*  If mode unspecified, use FALSE   */

    result-> value. n = match_pattern (string_value (&string1-> value),
                                          string_value (&pattern-> value),
                                          ignore_case);
    result-> value. type = TYPE_NUMBER;
  }

    return 0;
}

static int
eval_string_soundex (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *string  = argc > 0 ? argv [0] : NULL;

    if (string && (string-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string-> culprit;
        return 0;
      }

  {
    char
        *strptr = soundex (string_value (&string-> value));
    result-> value. s    = mem_strdup (strptr);
    result-> value. type = TYPE_STRING;
  }

    return 0;
}

static int
eval_string_cntch (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *string  = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *value   = argc > 1 ? argv [1] : NULL;

    if (string && (string-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string-> culprit;
        return 0;
      }
    if (value && (value-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = value-> culprit;
        return 0;
      }

  {
    result-> value. n = strcntch (string_value (&string-> value),
                                    *string_value (&value -> value));
    result-> value. type = TYPE_NUMBER;
  }

    return 0;
}

static int
eval_string_xml (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *scope   = argc > 0 ? argv [0] : NULL;


{
    XML_ITEM
        *xml_scope;
    GGCODE_TCB
        *tcb;                           /*  Thread control block             */
    char
        *error_text;

    tcb = gsl_thread-> tcb;
    xml_scope = extended_scope_xml (&tcb-> scope_stack,
                                    scope ? scope-> scope : NULL,
                                    tcb-> ignorecase,
                                    &error_text);
    if (xml_scope) {
        result-> value.s    = xml_save_string (xml_scope);
        result-> value.type = TYPE_STRING;
    }
    else {
        strcpy (object_error, error_text);
        return -1;
    }
}

    return 0;
}

static int
eval_string_html_encode (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *string  = argc > 0 ? argv [0] : NULL;

    if (string && (string-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string-> culprit;
        return 0;
      }

{
    char
        *encoded,
        *encptr;
    size_t
        encmax;
    encmax  = strlen (string_value (&string-> value)) * 2;
    encoded = mem_alloc (encmax);
    encptr  = string_value (&string-> value);
    http_encode_meta (encoded, &encptr, encmax, FALSE);
    result-> value.s    = encoded;
    result-> value.type = TYPE_STRING;
}

    return 0;
}

static int
eval_string_html_decode (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *string  = argc > 0 ? argv [0] : NULL;

    if (string && (string-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = string-> culprit;
        return 0;
      }

{
    char
        *decoded,
        *decptr;
    size_t
        decmax;
    decmax  = strlen (string_value (&string-> value));
    decoded = mem_alloc (decmax);
    decptr  = string_value (&string-> value);
    http_decode_meta (decoded, &decptr, decmax);
    result-> value.s    = decoded;
    result-> value.type = TYPE_STRING;
}

    return 0;
}


