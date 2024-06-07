void SSL::setKeys()
{
    Connection& conn = secure_.use_connection();

    if (secure_.get_parms().entity_ == client_end) {
        crypto_.use_cipher().set_encryptKey(conn.client_write_key_, 
                                            conn.client_write_IV_);
        crypto_.use_cipher().set_decryptKey(conn.server_write_key_,
                                            conn.server_write_IV_);
    }
    else {
        crypto_.use_cipher().set_encryptKey(conn.server_write_key_,
                                            conn.server_write_IV_);
        crypto_.use_cipher().set_decryptKey(conn.client_write_key_,
                                            conn.client_write_IV_);
    }
}