signal_cleanup(int x)
{
  if (!initialised) exit(0);
  SCH_QuitProgram();
}