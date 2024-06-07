int main(int argc, char **argv)
{
    g_test_init(&argc, &argv, NULL);

    qtest_add_func("STR",
                   test_lsi_do_dma_empty_queue);

    return g_test_run();
}