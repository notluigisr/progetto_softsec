void TopologyManager::onServerRTTUpdated(HostAndPort hostAndPort, IsMasterRTT rtt) {
    {
        stdx::lock_guard<mongo::Mutex> lock(_mutex);

        auto oldServerDescription = _topologyDescription->findServerByAddress(hostAndPort);
        if (oldServerDescription) {
            auto newServerDescription = (*oldServerDescription)->cloneWithRTT(rtt);

            auto oldTopologyDescription = _topologyDescription;
            _topologyDescription = std::make_shared<TopologyDescription>(*_topologyDescription);
            _topologyDescription->installServerDescription(newServerDescription);

            _publishTopologyDescriptionChanged(oldTopologyDescription, _topologyDescription);

            return;
        }
    }
    
    LOGV2(4333201,
          "STR",
          "STR",
          "STR"_attr = hostAndPort,
          "STR"_attr = getTopologyDescription()->getSetName());
}