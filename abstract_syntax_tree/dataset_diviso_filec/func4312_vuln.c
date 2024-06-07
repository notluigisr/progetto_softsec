int main(int argc, char *argv[])
{
    g_test_init(&argc, &argv, NULL);

    
    g_test_add_func("STR", test_no_issues);

    
    g_test_add_func("STR", test_stride_too_small);

    
    g_test_add_func("STR", test_too_big_image);

    
    g_test_add_func("STR", test_cursor_command);

    
    g_test_add_func("STR", test_circular_empty_chunks);

    
    g_test_add_func("STR", test_circular_small_chunks);

    return g_test_run();
}