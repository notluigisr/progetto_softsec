SCM_DEFINE (scm_mkdir, "STR", 1, 1, 0,
            (SCM path, SCM mode),
	    "STR"
	    "STR"
	    "STR"
	    "STR")

{
  int rv;
  mode_t mask;

  if (SCM_UNBNDP (mode))
    {
      mask = umask (0);
      umask (mask);
      STRING_SYSCALL (path, c_path, rv = mkdir (c_path, 0777 ^ mask));
    }
  else
    {
      STRING_SYSCALL (path, c_path, rv = mkdir (c_path, scm_to_uint (mode)));
    }
  if (rv != 0)
    SCM_SYSERROR;
  return SCM_UNSPECIFIED;
}