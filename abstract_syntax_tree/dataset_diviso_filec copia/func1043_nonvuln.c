bash_complete_username (ignore, ignore2)
     int ignore, ignore2;
{
  return bash_complete_username_internal (rl_completion_mode (bash_complete_username));
}