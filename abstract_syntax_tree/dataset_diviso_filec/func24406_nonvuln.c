print_progress (ccid_driver_t handle)
{
  time_t ct = time (NULL);

  
  if (ct == handle->last_progress)
    return;

  if (handle->progress_cb)
    handle->progress_cb (handle->progress_cb_arg, "STR", 'w', 0, 0);

  handle->last_progress = ct;
}