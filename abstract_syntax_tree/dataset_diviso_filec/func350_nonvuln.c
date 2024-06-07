void ClientKeyExchange::createKey(SSL& ssl)
{
    const ClientKeyFactory& ckf = ssl.getFactory().getClientKey();
    client_key_ = ckf.CreateObject(ssl.getSecurity().get_parms().kea_);

    if (!client_key_)
        ssl.SetError(factory_error);
}