static int aes_cbc_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
                          const unsigned char *in, size_t len)
{
    EVP_AES_KEY *dat = (EVP_AES_KEY *) ctx->cipher_data;

    if (dat->stream.cbc)
        (*dat->stream.cbc) (in, out, len, &dat->ks, ctx->iv, ctx->encrypt);
    else if (ctx->encrypt)
        CRYPTO_cbc128_encrypt(in, out, len, &dat->ks, ctx->iv, dat->block);
    else
        CRYPTO_cbc128_decrypt(in, out, len, &dat->ks, ctx->iv, dat->block);

    return 1;
}