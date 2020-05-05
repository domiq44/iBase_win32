/*---------------------------------------------------------------------------
 *  ggmath.c - GSL/math package
 *
 *  Generated on 2010/10/06, 19:32:56 from ggmath
 *  by ggobjt.gsl using GSLgen.
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/

#include "ggpriv.h"                     /*  Project header file              */
#include "ggmath.h"                     /*  Include header file              */


/*- Macros ------------------------------------------------------------------*/

#define MATH_NAME "math"                /*  Math Functions                   */

/*- Function prototypes -----------------------------------------------------*/

static EVAL_FUNCTION eval_math_abs;
static EVAL_FUNCTION eval_math_ceil;
static EVAL_FUNCTION eval_math_floor;
static EVAL_FUNCTION eval_math_mod;
static EVAL_FUNCTION eval_math_rand;
static EVAL_FUNCTION eval_math_sqrt;
static EVAL_FUNCTION eval_math_exp;
static EVAL_FUNCTION eval_math_log;
static EVAL_FUNCTION eval_math_log10;
static EVAL_FUNCTION eval_math_pow;
static EVAL_FUNCTION eval_math_sin;
static EVAL_FUNCTION eval_math_cos;
static EVAL_FUNCTION eval_math_tan;
static EVAL_FUNCTION eval_math_sinh;
static EVAL_FUNCTION eval_math_cosh;
static EVAL_FUNCTION eval_math_tanh;
static EVAL_FUNCTION eval_math_asin;
static EVAL_FUNCTION eval_math_acos;
static EVAL_FUNCTION eval_math_atan;
static EVAL_FUNCTION eval_math_atan2;
static EVAL_FUNCTION eval_math_pi;
static EVAL_FUNCTION eval_math_asinh;
static EVAL_FUNCTION eval_math_acosh;
static EVAL_FUNCTION eval_math_atanh;

/*- Global variables --------------------------------------------------------*/

static PARM_LIST parm_list_v            = { PARM_VALUE };

static GSL_FUNCTION math_functions [] = 
{
    {"abs",         0, 1, 1, (void *) &parm_list_v, 1, eval_math_abs},
    {"acos",        0, 1, 1, (void *) &parm_list_v, 1, eval_math_acos},
    {"acosh",       0, 1, 1, (void *) &parm_list_v, 1, eval_math_acosh},
    {"asin",        0, 1, 1, (void *) &parm_list_v, 1, eval_math_asin},
    {"asinh",       0, 1, 1, (void *) &parm_list_v, 1, eval_math_asinh},
    {"atan",        0, 1, 1, (void *) &parm_list_v, 1, eval_math_atan},
    {"atan2",       0, 2, 1, (void *) &parm_list_v, 1, eval_math_atan2},
    {"atanh",       0, 1, 1, (void *) &parm_list_v, 1, eval_math_atanh},
    {"ceil",        0, 1, 1, (void *) &parm_list_v, 1, eval_math_ceil},
    {"cos",         0, 1, 1, (void *) &parm_list_v, 1, eval_math_cos},
    {"cosh",        0, 1, 1, (void *) &parm_list_v, 1, eval_math_cosh},
    {"exp",         0, 1, 1, (void *) &parm_list_v, 1, eval_math_exp},
    {"floor",       0, 1, 1, (void *) &parm_list_v, 1, eval_math_floor},
    {"log",         0, 1, 1, (void *) &parm_list_v, 1, eval_math_log},
    {"log10",       0, 1, 1, (void *) &parm_list_v, 1, eval_math_log10},
    {"mod",         0, 2, 1, (void *) &parm_list_v, 1, eval_math_mod},
    {"pi",          0, 0, 0, (void *) &parm_list_v, 1, eval_math_pi},
    {"pow",         0, 2, 1, (void *) &parm_list_v, 1, eval_math_pow},
    {"rand",        0, 0, 0, (void *) &parm_list_v, 1, eval_math_rand},
    {"sin",         0, 1, 1, (void *) &parm_list_v, 1, eval_math_sin},
    {"sinh",        0, 1, 1, (void *) &parm_list_v, 1, eval_math_sinh},
    {"sqrt",        0, 1, 1, (void *) &parm_list_v, 1, eval_math_sqrt},
    {"tan",         0, 1, 1, (void *) &parm_list_v, 1, eval_math_tan},
    {"tanh",        0, 1, 1, (void *) &parm_list_v, 1, eval_math_tanh}
};

