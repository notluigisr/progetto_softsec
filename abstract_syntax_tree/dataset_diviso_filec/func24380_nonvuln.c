bash_complete_filename (ignore, ignore2)
     int ignore, ignore2;
{
  return bash_complete_filename_internal (rl_completion_mode (bash_complete_filename));
}