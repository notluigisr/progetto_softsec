ossl_cipher_initialize(VALUE self, VALUE str)
{
    EVP_CIPHER_CTX *ctx;
    const EVP_CIPHER *cipher;
    char *name;
    unsigned char key[EVP_MAX_KEY_LENGTH];

    name = StringValuePtr(str);
    GetCipherInit(self, ctx);
    if (ctx) {
	ossl_raise(rb_eRuntimeError, "STR");
    }
    AllocCipher(self, ctx);
    EVP_CIPHER_CTX_init(ctx);
    if (!(cipher = EVP_get_cipherbyname(name))) {
	ossl_raise(rb_eRuntimeError, "STR", name);
    }
    
    memset(key, 0, EVP_MAX_KEY_LENGTH);
    if (EVP_CipherInit_ex(ctx, cipher, NULL, key, NULL, -1) != 1)
	ossl_raise(eCipherError, NULL);

    return self;
}