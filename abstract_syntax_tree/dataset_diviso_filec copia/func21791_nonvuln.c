int GetNumBlocksOfPeers()
{
    return std::max(cPeerBlockCounts.median(), Checkpoints::GetTotalBlocksEstimate());
}