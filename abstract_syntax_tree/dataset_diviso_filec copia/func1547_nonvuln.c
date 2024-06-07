sv_keymap (value)
     const char *value;
{
  Keymap kmap;

  kmap = rl_get_keymap_by_name (value);
  if (kmap)
    {
      rl_set_keymap (kmap);
      return 0;
    }
  return 1;
}