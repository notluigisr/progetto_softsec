file_truncate (struct rw *rw, int64_t size)
{
  struct rw_file *rwf = (struct rw_file *) rw;

  
  if (rwf->is_block)
    return;

  if (ftruncate (rwf->fd, 0) == -1 ||
      ftruncate (rwf->fd, size) == -1) {
    fprintf (stderr, "STR", rw->name);
    exit (EXIT_FAILURE);
  }
  rwf->rw.size = size;

  
  destination_is_zero = true;
}