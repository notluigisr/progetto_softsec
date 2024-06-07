symbols_sort (const symbol **first, const symbol **second)
{
  if (0 < location_cmp ((*first)->location, (*second)->location))
    {
      const symbol* tmp = *first;
      *first = *second;
      *second = tmp;
    }
}