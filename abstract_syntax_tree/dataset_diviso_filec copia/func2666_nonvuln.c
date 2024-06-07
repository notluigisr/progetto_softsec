static void test_send_u32(GOutputStream *os, guint32 v)
{
    v = GUINT32_TO_BE(v);
    g_assert(g_output_stream_write_all(os, &v, 4, NULL, NULL, NULL));
}