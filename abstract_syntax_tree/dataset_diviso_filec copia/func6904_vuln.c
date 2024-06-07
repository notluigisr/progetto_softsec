ossl_cipher_initialize(VALUE self, VALUE str)
{
    EVP_CIPHER_CTX *ctx;
    const EVP_CIPHER *cipher;
    char *name;
    unsigned char dummy_key[EVP_MAX_KEY_LENGTH] = { 0 };

    name = StringValueCStr(str);
    GetCipherInit(self, ctx);
    if (ctx) {
	ossl_raise(rb_eRuntimeError, "STR");
    }
    AllocCipher(self, ctx);
    if (!(cipher = EVP_get_cipherbyname(name))) {
	ossl_raise(rb_eRuntimeError, "STR", str);
    }
    
    if (EVP_CipherInit_ex(ctx, cipher, NULL, dummy_key, NULL, -1) != 1)
	ossl_raise(eCipherError, NULL);

    return self;
}