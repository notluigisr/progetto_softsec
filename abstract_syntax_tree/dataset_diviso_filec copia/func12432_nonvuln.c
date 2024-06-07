test_bson_append_utf8 (void)
{
   bson_t *b;
   bson_t *b2;

   b = bson_new ();
   b2 = get_bson ("STR");
   BSON_ASSERT (bson_append_utf8 (b, "STR", -1));
   BSON_ASSERT_BSON_EQUAL (b, b2);
   bson_destroy (b);
   bson_destroy (b2);
}