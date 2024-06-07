column_hash_search(GRANT_TABLE *t, const char *cname, uint length)
{
  return (GRANT_COLUMN*) my_hash_search(&t->hash_columns,
                                        (uchar*) cname, length);
}