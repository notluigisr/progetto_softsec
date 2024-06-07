string_to_cipher_algo (const char *string)
{
  int val;

  val = map_cipher_gcry_to_openpgp (gcry_cipher_map_name (string));
  if (!val && string && (string[0]=='S' || string[0]=='s'))
    {
      char *endptr;

      string++;
      val = strtol (string, &endptr, 10);
      if (!*string || *endptr || openpgp_cipher_test_algo (val))
        val = 0;
    }

  return val;
}