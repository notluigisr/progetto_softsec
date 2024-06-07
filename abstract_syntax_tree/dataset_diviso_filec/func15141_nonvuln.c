virDomainNetGetActualBandwidth(const virDomainNetDef *iface)
{
    
    if (iface->type == VIR_DOMAIN_NET_TYPE_NETWORK &&
        iface->data.network.actual)
        return iface->data.network.actual->bandwidth;
    return iface->bandwidth;
}