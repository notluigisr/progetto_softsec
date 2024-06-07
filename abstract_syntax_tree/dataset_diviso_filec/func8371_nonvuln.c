bool Lex_input_stream::consume_comment(int remaining_recursions_permitted)
{
  
  DBUG_ASSERT(remaining_recursions_permitted == 0 ||
              remaining_recursions_permitted == 1);
  uchar c;
  while (!eof())
  {
    c= yyGet();

    if (remaining_recursions_permitted == 1)
    {
      if ((c == '/') && (yyPeek() == '*'))
      {
        yyUnput('(');  
        yySkip();      

        yySkip(); 
        if (consume_comment(0))
          return true;

        yyUnput(')');  
        yySkip();      
        continue;
      }
    }

    if (c == '*')
    {
      if (yyPeek() == '/')
      {
        yySkip(); 
        return FALSE;
      }
    }

    if (c == '\n')
      yylineno++;
  }

  return TRUE;
}