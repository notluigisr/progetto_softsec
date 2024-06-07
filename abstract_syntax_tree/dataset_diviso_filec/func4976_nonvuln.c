bool CIRCNetwork::IsIRCConnected() const {
    const CIRCSock* pSock = GetIRCSock();
    return (pSock && pSock->IsAuthed());
}