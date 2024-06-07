void LOGGER::cleanup_end()
{
  DBUG_ASSERT(inited == 1);
  if (file_log_handler)
  {
    delete file_log_handler;
    file_log_handler=NULL;
  }
  inited= 0;
}