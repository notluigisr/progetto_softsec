static inline bool isValid(const RemoteFsDevice::Details &d)
{
    return d.isLocalFile() || RemoteFsDevice::constSshfsProtocol==d.url.scheme() ||
           RemoteFsDevice::constSambaProtocol==d.url.scheme() || RemoteFsDevice::constSambaAvahiProtocol==d.url.scheme();
}