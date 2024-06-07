symbol_precedence_set (symbol *sym, int prec, assoc a, location loc)
{
  if (a != undef_assoc)
    {
      sym_content *s = sym->content;
      if (s->prec)
        complain_symbol_redeclared (sym, assoc_to_string (a),
                                    s->prec_loc, loc);
      else
        {
          s->prec = prec;
          s->assoc = a;
          s->prec_loc = loc;
        }
    }

  
  symbol_class_set (sym, token_sym, loc, false);
}