select_opt_map(OptMap* now, OptMap* alt)
{
  static int z = 1<<15; 

  int vn, va;

  if (alt->value == 0) return ;
  if (now->value == 0) {
    copy_opt_map(now, alt);
    return ;
  }

  vn = z / now->value;
  va = z / alt->value;
  if (comp_distance_value(&now->mmd, &alt->mmd, vn, va) > 0)
    copy_opt_map(now, alt);
}