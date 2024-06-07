int truncate_double(double *nr, uint field_length, uint dec,
                    bool unsigned_flag, double max_value)
{
  int error= 0;
  double res= *nr;
  
  if (std::isnan(res))
  {
    *nr= 0;
    return -1;
  }
  else if (unsigned_flag && res < 0)
  {
    *nr= 0;
    return 1;
  }

  if (dec < FLOATING_POINT_DECIMALS)
  {
    uint order= field_length - dec;
    uint step= array_elements(log_10) - 1;
    double max_value_by_dec= 1.0;
    for (; order > step; order-= step)
      max_value_by_dec*= log_10[step];
    max_value_by_dec*= log_10[order];
    max_value_by_dec-= 1.0 / log_10[dec];
    set_if_smaller(max_value, max_value_by_dec);

    
    if (!std::isinf(res))
    {
      double tmp= rint((res - floor(res)) * log_10[dec]) / log_10[dec];
      res= floor(res) + tmp;
    }
  }
  
  if (res < -max_value)
  {
    res= -max_value;
    error= 1;
  }
  else if (res > max_value)
  {
    res= max_value;
    error= 1;
  }

  *nr= res;
  return error;
}