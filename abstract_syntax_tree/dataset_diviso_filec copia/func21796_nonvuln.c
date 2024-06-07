ofputil_decode_ofp11_port_mod(const struct ofp11_port_mod *opm,
                              struct ofputil_port_mod *pm)
{
    enum ofperr error;

    error = ofputil_port_from_ofp11(opm->port_no, &pm->port_no);
    if (error) {
        return error;
    }

    pm->hw_addr = opm->hw_addr;
    pm->config = ntohl(opm->config) & OFPPC11_ALL;
    pm->mask = ntohl(opm->mask) & OFPPC11_ALL;
    pm->advertise = netdev_port_features_from_ofp11(opm->advertise);

    return 0;
}