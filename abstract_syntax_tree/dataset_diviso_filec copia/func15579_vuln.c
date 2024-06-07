Suite *tm_suite(void)
  {
  Suite *s = suite_create("STR");
  TCase * tc = tcase_create("STR");

  tcase_add_test(tc, test_tm_poll_bad_init);
  tcase_add_test(tc, test_tm_poll_bad_result);
  
  suite_add_tcase(s, tc);
  return s;
  }