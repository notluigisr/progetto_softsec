bool isStaleTopologyVersion(boost::optional<TopologyVersion> lastTopologyVersion,
                            boost::optional<TopologyVersion> newTopologyVersion) {
    if (lastTopologyVersion && newTopologyVersion &&
        ((lastTopologyVersion->getProcessId() == newTopologyVersion->getProcessId()) &&
         (lastTopologyVersion->getCounter() > newTopologyVersion->getCounter()))) {
        return true;
    }

    return false;
}