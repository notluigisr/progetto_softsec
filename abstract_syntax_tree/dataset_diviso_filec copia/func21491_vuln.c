test_bson_append_code_with_scope (void)
{
   const uint8_t *scope_buf = NULL;
   uint32_t scopelen = 0;
   uint32_t len = 0;
   bson_iter_t iter;
   bool r;
   const char *code = NULL;
   bson_t *b;
   bson_t *b2;
   bson_t *scope;

   
   b = bson_new ();
   BSON_ASSERT (
      bson_append_code_with_scope (b, "STR", NULL));
   b2 = get_bson ("STR");
   BSON_ASSERT_BSON_EQUAL (b, b2);
   r = bson_iter_init_find (&iter, b, "STR");
   BSON_ASSERT (r);
   BSON_ASSERT (BSON_ITER_HOLDS_CODE (&iter)); 
   bson_destroy (b);
   bson_destroy (b2);

   
   b = bson_new ();
   scope = bson_new ();
   BSON_ASSERT (
      bson_append_code_with_scope (b, "STR", scope));
   b2 = get_bson ("STR");
   BSON_ASSERT_BSON_EQUAL (b, b2);
   r = bson_iter_init_find (&iter, b, "STR");
   BSON_ASSERT (r);
   BSON_ASSERT (BSON_ITER_HOLDS_CODEWSCOPE (&iter));
   bson_destroy (b);
   bson_destroy (b2);
   bson_destroy (scope);

   
   b = bson_new ();
   scope = bson_new ();
   BSON_ASSERT (bson_append_utf8 (scope, "STR", -1));
   BSON_ASSERT (
      bson_append_code_with_scope (b, "STR", scope));
   b2 = get_bson ("STR");
   BSON_ASSERT_BSON_EQUAL (b, b2);
   r = bson_iter_init_find (&iter, b, "STR");
   BSON_ASSERT (r);
   BSON_ASSERT (BSON_ITER_HOLDS_CODEWSCOPE (&iter));
   code = bson_iter_codewscope (&iter, &len, &scopelen, &scope_buf);
   BSON_ASSERT (len == 11);
   BSON_ASSERT (scopelen == scope->len);
   BSON_ASSERT (!strcmp (code, "STR"));
   bson_destroy (b);
   bson_destroy (b2);
   bson_destroy (scope);
}