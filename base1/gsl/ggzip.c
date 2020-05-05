/*---------------------------------------------------------------------------
 *  ggzip.c - GSL/zip package
 *
 *  Generated on 2010/10/06, 19:32:56 from ggzip
 *  by ggobjt.gsl using GSLgen.
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/

#include "ggpriv.h"                     /*  Project header file              */
#include "ggzip.h"                      /*  Include header file              */


/*- Macros ------------------------------------------------------------------*/

#define ZIP_NAME "zip"                  /*  Zip Functions                    */

/*- Function prototypes -----------------------------------------------------*/

static EVAL_FUNCTION eval_zip_extract;
static EVAL_FUNCTION eval_zip_load;
static EVAL_FUNCTION eval_zip_create;
static EVAL_FUNCTION eval_zip_new;
static EVAL_FUNCTION eval_zip_open;
static EVAL_FUNCTION eval_zip_close;
static EVAL_FUNCTION eval_zip_add;

/*- Global variables --------------------------------------------------------*/

static PARM_LIST parm_list_v            = { PARM_VALUE };
static PARM_LIST parm_list_xv           = { PARM_EXTENDED_SCOPE,
                                            PARM_VALUE };

static GSL_FUNCTION zip_functions [] = 
{
    {"add",         2, 3, 1, (void *) &parm_list_v, 1, eval_zip_add},
    {"close",       1, 1, 1, (void *) &parm_list_v, 1, eval_zip_close},
    {"create",      0, 3, 2, (void *) &parm_list_xv, 1, eval_zip_create},
    {"extract",     1, 2, 1, (void *) &parm_list_v, 1, eval_zip_extract},
    {"load",        0, 2, 2, (void *) &parm_list_xv, 1, eval_zip_load},
    {"new",         1, 1, 1, (void *) &parm_list_v, 1, eval_zip_new},
    {"open",        1, 1, 1, (void *) &parm_list_v, 1, eval_zip_open}
};

#include "zip.h"
#include "unzip.h"

#define CASESENSITIVITY (0)
#define WRITEBUFFERSIZE (8192)

#define MAX_ZIPFILES 16
static unzFile
    *zipfile_ptr [MAX_ZIPFILES];

static int
    fileerrno;

static zipFile      zip_new                 (const char *zipfile);
static zipFile      zip_open                (const char *zipfile);
static zip_fileinfo zip_get_file_date_time  (const char *file);
static int          zip_close               (zipFile zf);
static int          zip_add                 (zipFile zf, const char *file, int compress_level);
static int          zip_extract_currentfile (unzFile uf, const char *outdir);
static int          zip_extract             (unzFile uf, const char *outdir);
static uLong        dosDate_to_date         (uLong dosDate);
static uLong        dosDate_to_time         (uLong dosDate);


/* ------------------------------  zip_new   ----------------------------- */

static zipFile
zip_new (const char *zipfile)
{
    ASSERT (zipfile);
    /*  append = 0  ==>  "wb" */
    return (zipOpen (zipfile, 0));
}


/* ------------------------------  zip_open   ----------------------------- */

static zipFile
zip_open (const char *zipfile)
{
    ASSERT (zipfile);
    /*  append = 1  ==>  "ab" */
    return (zipOpen (zipfile, 1));
}


/* -----------------------------  zip_close  ----------------------------- */

static int
zip_close (zipFile zf)
{
    if (zf)
        return (zipClose (zf, NULL));
    else
        return (0);
}


/* ----------------------  zip_get_file_date_time  ----------------------- */

static zip_fileinfo
zip_get_file_date_time (const char *file)
{
    zip_fileinfo
        zi;
    time_t
        filetime;
    struct tm
        *file_time;

    zi.dosDate = 0;
    zi.internal_fa = 0;
    zi.external_fa = 0;

    zi.tmz_date.tm_sec  = 0;
    zi.tmz_date.tm_min  = 0;
    zi.tmz_date.tm_hour = 0;
    zi.tmz_date.tm_mday = 0;
    zi.tmz_date.tm_min  = 0;
    zi.tmz_date.tm_year = 0;

    filetime = get_file_time (file);
    file_time = safe_localtime (&filetime);
    
    zi.tmz_date.tm_sec  = file_time-> tm_sec;
    zi.tmz_date.tm_min  = file_time-> tm_min;
    zi.tmz_date.tm_hour = file_time-> tm_hour;
    zi.tmz_date.tm_mday = file_time-> tm_mday;
    zi.tmz_date.tm_mon  = file_time-> tm_mon;
    zi.tmz_date.tm_year = file_time-> tm_year;
    
    return (zi);
}

