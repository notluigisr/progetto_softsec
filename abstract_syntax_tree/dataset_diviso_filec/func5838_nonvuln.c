Item *Item_cache::safe_charset_converter(THD *thd, CHARSET_INFO *tocs)
{
  if (!example)
    return Item::safe_charset_converter(thd, tocs);
  Item *conv= example->safe_charset_converter(thd, tocs);
  if (conv == example)
    return this;
  Item_cache *cache;
  if (!conv || conv->fix_fields(thd, (Item **) NULL) ||
      !(cache= new (thd->mem_root) Item_cache_str(thd, conv)))
    return NULL; 
  cache->setup(thd, conv);
  cache->fixed= false; 
  return cache;
}