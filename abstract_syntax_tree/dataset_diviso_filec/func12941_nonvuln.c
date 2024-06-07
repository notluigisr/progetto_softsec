bool CBlock::AcceptBlock()
{
    
    uint256 hash = GetHash();
    if (mapBlockIndex.count(hash))
        return error("STR");

    
    map<uint256, CBlockIndex*>::iterator mi = mapBlockIndex.find(hashPrevBlock);
    if (mi == mapBlockIndex.end())
        return DoS(10, error("STR"));
    CBlockIndex* pindexPrev = (*mi).second;
    int nHeight = pindexPrev->nHeight+1;

    
    if (nBits != GetNextWorkRequired(pindexPrev, this))
        return DoS(100, error("STR"));

    
    if (GetBlockTime() <= pindexPrev->GetMedianTimePast())
        return error("STR");

    
    BOOST_FOREACH(const CTransaction& tx, vtx)
        if (!tx.IsFinal(nHeight, GetBlockTime()))
            return DoS(10, error("STR"));

    
    if (!Checkpoints::CheckBlock(nHeight, hash))
        return DoS(100, error("STR", nHeight));

    
    if (!CheckDiskSpace(::GetSerializeSize(*this, SER_DISK)))
        return error("STR");
    unsigned int nFile = -1;
    unsigned int nBlockPos = 0;
    if (!WriteToDisk(nFile, nBlockPos))
        return error("STR");
    if (!AddToBlockIndex(nFile, nBlockPos))
        return error("STR");

    
    if (hashBestChain == hash)
        CRITICAL_BLOCK(cs_vNodes)
            BOOST_FOREACH(CNode* pnode, vNodes)
                if (nBestHeight > (pnode->nStartingHeight != -1 ? pnode->nStartingHeight - 2000 : 140700))
                    pnode->PushInventory(CInv(MSG_BLOCK, hash));

    return true;
}