void CIRCNetwork::BounceAllClients() {
    for (CClient* pClient : m_vClients) {
        pClient->BouncedOff();
    }

    m_vClients.clear();
}