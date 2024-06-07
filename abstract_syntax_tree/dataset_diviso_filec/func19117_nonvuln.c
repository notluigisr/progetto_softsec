make_pa_for_user_checksum(krb5_context context,
                          krb5_keyblock *key,
                          krb5_pa_for_user *req,
                          krb5_checksum *cksum)
{
    krb5_error_code code;
    int i;
    char *p;
    krb5_data data;

    data.length = 4;
    for (i = 0; i < req->user->length; i++)
        data.length += req->user->data[i].length;
    data.length += req->user->realm.length;
    data.length += req->auth_package.length;

    p = data.data = malloc(data.length);
    if (data.data == NULL)
        return ENOMEM;

    p[0] = (req->user->type >> 0) & 0xFF;
    p[1] = (req->user->type >> 8) & 0xFF;
    p[2] = (req->user->type >> 16) & 0xFF;
    p[3] = (req->user->type >> 24) & 0xFF;
    p += 4;

    for (i = 0; i < req->user->length; i++) {
        if (req->user->data[i].length > 0)
            memcpy(p, req->user->data[i].data, req->user->data[i].length);
        p += req->user->data[i].length;
    }

    if (req->user->realm.length > 0)
        memcpy(p, req->user->realm.data, req->user->realm.length);
    p += req->user->realm.length;

    if (req->auth_package.length > 0)
        memcpy(p, req->auth_package.data, req->auth_package.length);

    
    code = krb5_c_make_checksum(context, CKSUMTYPE_HMAC_MD5_ARCFOUR, key,
                                KRB5_KEYUSAGE_APP_DATA_CKSUM, &data,
                                cksum);

    free(data.data);

    return code;
}