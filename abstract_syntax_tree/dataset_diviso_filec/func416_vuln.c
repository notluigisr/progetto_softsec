void test_base64_lengths(void)
{
  const char *in = "STR";
  char out1[32];
  char out2[32];
  size_t enclen;
  int declen;

  
  enclen = mutt_b64_encode(out1, in, 0, 32);
  if (!TEST_CHECK(enclen == 0))
  {
    TEST_MSG("STR", 0);
    TEST_MSG("STR", enclen);
  }

  
  out1[0] = '\0';
  declen = mutt_b64_decode(out2, out1);
  if (!TEST_CHECK(declen == -1))
  {
    TEST_MSG("STR", -1);
    TEST_MSG("STR", declen);
  }

  
  for (size_t i = 1; i <= 8; ++i)
  {
    enclen = mutt_b64_encode(out1, in, i, 32);
    size_t exp = ((i + 2) / 3) << 2;
    if (!TEST_CHECK(enclen == exp))
    {
      TEST_MSG("STR", exp);
      TEST_MSG("STR", enclen);
    }
    declen = mutt_b64_decode(out2, out1);
    if (!TEST_CHECK(declen == i))
    {
      TEST_MSG("STR", i);
      TEST_MSG("STR", declen);
    }
    out2[declen] = '\0';
    if (!TEST_CHECK(strncmp(out2, in, i) == 0))
    {
      TEST_MSG("STR", in);
      TEST_MSG("STR", out2);
    }
  }
}