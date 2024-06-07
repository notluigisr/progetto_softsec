sh_openpipe (pv)
     int *pv;
{
  int r;

  if ((r = pipe (pv)) < 0)
    return r;

  pv[0] = move_to_high_fd (pv[0], 1, 64);
  pv[1] = move_to_high_fd (pv[1], 1, 64);

  return 0;  
}