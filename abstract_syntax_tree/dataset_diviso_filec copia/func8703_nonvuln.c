AE_1_TransportConnect(PRIVATE_NETWORKKEY ** network,
         PRIVATE_ASSOCIATIONKEY ** association, int nextState, void *params)
{
    DUL_ASSOCIATESERVICEPARAMETERS
    * service;
    OFCondition cond = EC_Normal;

    service = (DUL_ASSOCIATESERVICEPARAMETERS *) params;
    clearPDUCache(association);
    cond = requestAssociationTCP(network, service, association);
    (*association)->protocolState = nextState;
    return cond;
}