int X509v3_addr_get_range(IPAddressOrRange *aor,
                          const unsigned afi,
                          unsigned char *min,
                          unsigned char *max, const int length)
{
    int afi_length = length_from_afi(afi);
    if (aor == NULL || min == NULL || max == NULL ||
        afi_length == 0 || length < afi_length ||
        (aor->type != IPAddressOrRange_addressPrefix &&
         aor->type != IPAddressOrRange_addressRange) ||
        !extract_min_max(aor, min, max, afi_length))
        return 0;

    return afi_length;
}