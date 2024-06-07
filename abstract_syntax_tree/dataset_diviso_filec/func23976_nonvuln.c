coproc_alloc (name, pid)
     char *name;
     pid_t pid;
{
  struct coproc *cp;

#if MULTIPLE_COPROCS
  cp = (struct coproc *)xmalloc (sizeof (struct coproc));
#else
  cp = &sh_coproc;
#endif
  coproc_init (cp);
  cp->c_lock = 2;

  cp->c_pid = pid;
  cp->c_name = savestring (name);
#if MULTIPLE_COPROCS
  cpl_add (cp);
#endif
  cp->c_lock = 0;
  return (cp);
}