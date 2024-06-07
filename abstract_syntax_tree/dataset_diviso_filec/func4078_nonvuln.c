void set_wild_chars (my_bool set)
{
  static char old_many= 0, old_one, old_prefix;

  if (set) 
  {
    if (wild_many == '*') return; 
    old_many= wild_many;
    old_one= wild_one;
    old_prefix= wild_prefix;
    wild_many= '*';
    wild_one= '?';
    wild_prefix= 0;
  }
  else 
  {
    if (! old_many) return;	
    wild_many= old_many;
    wild_one= old_one;
    wild_prefix= old_prefix;
  }
}