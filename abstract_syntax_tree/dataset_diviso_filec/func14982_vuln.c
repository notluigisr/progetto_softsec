TEST_F(ServerSelectorTestFixture, ShouldSelectRandomlyWhenMultipleOptionsAreAvailable) {
    TopologyStateMachine stateMachine(sdamConfiguration);
    auto topologyDescription = std::make_shared<TopologyDescription>(sdamConfiguration);

    const auto s0Latency = Milliseconds(1);
    auto primary = ServerDescriptionBuilder()
                       .withAddress(HostAndPort("STR"))
                       .withType(ServerType::kRSPrimary)
                       .withLastUpdateTime(Date_t::now())
                       .withLastWriteDate(Date_t::now())
                       .withRtt(s0Latency)
                       .withSetName("STR")
                       .withHost(HostAndPort("STR"))
                       .withHost(HostAndPort("STR"))
                       .withHost(HostAndPort("STR"))
                       .withHost(HostAndPort("STR"))
                       .withMinWireVersion(WireVersion::SUPPORTS_OP_MSG)
                       .withMaxWireVersion(WireVersion::LATEST_WIRE_VERSION)
                       .instance();
    stateMachine.onServerDescription(*topologyDescription, primary);

    const auto s1Latency = Milliseconds((s0Latency + sdamConfiguration.getLocalThreshold()) / 2);
    auto secondaryInLatencyWindow =
        make_with_latency(s1Latency, HostAndPort("STR"), ServerType::kRSSecondary);
    stateMachine.onServerDescription(*topologyDescription, secondaryInLatencyWindow);

    
    const auto s2Latency = s0Latency + sdamConfiguration.getLocalThreshold();
    auto secondaryOnBoundaryOfLatencyWindow =
        make_with_latency(s2Latency, HostAndPort("STR"), ServerType::kRSSecondary);
    stateMachine.onServerDescription(*topologyDescription, secondaryOnBoundaryOfLatencyWindow);

    
    const auto s3Latency = s2Latency + Milliseconds(10);
    auto secondaryTooFar =
        make_with_latency(s3Latency, HostAndPort("STR"), ServerType::kRSSecondary);
    stateMachine.onServerDescription(*topologyDescription, secondaryTooFar);

    std::map<HostAndPort, int> frequencyInfo{{HostAndPort("STR"), 0},
                                             {HostAndPort("STR"), 0},
                                             {HostAndPort("STR"), 0},
                                             {HostAndPort("STR"), 0}};
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        auto server = selector.selectServer(topologyDescription,
                                            ReadPreferenceSetting(ReadPreference::Nearest));
        if (server) {
            frequencyInfo[(*server)->getAddress()]++;
        }
    }

    ASSERT(frequencyInfo[HostAndPort("STR")]);
    ASSERT(frequencyInfo[HostAndPort("STR")]);
    ASSERT(frequencyInfo[HostAndPort("STR")]);
    ASSERT_FALSE(frequencyInfo[HostAndPort("STR")]);
}