static int aes_wrap_init_key(EVP_CIPHER_CTX *ctx, const unsigned char *key,
                             const unsigned char *iv, int enc)
{
    EVP_AES_WRAP_CTX *wctx = ctx->cipher_data;
    if (!iv && !key)
        return 1;
    if (key) {
        if (ctx->encrypt)
            AES_set_encrypt_key(key, ctx->key_len * 8, &wctx->ks.ks);
        else
            AES_set_decrypt_key(key, ctx->key_len * 8, &wctx->ks.ks);
        if (!iv)
            wctx->iv = NULL;
    }
    if (iv) {
        memcpy(ctx->iv, iv, 8);
        wctx->iv = ctx->iv;
    }
    return 1;
}