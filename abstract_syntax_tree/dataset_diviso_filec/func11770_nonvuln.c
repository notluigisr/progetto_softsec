void TopologyManager::_publishTopologyDescriptionChanged(
    const TopologyDescriptionPtr& oldTopologyDescription,
    const TopologyDescriptionPtr& newTopologyDescription) const {
    if (_topologyEventsPublisher)
        _topologyEventsPublisher->onTopologyDescriptionChangedEvent(oldTopologyDescription,
                                                                    newTopologyDescription);
}