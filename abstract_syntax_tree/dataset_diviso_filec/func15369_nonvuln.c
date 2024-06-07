hostkey_method_ssh_dss_initPEMFromMemory(LIBSSH2_SESSION * session,
                                         const char *privkeyfiledata,
                                         size_t privkeyfiledata_len,
                                         unsigned const char *passphrase,
                                         void **abstract)
{
    libssh2_dsa_ctx *dsactx;
    int ret;

    if(*abstract) {
        hostkey_method_ssh_dss_dtor(session, abstract);
        *abstract = NULL;
    }

    ret = _libssh2_dsa_new_private_frommemory(&dsactx, session,
                                              privkeyfiledata,
                                              privkeyfiledata_len, passphrase);
    if(ret) {
        return -1;
    }

    *abstract = dsactx;

    return 0;
}