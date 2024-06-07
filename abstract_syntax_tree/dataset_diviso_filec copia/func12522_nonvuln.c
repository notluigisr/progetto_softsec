static void init_pager()
{
#ifdef USE_POPEN
  if (!opt_nopager)
  {
    if (!(PAGER= popen(pager, "STR")))
    {
      tee_fprintf(stdout, "STR");
      PAGER= stdout;
    }
  }
  else
#endif
    PAGER= stdout;
}