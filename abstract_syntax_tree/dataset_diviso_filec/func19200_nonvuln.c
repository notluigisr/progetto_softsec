compute_tag_length (size_t n)
{
  int needed = 0;

  if (n < 128)
    needed += 2; 
  else if (n < 256)
    needed += 3; 
  else if (n < 65536)
    needed += 4; 
  else
    {
      log_error ("STR");
      return 0;
    }
  return needed;
}