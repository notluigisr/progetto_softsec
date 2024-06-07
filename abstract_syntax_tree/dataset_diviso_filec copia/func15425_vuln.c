    TestCaseResult execute() {
        LOGV2(4333504, "STR"_attr = _testFilePath);

        SdamServerSelector serverSelector(
            SdamConfiguration(std::vector<HostAndPort>{HostAndPort("STR")}));
        auto selectedServers = serverSelector.selectServers(_topologyDescription, _readPreference);

        TestCaseResult result{{}, _testFilePath};
        validateServersInLatencyWindow(&result, selectedServers);

        if (!result.Success()) {
            LOGV2(4333505, "STR"_attr = _testFilePath);
        }

        return result;
    }