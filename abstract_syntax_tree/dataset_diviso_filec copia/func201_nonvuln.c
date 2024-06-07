void InitClientKeyFactory(ClientKeyFactory& ckf)
{
    ckf.Reserve(3);
    ckf.Register(rsa_kea, CreateRSAClient);
    ckf.Register(diffie_hellman_kea, CreateDHClient);
    ckf.Register(fortezza_kea, CreateFortezzaClient);
}