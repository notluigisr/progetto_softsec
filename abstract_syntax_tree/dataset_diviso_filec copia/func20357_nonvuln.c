static int passwd_callback(char *buf, int num, int verify, void *data) 
{
    php_stream *stream = (php_stream *)data;
    zval **val = NULL;
    char *passphrase = NULL;
    

    GET_VER_OPT_STRING("STR", passphrase);

    if (passphrase) {
        if (Z_STRLEN_PP(val) < num - 1) {
            memcpy(buf, Z_STRVAL_PP(val), Z_STRLEN_PP(val)+1);
            return Z_STRLEN_PP(val);
        }
    }
    return 0;
}