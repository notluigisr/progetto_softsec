TEST_F(ServerSelectorTestFixture, ShouldFilterByLastWriteTime) {
    TopologyStateMachine stateMachine(sdamConfiguration);
    auto topologyDescription = std::make_shared<TopologyDescription>(sdamConfiguration);

    const int MAX_STALENESS = 90;
    const auto ninetySeconds = Seconds(MAX_STALENESS);
    const auto now = Date_t::now();


    const auto d0 = now - Milliseconds(1000);
    const auto s0 = ServerDescriptionBuilder()
                        .withAddress(HostAndPort("STR"))
                        .withType(ServerType::kRSPrimary)
                        .withRtt(sdamConfiguration.getLocalThreshold())
                        .withSetName("STR")
                        .withHost(HostAndPort("STR"))
                        .withHost(HostAndPort("STR"))
                        .withHost(HostAndPort("STR"))
                        .withMinWireVersion(WireVersion::SUPPORTS_OP_MSG)
                        .withMaxWireVersion(WireVersion::LATEST_WIRE_VERSION)
                        .withLastUpdateTime(now)
                        .withLastWriteDate(d0)
                        .instance();
    stateMachine.onServerDescription(*topologyDescription, s0);

    const auto d1 = now - Milliseconds(1000 * 5);
    const auto s1 = ServerDescriptionBuilder()
                        .withAddress(HostAndPort("STR"))
                        .withType(ServerType::kRSSecondary)
                        .withRtt(sdamConfiguration.getLocalThreshold())
                        .withSetName("STR")
                        .withMinWireVersion(WireVersion::SUPPORTS_OP_MSG)
                        .withMaxWireVersion(WireVersion::LATEST_WIRE_VERSION)
                        .withLastUpdateTime(now)
                        .withLastWriteDate(d1)
                        .instance();
    stateMachine.onServerDescription(*topologyDescription, s1);

    
    const auto d2 = now - ninetySeconds - ninetySeconds;
    const auto s2 = ServerDescriptionBuilder()
                        .withAddress(HostAndPort("STR"))
                        .withType(ServerType::kRSSecondary)
                        .withRtt(sdamConfiguration.getLocalThreshold())
                        .withSetName("STR")
                        .withMinWireVersion(WireVersion::SUPPORTS_OP_MSG)
                        .withMaxWireVersion(WireVersion::LATEST_WIRE_VERSION)
                        .withLastUpdateTime(now)
                        .withLastWriteDate(d2)
                        .instance();
    stateMachine.onServerDescription(*topologyDescription, s2);

    const auto readPref =
        ReadPreferenceSetting(ReadPreference::Nearest, TagSets::emptySet, ninetySeconds);

    std::map<HostAndPort, int> frequencyInfo{
        {HostAndPort("STR"), 0}};
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        auto server = selector.selectServer(topologyDescription, readPref);

        if (server) {
            frequencyInfo[(*server)->getAddress()]++;
        }
    }

    ASSERT(frequencyInfo[HostAndPort("STR")]);
    ASSERT(frequencyInfo[HostAndPort("STR")]);
    ASSERT_FALSE(frequencyInfo[HostAndPort("STR")]);
}