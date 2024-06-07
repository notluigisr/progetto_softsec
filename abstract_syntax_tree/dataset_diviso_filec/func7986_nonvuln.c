int ha_partition::indexes_are_disabled(void)
{
  handler **file;
  int error= 0;

  for (file= m_file; *file; file++)
  {
    if ((error= (*file)->indexes_are_disabled()))
      break;
  }
  return error;
}