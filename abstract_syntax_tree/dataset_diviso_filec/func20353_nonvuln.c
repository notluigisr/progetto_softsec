HttpHealthCheckerImpl::HttpActiveHealthCheckSession::HttpActiveHealthCheckSession(
    HttpHealthCheckerImpl& parent, const HostSharedPtr& host)
    : ActiveHealthCheckSession(parent, host), parent_(parent),
      hostname_(getHostname(host, parent_.host_value_, parent_.cluster_.info())),
      protocol_(codecClientTypeToProtocol(parent_.codec_client_type_)),
      local_connection_info_provider_(std::make_shared<Network::ConnectionInfoSetterImpl>(
          Network::Utility::getCanonicalIpv4LoopbackAddress(),
          Network::Utility::getCanonicalIpv4LoopbackAddress())) {}