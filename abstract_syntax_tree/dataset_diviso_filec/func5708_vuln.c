void test_base64_decode(void)
{
  char buffer[16];
  int len = mutt_b64_decode(buffer, encoded);
  if (!TEST_CHECK(len == sizeof(clear) - 1))
  {
    TEST_MSG("STR", sizeof(clear) - 1);
    TEST_MSG("STR", len);
  }
  buffer[len] = '\0';
  if (!TEST_CHECK(strcmp(buffer, clear) == 0))
  {
    TEST_MSG("STR", clear);
    TEST_MSG("STR", buffer);
  }
}