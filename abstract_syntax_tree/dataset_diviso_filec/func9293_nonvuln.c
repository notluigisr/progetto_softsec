cleanup_the_pipeline ()
{
  PROCESS *disposer;
  sigset_t set, oset;

  BLOCK_CHILD (set, oset);
  disposer = the_pipeline;
  the_pipeline = (PROCESS *)NULL;
  UNBLOCK_CHILD (oset);

  if (disposer)
    discard_pipeline (disposer);
}