/*- Functions for object "math" - Math Functions                             */

int register_math_functions (void)
{
    return object_register (MATH_NAME,
                            math_functions,
                            tblsize (math_functions),
                            NULL);
}

static int
eval_math_abs (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *parm    = argc > 0 ? argv [0] : NULL;


  {
    number_value (&parm-> value);

    if (parm-> value. type == TYPE_NUMBER)
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = fabs (parm-> value. n);
      }
    return 0;
  }

    return 0;
}

static int
eval_math_ceil (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *parm    = argc > 0 ? argv [0] : NULL;


  {
    number_value (&parm-> value);

    if (parm-> value. type == TYPE_NUMBER)
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = ceil (parm-> value. n);
      }
    return 0;
  }

    return 0;
}

static int
eval_math_floor (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *parm    = argc > 0 ? argv [0] : NULL;


  {
    number_value (&parm-> value);

    if (parm-> value. type == TYPE_NUMBER)
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = floor (parm-> value. n);
      }
    return 0;
  }

    return 0;
}

static int
eval_math_mod (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *x       = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *y       = argc > 1 ? argv [1] : NULL;


  {
    number_value (&x-> value);
    number_value (&y-> value);

    if ((x-> value. type == TYPE_NUMBER)
    && (y-> value. type == TYPE_NUMBER)
    && (y-> value. n))
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = fmod (number_value (&x-> value),
                                     number_value (&y-> value));
      }
    return 0;
  }

    return 0;
}

static int
eval_math_rand (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{


  {
    static Bool
        first_time = TRUE;
  
    if (first_time)
      {
        srand (micro_time ());
        first_time = FALSE;
      }
    result-> value. type = TYPE_NUMBER;
    result-> value. n    = (double) rand () / RAND_MAX;
  }

    return 0;
}

static int
eval_math_sqrt (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *parm    = argc > 0 ? argv [0] : NULL;


  {
    number_value (&parm-> value);

    if ((parm-> value. type == TYPE_NUMBER)
    && (parm-> value. n >= 0))
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = sqrt (parm-> value. n);
      }
    return 0;
  }

    return 0;
}

static int
eval_math_exp (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *parm    = argc > 0 ? argv [0] : NULL;


  {
    number_value (&parm-> value);

    if (parm-> value. type == TYPE_NUMBER)
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = exp (parm-> value. n);
      }
    return 0;
  }

    return 0;
}

static int
eval_math_log (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *parm    = argc > 0 ? argv [0] : NULL;


  {
    number_value (&parm-> value);

    if ((parm-> value. type == TYPE_NUMBER)
    && (parm-> value.n > 0))
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = log (parm-> value. n);
      }
    return 0;
  }

    return 0;
}

static int
eval_math_log10 (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *parm    = argc > 0 ? argv [0] : NULL;


  {
    number_value (&parm-> value);

    if ((parm-> value. type == TYPE_NUMBER)
    && (parm-> value.n > 0))
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = log10 (parm-> value. n);
      }
    return 0;
  }

    return 0;
}

static int
eval_math_pow (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *x       = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *y       = argc > 1 ? argv [1] : NULL;


  {
    number_value (&x-> value);
    number_value (&y-> value);

    if ((x-> value. type == TYPE_NUMBER)
    && (y-> value. type == TYPE_NUMBER))
      {
        if (((x-> value.n != 0)
        ||   (y-> value.n > 0))
        && ((x-> value.n >= 0)
        ||   (y-> value.n == floor (y-> value.n))))
          {
            result-> value. type = TYPE_NUMBER;
            result-> value. n    = pow (number_value (&x-> value),
                                           number_value (&y-> value));
          }
      }
    return 0;
  }

    return 0;
}

static int
eval_math_sin (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *parm    = argc > 0 ? argv [0] : NULL;


  {
    number_value (&parm-> value);

    if (parm-> value. type == TYPE_NUMBER)
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = sin (parm-> value. n);
      }
    return 0;
  }

    return 0;
}

