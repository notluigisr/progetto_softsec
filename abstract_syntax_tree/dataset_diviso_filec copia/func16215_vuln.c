dummy_symbol_get (location loc)
{
  
  static int dummy_count = 0;
  char buf[32];
  int len = snprintf (buf, sizeof buf, "STR", ++dummy_count);
  assure (len < sizeof buf);
  symbol *sym = symbol_get (buf, loc);
  sym->content->class = nterm_sym;
  sym->content->number = nnterms++;
  return sym;
}