AA_4_IndicateAPAbort(PRIVATE_NETWORKKEY ** ,
         PRIVATE_ASSOCIATIONKEY ** association, int nextState, void * )
{
    closeTransport(association);
    (*association)->protocolState = nextState;
    return DUL_PEERABORTEDASSOCIATION;
}