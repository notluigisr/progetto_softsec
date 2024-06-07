ProcessUDPHeader(tTcpIpPacketParsingResult _res, PVOID pIpHeader, ULONG len, USHORT ipHeaderSize)
{
    tTcpIpPacketParsingResult res = _res;
    ULONG udpDataStart = ipHeaderSize + sizeof(UDPHeader);
    res.xxpStatus = ppresXxpIncomplete;
    res.TcpUdp = ppresIsUDP;
    res.XxpIpHeaderSize = udpDataStart;
    if (len >= udpDataStart)
    {
        UDPHeader *pUdpHeader = (UDPHeader *)RtlOffsetToPointer(pIpHeader, ipHeaderSize);
        USHORT datagramLength = swap_short(pUdpHeader->udp_length);
        res.xxpStatus = ppresXxpKnown;
        
        DPrintf(2, ("STR", len, datagramLength));
    }
    return res;
}