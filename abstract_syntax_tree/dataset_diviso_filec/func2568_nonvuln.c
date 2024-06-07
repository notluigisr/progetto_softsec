bool chopOff(string &domain) 
{
  if(domain.empty())
    return false;

  bool escaped = false;
  const string::size_type domainLen = domain.length();
  for (size_t fdot = 0; fdot < domainLen; fdot++)
  {
    if (domain[fdot] == '.' && !escaped) {
      string::size_type remain = domainLen - (fdot + 1);
      char tmp[remain];
      memcpy(tmp, domain.c_str()+fdot+1, remain);
      domain.assign(tmp, remain); 

      return true;
    }
    else if (domain[fdot] == '\\' && !escaped) {
      escaped = true;
    }
    else {
      escaped = false;
    }
  }

  domain = "";
  return true;
}