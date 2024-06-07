ParaNdis_UpdateGuestOffloads(PARANDIS_ADAPTER *pContext, UINT64 Offloads)
{
    if (pContext->RSC.bHasDynamicConfig)
    {
        pContext->CXPath.SendControlMessage(VIRTIO_NET_CTRL_GUEST_OFFLOADS, VIRTIO_NET_CTRL_GUEST_OFFLOADS_SET,
                           &Offloads,
                           sizeof(Offloads),
                           NULL, 0, 2);
    }
}