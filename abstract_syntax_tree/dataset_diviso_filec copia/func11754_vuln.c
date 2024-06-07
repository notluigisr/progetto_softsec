static void remove_trailing_spaces(char *string, size_t len)
{
  if(len<1) return; 
  string[len-1]=0;
  if(len<3) return; 
  len = strnlen(string,len-1);
  for(int i=len-1; i>=0; i--)
  {
    if(isspace(string[i]))
      string[i]=0;
    else
      break;
  }
}