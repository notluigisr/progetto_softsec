static bool SafeCharToWide(const char *Src,wchar *Dest,size_t DestSize)
{
  if (!CharToWide(Src,Dest,DestSize) || *Dest==0)
    return false;
  uint SrcChars=0,DestChars=0;
  for (uint I=0;Src[I]!=0;I++)
    if (Src[I]=='/' || Src[I]=='.')
      SrcChars++;
  for (uint I=0;Dest[I]!=0;I++)
    if (Dest[I]=='/' || Dest[I]=='.')
      DestChars++;
  return SrcChars==DestChars;
}