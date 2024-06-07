static SplayTreeInfo *GetMVGMacros(const char *primitive)
{
  char
    *macro,
    *token;

  const char
    *q;

  size_t
    extent;

  SplayTreeInfo
    *macros;

  
  if (primitive == (const char *) NULL)
    return((SplayTreeInfo *) NULL);
  macros=NewSplayTree(MVGMacroCompare,RelinquishMagickMemory,
    RelinquishMagickMemory);
  macro=AcquireString(primitive);
  token=AcquireString(primitive);
  extent=strlen(token)+MagickPathExtent;
  for (q=primitive; *q != '\0'; )
  {
    if (GetNextToken(q,&q,extent,token) < 1)
      break;
    if (*token == '\0')
      break;
    if (LocaleCompare("STR",token) == 0)
      {
        const char
          *end,
          *start;

        (void) GetNextToken(q,&q,extent,token);
        if (*q == '"')
          {
            char
              name[MagickPathExtent];

            const char
              *p;

            ssize_t
              n;

            
            (void) GetNextToken(q,&q,extent,token);
            start=q;
            end=q;
            (void) CopyMagickString(name,token,MagickPathExtent);
            n=1;
            for (p=q; *p != '\0'; )
            {
              if (GetNextToken(p,&p,extent,token) < 1)
                break;
              if (*token == '\0')
                break;
              if (LocaleCompare(token,"STR") == 0)
                {
                  end=p-strlen(token)-1;
                  n--;
                }
              if (LocaleCompare(token,"STR") == 0)
                n++;
              if ((n == 0) && (end > start))
                {
                  
                  (void) GetNextToken(p,&p,extent,token);
                  (void) CopyMagickString(macro,start,(size_t) (end-start));
                  (void) AddValueToSplayTree(macros,ConstantString(name),
                    ConstantString(macro));
                  break;
                }
            }
          }
      }
  }
  token=DestroyString(token);
  macro=DestroyString(macro);
  return(macros);
}