/* ------------------------------  zip_add  ------------------------------ */

static int
zip_add (zipFile zf, const char *file, int compress_level)
{
    FILE
        *f_in = NULL;
    int
        err,
        size_buf = 0,
        size_read;
    void
        *buf = NULL;
    zip_fileinfo
        zi;

    zi = zip_get_file_date_time (file);

    err = zipOpenNewFileInZip (
        zf,
        file,
        &zi,
        NULL,
        0,
        NULL,
        0,
        NULL /* comment*/,
        (compress_level != 0) ? Z_DEFLATED : 0,
        compress_level
    );
    if (err != ZIP_OK)
      {
        sprintf (object_error, "error in opening %s in zipfile", file);
        return -1;
      }

    f_in = fopen (file, "rb");
    if (f_in == NULL)
      {
        sprintf (object_error, "error in opening %s for reading", file);
        return -1;
      }

    size_buf = WRITEBUFFERSIZE;
    buf = (void *) malloc (size_buf);
    if (buf == NULL)
      {
        strcpy (object_error, "Error allocating memory");
        return -1;
      }

    do
      {
        err = ZIP_OK;
        size_read = fread (buf, 1, size_buf, f_in);
        if (size_read < size_buf)
            if (feof (f_in) == 0)
              {
                sprintf (object_error, "error in reading %s", file);
                free (buf);
                return -1;
              }

        if (size_read > 0)
          {
            err = zipWriteInFileInZip (zf, buf, size_read);
            if (err < 0)
              {
                sprintf (object_error, "error in writing %s in the zipfile", file);
                free (buf);
                return -1;
              }
            
          }
      }
    while ((err == ZIP_OK) &&(size_read > 0));

    free (buf);

    if (f_in)
        fclose (f_in);

    if (err < 0)
      {
        err = ZIP_ERRNO;
        return -1;
      }

    err = zipCloseFileInZip (zf);
    if (err != ZIP_OK)
      {
        sprintf (object_error, "error in closing %s in the zipfile", file);
        return -1;
      }

    return err;
}

static uLong
dosDate_to_date (uLong dosDate)
{
    uLong
        uDate;
    uInt
        year,
        mon,
        mday;

    uDate = (uLong) (dosDate >> 16);

    year = (uInt) (((uDate &0x0FE00) / 0x0200) + 1980);
    mon  = (uInt) (((uDate &0x1E0  ) / 0x20)   - 1);
    mday = (uInt)   (uDate &0x1f   );

    return (MAKE_DATE (year / 100, year % 100, mon + 1, mday));
}

static uLong
dosDate_to_time (uLong dosDate)
{
    uInt
        hour,
        min,
        sec;

    hour = (uInt) ((dosDate &0xF800) / 0x800);
    min  = (uInt) ((dosDate &0x7E0 ) / 0x20 );
    sec  = (uInt) ((dosDate &0x1f  ) * 2    );

    return (MAKE_TIME (hour, min, sec, 0));
}


/* ----------------------  zip_extract_currentfile  ---------------------- */

