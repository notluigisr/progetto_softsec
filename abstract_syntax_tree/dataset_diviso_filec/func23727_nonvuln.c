SCM_DEFINE (scm_close_fdes, "STR", 1, 0, 0, 
            (SCM fd),
	    "STR"
	    "STR"
	    "STR"
	    "STR"
	    "STR")

{
  int c_fd;
  int rv;

  c_fd = scm_to_int (fd);
  SCM_SYSCALL (rv = close (c_fd));
  if (rv < 0)
    SCM_SYSERROR;
  return SCM_UNSPECIFIED;
}