void mutt_free_alias (ALIAS **p)
{
  ALIAS *t;

  while (*p)
  {
    t = *p;
    *p = (*p)->next;
    mutt_alias_delete_reverse (t);
    FREE (&t->name);
    rfc822_free_address (&t->addr);
    FREE (&t);
  }
}