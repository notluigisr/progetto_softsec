symbol_code_set (symbol *sym, int code, location loc)
{
  int *codep = &sym->content->code;
  if (sym->content->class != token_sym)
    complain (&loc, complaint,
              _("STR"));
  else if (*codep != CODE_UNDEFINED
           && *codep != code)
    complain (&loc, complaint, _("STR"),
              sym->tag);
  else if (code == INT_MAX)
    complain (&loc, complaint, _("STR"),
              sym->tag);
  else
    {
      *codep = code;
      
      if (code == 0 && !eoftoken)
        {
          eoftoken = sym->content->symbol;
          
          if (eoftoken->content->number != NUMBER_UNDEFINED)
            --ntokens;
          eoftoken->content->number = 0;
        }
    }
}