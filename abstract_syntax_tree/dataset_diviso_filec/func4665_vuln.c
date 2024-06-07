void ListenerImpl::listenCallback(evconnlistener*, evutil_socket_t fd, sockaddr* remote_addr,
                                  int remote_addr_len, void* arg) {
  ListenerImpl* listener = static_cast<ListenerImpl*>(arg);

  
  IoHandlePtr io_handle = SocketInterfaceSingleton::get().socket(fd);

  
  
  const Address::InstanceConstSharedPtr& local_address =
      listener->local_address_ ? listener->local_address_ : io_handle->localAddress();

  
  
  
  
  
  
  
  const Address::InstanceConstSharedPtr& remote_address =
      (remote_addr->sa_family == AF_UNIX)
          ? io_handle->peerAddress()
          : Address::addressFromSockAddr(*reinterpret_cast<const sockaddr_storage*>(remote_addr),
                                         remote_addr_len,
                                         local_address->ip()->version() == Address::IpVersion::v6);
  listener->cb_.onAccept(
      std::make_unique<AcceptedSocketImpl>(std::move(io_handle), local_address, remote_address));
}