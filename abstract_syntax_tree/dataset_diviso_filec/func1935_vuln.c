main (int argc, char **argv)
{
    g_test_init (&argc, &argv, NULL);

    g_test_add_func ("STR", test_non_svg_element);

    g_test_add_data_func_full ("STR",
                               "STR",
                               test_instancing_limit,
                               NULL);

    g_test_add_data_func_full ("STR",
                               "STR",
                               test_instancing_limit,
                               NULL);


    return g_test_run ();
}