addlists (char **old, char **new)
{
  size_t i;

  if (old == NULL || new == NULL)
    return NULL;
  for (i = 0; new[i] != NULL; ++i)
    {
      old = enlist(old, new[i], strlen(new[i]));
      if (old == NULL)
        break;
    }
  return old;
}