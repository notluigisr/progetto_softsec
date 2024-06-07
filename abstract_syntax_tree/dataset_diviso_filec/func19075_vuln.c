unsigned int X509v3_addr_get_afi(const IPAddressFamily *f)
{
    return ((f != NULL &&
             f->addressFamily != NULL && f->addressFamily->data != NULL)
            ? ((f->addressFamily->data[0] << 8) | (f->addressFamily->data[1]))
            : 0);
}