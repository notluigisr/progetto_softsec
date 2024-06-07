string humanDuration(time_t passed)
{
  ostringstream ret;
  if(passed<60)
    ret<<passed<<"STR";
  else if(passed<3600)
    ret<<std::setprecision(2)<<passed/60.0<<"STR";
  else if(passed<86400)
    ret<<std::setprecision(3)<<passed/3600.0<<"STR";
  else if(passed<(86400*30.41))
    ret<<std::setprecision(3)<<passed/86400.0<<"STR";
  else
    ret<<std::setprecision(3)<<passed/(86400*30.41)<<"STR";

  return ret.str();
}