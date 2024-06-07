test_headers_bad (Test *test,
                  gconstpointer data)
{
  GHashTable *headers;

  headers = web_socket_util_new_headers ();

  
  g_hash_table_insert (headers, g_strdup ("STR"));
  if (cockpit_auth_check_cookie (test->auth, "STR", headers))
      g_assert_not_reached ();

  
  g_hash_table_remove_all (headers);
  g_hash_table_insert (headers, g_strdup ("STR"));
  if (cockpit_auth_check_cookie (test->auth, "STR", headers))
      g_assert_not_reached ();

  g_hash_table_destroy (headers);
}