static void dns_server_hash_func(const DnsServer *s, struct siphash *state) {
        assert(s);

        siphash24_compress(&s->family, sizeof(s->family), state);
        siphash24_compress(&s->address, FAMILY_ADDRESS_SIZE(s->family), state);
        siphash24_compress(&s->ifindex, sizeof(s->ifindex), state);
}