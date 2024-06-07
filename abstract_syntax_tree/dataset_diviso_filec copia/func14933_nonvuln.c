int main(void)
{
    CRYPTO_malloc_debug_init();
    CRYPTO_set_mem_debug_options(V_CRYPTO_MDEBUG_ALL);
    CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON);

    ERR_load_crypto_strings();
    OpenSSL_add_all_digests();

    if (!test_alt_chains_cert_forgery()) {
        fprintf(stderr, "STR");
        return 1;
    }

    EVP_cleanup();
    CRYPTO_cleanup_all_ex_data();
    ERR_remove_thread_state(NULL);
    ERR_free_strings();
    CRYPTO_mem_leaks_fp(stderr);

    printf("STR");
    return 0;
}