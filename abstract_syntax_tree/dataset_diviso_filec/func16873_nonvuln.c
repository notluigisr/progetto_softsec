SCM_DEFINE (scm_opendir, "STR", 1, 0, 0,
	    (SCM dirname),
	    "STR"
	    "STR")

{
  DIR *ds;
  STRING_SYSCALL (dirname, c_dirname, ds = opendir (c_dirname));
  if (ds == NULL)
    SCM_SYSERROR;
  SCM_RETURN_NEWSMOB (scm_tc16_dir | (SCM_DIR_FLAG_OPEN<<16), ds);
}