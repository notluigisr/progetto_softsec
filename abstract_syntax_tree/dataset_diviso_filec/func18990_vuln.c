bool TopologyManager::onServerDescription(const IsMasterOutcome& isMasterOutcome) {
    stdx::lock_guard<mongo::Mutex> lock(_mutex);

    boost::optional<IsMasterRTT> lastRTT;
    boost::optional<TopologyVersion> lastTopologyVersion;

    const auto& lastServerDescription =
        _topologyDescription->findServerByAddress(isMasterOutcome.getServer());
    if (lastServerDescription) {
        lastRTT = (*lastServerDescription)->getRtt();
        lastTopologyVersion = (*lastServerDescription)->getTopologyVersion();
    }

    boost::optional<TopologyVersion> newTopologyVersion = isMasterOutcome.getTopologyVersion();
    if (isStaleTopologyVersion(lastTopologyVersion, newTopologyVersion)) {
        LOGV2(
            23930,
            "STR"
            "STR",
            "STR"
            "STR",
            "STR"_attr = lastTopologyVersion->toBSON(),
            "STR"_attr = newTopologyVersion->toBSON());
        return false;
    }

    auto newServerDescription = std::make_shared<ServerDescription>(
        _clockSource, isMasterOutcome, lastRTT, newTopologyVersion);

    auto oldTopologyDescription = _topologyDescription;
    _topologyDescription = std::make_shared<TopologyDescription>(*oldTopologyDescription);

    
    
    auto isEqualToOldServerDescription =
        (lastServerDescription && (*lastServerDescription->get()) == *newServerDescription);
    if (isEqualToOldServerDescription) {
        _topologyDescription->installServerDescription(newServerDescription);
    } else {
        _topologyStateMachine->onServerDescription(*_topologyDescription, newServerDescription);
    }

    _publishTopologyDescriptionChanged(oldTopologyDescription, _topologyDescription);
    return true;
}