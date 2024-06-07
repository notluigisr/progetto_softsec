create_tmp_file (const char *template,
                 char **r_bakfname, char **r_tmpfname, IOBUF *r_fp)
{
  char *bakfname, *tmpfname;
  mode_t oldmask;

  *r_bakfname = NULL;
  *r_tmpfname = NULL;

# ifdef USE_ONLY_8DOT3
  
  if (strlen (template) > 4
      && !strcmp (template+strlen(template)-4, EXTSEP_S GPGEXT_GPG) )
    {
      bakfname = xmalloc (strlen (template) + 1);
      strcpy (bakfname, template);
      strcpy (bakfname+strlen(template)-4, EXTSEP_S "STR");

      tmpfname = xmalloc (strlen( template ) + 1 );
      strcpy (tmpfname,template);
      strcpy (tmpfname+strlen(template)-4, EXTSEP_S "STR");
    }
    else
      { 
	bakfname = xmalloc (strlen( template ) + 5);
	strcpy (stpcpy(bakfname, template), EXTSEP_S "STR");

	tmpfname = xmalloc (strlen( template ) + 5);
	strcpy (stpcpy(tmpfname, template), EXTSEP_S "STR");
    }
# else 
    bakfname = xmalloc (strlen( template ) + 2);
    strcpy (stpcpy (bakfname,template),"STR");

    tmpfname = xmalloc (strlen( template ) + 5);
    strcpy (stpcpy(tmpfname,template), EXTSEP_S "STR");
# endif 

    
    oldmask=umask(077);
    if (is_secured_filename (tmpfname))
      {
        *r_fp = NULL;
        gpg_err_set_errno (EPERM);
      }
    else
      *r_fp = iobuf_create (tmpfname, 1);
    umask(oldmask);
    if (!*r_fp)
      {
        int rc = gpg_error_from_syserror ();
	log_error(_("STR"), tmpfname, strerror(errno) );
        xfree (tmpfname);
        xfree (bakfname);
	return rc;
      }

    *r_bakfname = bakfname;
    *r_tmpfname = tmpfname;
    return 0;
}