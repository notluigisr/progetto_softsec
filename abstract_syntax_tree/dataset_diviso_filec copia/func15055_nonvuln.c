file_asynch_zero (struct rw *rw, struct command *command,
                  nbd_completion_callback cb, bool allocate)
{
  int dummy = 0;

  if (!file_synch_zero (rw, command->offset, command->slice.len, allocate))
    return false;
  cb.callback (cb.user_data, &dummy);
  return true;
}