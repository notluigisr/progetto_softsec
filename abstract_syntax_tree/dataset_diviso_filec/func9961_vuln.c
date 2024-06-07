main (int argc, char *argv[])
{
  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("STR", test_happy_eyeballs);

  return g_test_run ();
}