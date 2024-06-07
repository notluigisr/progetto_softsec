int zmq::curve_client_t::next_handshake_command (msg_t *msg_)
{
    int rc = 0;

    switch (state) {
        case send_hello:
            rc = produce_hello (msg_);
            if (rc == 0)
                state = expect_welcome;
            break;
        case send_initiate:
            rc = produce_initiate (msg_);
            if (rc == 0)
                state = expect_ready;
            break;
        default:
            errno = EAGAIN;
            rc = -1;
    }
    return rc;
}