int Field_long::store(double nr)
{
  ASSERT_COLUMN_MARKED_FOR_WRITE_OR_COMPUTED;
  int error= 0;
  int32 res;
  nr=rint(nr);
  if (unsigned_flag)
  {
    if (nr < 0)
    {
      res=0;
      error= 1;
    }
    else if (nr > (double) UINT_MAX32)
    {
      res= UINT_MAX32;
      set_warning(ER_WARN_DATA_OUT_OF_RANGE, 1);
      error= 1;
    }
    else
      res=(int32) (ulong) nr;
  }
  else
  {
    if (nr < (double) INT_MIN32)
    {
      res=(int32) INT_MIN32;
      error= 1;
    }
    else if (nr > (double) INT_MAX32)
    {
      res=(int32) INT_MAX32;
      error= 1;
    }
    else
      res=(int32) (longlong) nr;
  }
  if (error)
    set_warning(ER_WARN_DATA_OUT_OF_RANGE, 1);

  int4store(ptr,res);
  return error;
}