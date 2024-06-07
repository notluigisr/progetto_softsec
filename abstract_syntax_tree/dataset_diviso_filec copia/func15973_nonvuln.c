string bitFlip(const string &str)
{
  string::size_type pos=0, epos=str.size();
  string ret;
  ret.reserve(epos);
  for(;pos < epos; ++pos)
    ret.append(1, ~str[pos]);
  return ret;
}