static int
zip_extract_currentfile (unzFile uf, const char *outdir)
{
    char
        filename_inzip [256],
        filename [256],
        *file_name,
        *directory,
        *old_dir;
    int
        err = UNZ_OK;
    FILE
        *f_out = NULL;
    void
        *buf;
    uInt
        size_buf;
    unz_file_info
        file_info;
        
    err = unzGetCurrentFileInfo (
        uf,
        &file_info,
        filename_inzip,
        sizeof (filename_inzip),
        NULL,
        0,
        NULL,
        0
    );
    if (err != UNZ_OK)
      {
        sprintf (object_error, "Error %d with zipfile in unzGetCurrentFileInfo", err);
        return -1;
      }

    if (! file_exists (outdir))
        make_dir (outdir);

    old_dir = get_curdir ();

    if (! file_is_directory (outdir))
      {
        sprintf (object_error, "Error: %s is not a directory", outdir);
        mem_free (old_dir);
        return -1;
      }

    set_curdir (outdir);

    strcpy (filename, filename_inzip);

    directory = strip_file_name (filename_inzip);
    file_name = strip_file_path (filename_inzip);

    if (strcmp (file_name, "") == 0)    /*  it's just a directory name */
      {
        make_dir (directory);
        mem_free (old_dir);
        return 0;
      }

    err = unzOpenCurrentFile (uf);
    if (err != UNZ_OK)
      {
        sprintf (object_error, "Error %d with zipfile in unzOpenCurrentFile", err);
        mem_free (old_dir);
        return -1;
      }

    /*  some zipfile don't contain directory alone before file */
    if (lexcmp (directory, ".") != 0)
        make_dir (directory);

    f_out = fopen (filename, "wb");
    if (f_out == NULL)
      {
        sprintf (object_error, "Error opening %s", file_name);
        mem_free (old_dir);
        return -1;
      }

    size_buf = WRITEBUFFERSIZE;
    buf = (void *) malloc (size_buf);
    if (buf == NULL)
      {
        strcpy (object_error, "Error allocating memory");
        fclose (f_out);
        mem_free (old_dir);
        return -1;
      }

    do
      {
        err = unzReadCurrentFile (uf, buf, size_buf);
        if (err < 0)    
          {
            sprintf (object_error, "Error %d with zipfile in unzReadCurrentFile", err);
            fclose (f_out);
            free (buf);    
            mem_free (old_dir);
            return -1;
          }
        if (err > 0)
            if (fwrite (buf, err, 1, f_out) != 1)
              {
                strcpy (object_error, "Error in writing extracted file");
                fclose (f_out);
                free (buf);    
                mem_free (old_dir);
                return -1;
              }
      }
    while (err > 0);

    fclose (f_out);

    set_file_time (filename,
        dosDate_to_date (file_info.dosDate),
        dosDate_to_time (file_info.dosDate)
    );

    err = unzCloseCurrentFile (uf);
    if (err != UNZ_OK)
      {
        sprintf (object_error, "Error %d with zipfile in unzCloseCurrentFile", err);
        free (buf);    
        set_curdir (old_dir);
        mem_free (old_dir);
        return -1;
      }

    unzCloseCurrentFile (uf);   /* don't lose the error */       
    free (buf);    
    set_curdir (old_dir);
    mem_free (old_dir);
    return 0;
}


/* ----------------------------  zip_extract  ---------------------------- */

static int
zip_extract (unzFile uf, const char *outdir)
{
    uLong
        i;
    unz_global_info
        gi;
    int
        err;

    err = unzGetGlobalInfo (uf, &gi);
    if (err != UNZ_OK)
      {
        sprintf (object_error, "Error %d with zipfile in unzGetGlobalInfo", err);
        return -1;
      }

    for (i = 0; i < gi.number_entry; i++)
      {
        if (zip_extract_currentfile (uf, outdir) != UNZ_OK)
            break;

        if ((i + 1) < gi.number_entry)
          {
            err = unzGoToNextFile (uf);
            if (err != UNZ_OK)
              {
                sprintf (object_error, "Error %d with zipfile in unzGoToNextFile", err);
                return -1;
              }
          }
      }

    return 0;
}

/*- Functions for object "zip" - Zip Functions                               */

int register_zip_functions (void)
{
    return object_register (ZIP_NAME,
                            zip_functions,
                            tblsize (zip_functions),
                            NULL);
}

