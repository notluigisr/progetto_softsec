int main(int argc, char **argv)
{
    int fd;
    int ret;

    
    fd = mkstemp(test_image);
    g_assert(fd >= 0);
    ret = ftruncate(fd, TEST_IMAGE_SIZE);
    g_assert(ret == 0);
    close(fd);

    
    g_test_init(&argc, &argv, NULL);

    qtest_start("STR");
    qtest_irq_intercept_in(global_qtest, "STR");
    qtest_add_func("STR", test_cmos);
    qtest_add_func("STR", test_no_media_on_start);
    qtest_add_func("STR", test_read_without_media);
    qtest_add_func("STR", test_media_change);
    qtest_add_func("STR", test_sense_interrupt);
    qtest_add_func("STR", test_relative_seek);
    qtest_add_func("STR", test_read_id);
    qtest_add_func("STR", test_verify);
    qtest_add_func("STR", test_media_insert);
    qtest_add_func("STR", test_read_no_dma_1);
    qtest_add_func("STR", test_read_no_dma_18);
    qtest_add_func("STR", test_read_no_dma_19);
    qtest_add_func("STR", fuzz_registers);
    qtest_add_func("STR", test_cve_2021_20196);

    ret = g_test_run();

    
    qtest_end();
    unlink(test_image);

    return ret;
}