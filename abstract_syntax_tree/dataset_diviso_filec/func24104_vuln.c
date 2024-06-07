TEST_F(ServerSelectorTestFixture, ShouldFilterCorrectlyByLatencyWindow) {
    const auto delta = Milliseconds(10);
    const auto windowWidth = Milliseconds(100);
    const auto lowerBound = Milliseconds(100);

    auto window = LatencyWindow(lowerBound, windowWidth);

    std::vector<ServerDescriptionPtr> servers = {
        make_with_latency(window.lower - delta, HostAndPort("STR")),
        make_with_latency(window.lower, HostAndPort("STR")),
        make_with_latency(window.lower + delta, HostAndPort("STR")),
        make_with_latency(window.upper, HostAndPort("STR")),
        make_with_latency(window.upper + delta, HostAndPort("STR"))};

    window.filterServers(&servers);

    ASSERT_EQ(3, servers.size());
    ASSERT_EQ(HostAndPort("STR"), servers[0]->getAddress());
    ASSERT_EQ(HostAndPort("STR"), servers[1]->getAddress());
    ASSERT_EQ(HostAndPort("STR"), servers[2]->getAddress());
}