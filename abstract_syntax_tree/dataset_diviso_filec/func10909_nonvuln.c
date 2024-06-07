void ServerKeyExchange::Process(input_buffer& input, SSL& ssl)
{
    if (input.get_error()) {
        ssl.SetError(bad_input);
        return;
    }
    createKey(ssl);
    if (ssl.GetError()) return;
    server_key_->read(ssl, input);
    if (input.get_error()) {
        ssl.SetError(bad_input);
        return;
    }

    ssl.useStates().useClient() = serverKeyExchangeComplete;
}