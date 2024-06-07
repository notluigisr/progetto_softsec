START_TEST(test_tm_adopt_ispidowner)
  {
  
  fail_unless(TRUE == ispidowner(getpid()));

  
  
  fail_unless(FALSE == ispidowner(1));
  }