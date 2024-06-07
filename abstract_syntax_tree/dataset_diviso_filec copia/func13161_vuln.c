static inline bool isMountable(const RemoteFsDevice::Details &d)
{
    return RemoteFsDevice::constSshfsProtocol==d.url.scheme() ||
           RemoteFsDevice::constSambaProtocol==d.url.scheme() || RemoteFsDevice::constSambaAvahiProtocol==d.url.scheme();
}