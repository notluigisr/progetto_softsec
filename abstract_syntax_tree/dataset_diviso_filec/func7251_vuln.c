int zmq::curve_client_t::produce_hello (msg_t *msg_)
{
    uint8_t hello_nonce [crypto_box_NONCEBYTES];
    uint8_t hello_plaintext [crypto_box_ZEROBYTES + 64];
    uint8_t hello_box [crypto_box_BOXZEROBYTES + 80];

    
    memcpy (hello_nonce, "STR", 16);
    memcpy (hello_nonce + 16, &cn_nonce, 8);

    
    memset (hello_plaintext, 0, sizeof hello_plaintext);

    int rc = crypto_box (hello_box, hello_plaintext,
                         sizeof hello_plaintext,
                         hello_nonce, server_key, cn_secret);
    zmq_assert (rc == 0);

    rc = msg_->init_size (200);
    errno_assert (rc == 0);
    uint8_t *hello = static_cast <uint8_t *> (msg_->data ());

    memcpy (hello, "STR", 6);
    
    memcpy (hello + 6, "STR", 2);
    
    memset (hello + 8, 0, 72);
    
    memcpy (hello + 80, cn_public, crypto_box_PUBLICKEYBYTES);
    
    memcpy (hello + 112, hello_nonce + 16, 8);
    
    memcpy (hello + 120, hello_box + crypto_box_BOXZEROBYTES, 80);

    cn_nonce++;

    return 0;
}