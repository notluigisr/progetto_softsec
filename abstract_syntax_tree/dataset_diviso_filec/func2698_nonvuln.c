test_bson_append_int32 (void)
{
   bson_t *b;
   bson_t *b2;

   b = bson_new ();
   BSON_ASSERT (bson_append_int32 (b, "STR", -1, -123));
   BSON_ASSERT (bson_append_int32 (b, "STR", -1, 0));
   BSON_ASSERT (bson_append_int32 (b, "STR", -1, 123));
   b2 = get_bson ("STR");
   BSON_ASSERT_BSON_EQUAL (b, b2);
   bson_destroy (b);
   bson_destroy (b2);
}