static int
eval_math_cos (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *parm    = argc > 0 ? argv [0] : NULL;


  {
    number_value (&parm-> value);

    if (parm-> value. type == TYPE_NUMBER)
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = cos (parm-> value. n);
      }
    return 0;
  }

    return 0;
}

static int
eval_math_tan (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *parm    = argc > 0 ? argv [0] : NULL;


  {
    number_value (&parm-> value);

    if (parm-> value. type == TYPE_NUMBER)
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = tan (parm-> value. n);
      }
    return 0;
  }

    return 0;
}

static int
eval_math_sinh (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *parm    = argc > 0 ? argv [0] : NULL;


  {
    number_value (&parm-> value);

    if (parm-> value. type == TYPE_NUMBER)
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = sinh (parm-> value. n);
      }
    return 0;
  }

    return 0;
}

static int
eval_math_cosh (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *parm    = argc > 0 ? argv [0] : NULL;


  {
    number_value (&parm-> value);

    if (parm-> value. type == TYPE_NUMBER)
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = cosh (parm-> value. n);
      }
    return 0;
  }

    return 0;
}

static int
eval_math_tanh (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *parm    = argc > 0 ? argv [0] : NULL;


  {
    number_value (&parm-> value);

    if (parm-> value. type == TYPE_NUMBER)
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = tanh (parm-> value. n);
      }
    return 0;
  }

    return 0;
}

static int
eval_math_asin (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *parm    = argc > 0 ? argv [0] : NULL;


  {
    number_value (&parm-> value);

    if ((parm-> value. type == TYPE_NUMBER)
    && (parm-> value. n >= -1)
    && (parm-> value. n <=  1))
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = asin (parm-> value. n);
      }
    return 0;
  }

    return 0;
}

static int
eval_math_acos (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *parm    = argc > 0 ? argv [0] : NULL;


  {
    number_value (&parm-> value);

    if ((parm-> value. type == TYPE_NUMBER)
    && (parm-> value. n >= -1)
    && (parm-> value. n <=  1))
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = acos (parm-> value. n);
      }
    return 0;
  }

    return 0;
}

static int
eval_math_atan (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *parm    = argc > 0 ? argv [0] : NULL;


  {
    number_value (&parm-> value);

    if (parm-> value. type == TYPE_NUMBER)
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = atan (parm-> value. n);
      }
    return 0;
  }

    return 0;
}

static int
eval_math_atan2 (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *x       = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *y       = argc > 1 ? argv [1] : NULL;


  {
    number_value (&x-> value);
    number_value (&y-> value);

    if ((x-> value. type == TYPE_NUMBER)
    && (y-> value. type == TYPE_NUMBER))
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = atan2 (x-> value. n, y-> value. n);
      }
    return 0;
  }

    return 0;
}

static int
eval_math_pi (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{


  {
    result-> value. type = TYPE_NUMBER;
    result-> value. n    = atan (1) * 4;
    
    return 0;
  }

    return 0;
}

static int
eval_math_asinh (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *parm    = argc > 0 ? argv [0] : NULL;


  {
    number_value (&parm-> value);

    if (parm-> value. type == TYPE_NUMBER)
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = -log (
            sqrt (parm-> value. n * parm-> value. n + 1)
            - parm-> value. n
        );
      }
    return 0;
  }

    return 0;
}

static int
eval_math_acosh (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *parm    = argc > 0 ? argv [0] : NULL;


  {
    number_value (&parm-> value);

    if ((parm-> value. type == TYPE_NUMBER)
    && (parm-> value. n >= 1))
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = log (
            sqrt (parm-> value. n * parm-> value. n - 1)
            + parm-> value. n
        );
      }
    return 0;
  }

    return 0;
}

static int
eval_math_atanh (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *parm    = argc > 0 ? argv [0] : NULL;


  {
    number_value (&parm-> value);

    if ((parm-> value. type == TYPE_NUMBER)
    && (parm-> value. n < 1))
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = log (
            (1 + parm-> value. n) /
            (1 - parm-> value. n)
        ) / 2;
      }
    return 0;
  }

    return 0;
}


