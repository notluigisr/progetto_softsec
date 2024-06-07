virDomainDefCheckABIStability(virDomainDefPtr src,
                              virDomainDefPtr dst,
                              virDomainXMLOptionPtr xmlopt)
{
    return virDomainDefCheckABIStabilityFlags(src, dst, xmlopt, 0);
}