static int
eval_zip_extract (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *zipfilename = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *directory = argc > 1 ? argv [1] : NULL;

    if (zipfilename && (zipfilename-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = zipfilename-> culprit;
        return 0;
      }

  {
    unzFile
        uf = NULL;
    char
        *filename;

    filename = file_where (
        'r',
        env_get_string ("PATH", ""),
        string_value (&zipfilename-> value),
        ""
    );
    if (filename)
        uf = unzOpen (filename);

    if (uf == NULL)
      {
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = -1;
      }

    result-> value. type = TYPE_NUMBER;
    result-> value. n    = zip_extract (
        uf, 
        directory? string_value (&directory-> value): "."
    );
}

    return 0;
}

static int
eval_zip_load (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *scope   = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *zip     = argc > 1 ? argv [1] : NULL;


  {
    GGCODE_TCB
        *tcb = gsl_thread-> tcb;
    char
        *error_text,
        file [256],
        *zipfile;
    unzFile
        uf = NULL;
    unz_file_info
        file_info;
    int
        zip_rc;
    XML_ITEM
        *xml_parent,
        *xml_item;
    char
        char9 [9],
        *directory,
        *file_name;

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

    result-> value. type = TYPE_NUMBER;
    result-> value. n = 0;

    zipfile = file_where ('r', env_get_string ("PATH", ""),
                           string_value (&zip-> value), "");
    if (zipfile)
        uf = unzOpen (zipfile);
        
    if (uf == NULL)
      {
        sprintf (object_error, "Cannot open : %s",
                                string_value (&zip-> value));
        return -1;
      }
        
    zip_rc = UNZ_OK;
    while (zip_rc == UNZ_OK)
      {
        uLong
            ratio;
        const char
            *string_method =  NULL;

        zip_rc = unzGetCurrentFileInfo (uf, &file_info, file, sizeof (file),
                                        NULL, 0, NULL, 0);

        directory = strip_file_name (file);
        file_name = strip_file_path (file);

        result-> value. n++;

        if (file_info. uncompressed_size > 0)
            ratio = (file_info. compressed_size * 100) / file_info. uncompressed_size;
        else
            ratio = 0;

        if (file_info. compression_method == 0)
            string_method = "Stored";
        else if (file_info. compression_method == Z_DEFLATED)
          {
            uInt
                iLevel = (uInt) ((file_info. flag &0x6) / 2);
            if (iLevel == 0)
                string_method = "Defl:N";
            else if (iLevel == 1)
                string_method = "Defl:X";
            else if ((iLevel == 2) || (iLevel == 3))
                string_method = "Defl:F";   /*  2:fast, 3:extra fast */
          }
        else
            string_method = "Unkn. ";

        xml_item = xml_new (xml_parent, "file", NULL);
        xml_put_attr (xml_item, "name", file_name);
        xml_put_attr (xml_item, "path", directory);
        xml_put_attr (xml_item, "length", strprintf ("%lu", file_info. uncompressed_size));
        xml_put_attr (xml_item, "method", string_method);
        xml_put_attr (xml_item, "size", strprintf ("%lu", file_info. compressed_size));
        xml_put_attr (xml_item, "ratio", strprintf ("%lu", ratio));
        sprintf (char9, "%4.4lu%2.2lu%2.2lu",
            (uLong) file_info. tmu_date. tm_year,
            (uLong) file_info. tmu_date. tm_mon + 1,
            (uLong) file_info. tmu_date. tm_mday);
        xml_put_attr (xml_item, "date", char9);
        sprintf (char9, "%2.2lu%2.2lu%2.2lu%2.2lu",
            (uLong) file_info. tmu_date. tm_hour,
            (uLong) file_info. tmu_date. tm_min,
            (uLong) file_info. tmu_date. tm_sec,
            (uLong) 0);
        xml_put_attr (xml_item, "time", char9);
        xml_put_attr (xml_item, "crc", strprintf ("%lx", (uLong) file_info. crc));

        zip_rc = unzGoToNextFile (uf);
      }

    zip_rc = unzClose (uf);
}

    return 0;
}

static int
eval_zip_create (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *scope   = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *zip     = argc > 1 ? argv [1] : NULL;
    RESULT_NODE *cl      = argc > 2 ? argv [2] : NULL;


  {
    GGCODE_TCB
        *tcb = gsl_thread-> tcb;
    int
        err,
        count;
    char
        *error_text,
        *file_path,
        *file_name;
    XML_ITEM
        *xml_parent,
        *xml_child;
    static char
        filename [1024];
    zipFile
        zf;

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

    result-> value. type = TYPE_NUMBER;
    result-> value. n = 0;

    zf = zip_new (string_value (&zip-> value));
    count = 0;

    xml_child = xml_first_child (xml_parent);
    while (xml_child)
      {
        if (streq (xml_item_name (xml_child), "file")
        && streq (xml_get_attr_ic (xml_child, "directory", "0", 1), "0"))
          {
            file_name = xml_get_attr_ic (xml_child, "name", NULL, 1);
            file_path = xml_get_attr_ic (xml_child, "path", NULL, 1);

            if (lexcmp (".", file_path) != 0)
                strcpy (filename, file_path);
            else
                strcpy (filename, "");

            strcat (filename, file_name);

            err = zip_add (
                zf,
                filename,
                cl? (int) number_value (&cl-> value): Z_DEFAULT_COMPRESSION
            );
            count++;
          }
        xml_child = xml_next_sibling (xml_child);
      }

    zip_close (zf);

    result-> value. type = TYPE_NUMBER;
    result-> value. n    = count;
  }

    return 0;
}

static int
eval_zip_new (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *zip     = argc > 0 ? argv [0] : NULL;

    if (zip && (zip-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = zip-> culprit;
        return 0;
      }

  {
    zipFile
        zf = NULL;
    int
        handle;

    /*  Find a free handle.  */
    for (handle = 0; handle < MAX_ZIPFILES; handle++)
        if (zipfile_ptr [handle] == NULL)
            break;

    if (handle >= MAX_ZIPFILES)
      {
        fileerrno = EMFILE;             /*  Too many open files.             */
        return 0;                       /*  GSL function returns undefined.  */
      }

    zf = zip_new (string_value (&zip-> value));
    if (zf != NULL)
      {
        zipfile_ptr [handle]    = zf;
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = handle;
      }
    else
        fileerrno = errno;
  }

    return 0;
}

static int
eval_zip_open (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *zip     = argc > 0 ? argv [0] : NULL;

    if (zip && (zip-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = zip-> culprit;
        return 0;
      }

  {
    char
        *filename;
    zipFile
        zf = NULL;
    int
        handle;

    /*  Find a free handle.  */
    for (handle = 0; handle < MAX_ZIPFILES; handle++)
        if (zipfile_ptr [handle] == NULL)
            break;

    if (handle >= MAX_ZIPFILES)
      {
        fileerrno = EMFILE;             /*  Too many open files.             */
        return (0);                     /*  GSL function returns undefined.  */
      }

    filename = file_where (
        'r',
        env_get_string ("PATH", ""),
        string_value (&zip-> value),
        ""
    );

    if (filename)
        zf = zip_open (filename);
        
    if (zf != NULL)
      {
        zipfile_ptr [handle]    = zf;
        result-> value. type = TYPE_NUMBER;
        result-> value. n    = handle;
      }
    else
        fileerrno = errno;
  }

    return 0;
}

static int
eval_zip_close (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
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

    if ((handle_n < 0 || handle_n > MAX_ZIPFILES)
    ||  (! zipfile_ptr [handle_n]))
        return 0;
        
    result-> value. type = TYPE_NUMBER;
    result-> value. n    = zip_close (zipfile_ptr [handle_n]);

    if (result-> value. n == -1)
        fileerrno = errno;
  }

    return 0;
}

static int
eval_zip_add (int argc, RESULT_NODE **argv, RESULT_NODE *result, THREAD *gsl_thread)
{
    RESULT_NODE *handle  = argc > 0 ? argv [0] : NULL;
    RESULT_NODE *file    = argc > 1 ? argv [1] : NULL;
    RESULT_NODE *cl      = argc > 2 ? argv [2] : NULL;

    if (handle && (handle-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = handle-> culprit;
        return 0;
      }
    if (file && (file-> value. type == TYPE_UNDEFINED))
      {
        result-> culprit = file-> culprit;
        return 0;
      }

  {
    int
        handle_n;

    handle_n = (int) number_value (&handle-> value);

    if ((handle_n < 0 || handle_n > MAX_ZIPFILES)
    ||  (! zipfile_ptr [handle_n]))
        return 0;
    
    result-> value. type = TYPE_NUMBER;
    result-> value. n    = zip_add (
        zipfile_ptr [handle_n],
        string_value (&file-> value),
        cl? (int) number_value (&cl-> value): Z_DEFAULT_COMPRESSION
    );
  }

    return 0;
}


