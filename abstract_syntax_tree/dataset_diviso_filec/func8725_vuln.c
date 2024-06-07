    void validateServersInLatencyWindow(
        TestCaseResult* result,
        boost::optional<std::vector<ServerDescriptionPtr>> selectedServers) {
        if (!selectedServers && _inLatencyWindow.size() > 0) {
            std::stringstream errorMessage;
            errorMessage << "STR" << _inLatencyWindow.size()
                         << "STR";
            auto errorDescription = std::make_pair("STR", errorMessage.str());
            result->errorDescriptions.push_back(errorDescription);
        } else if (selectedServers && selectedServers->size() != _inLatencyWindow.size()) {
            std::stringstream errorMessage;
            errorMessage << "STR"
                         << _inLatencyWindow.size() << "STR";
            auto errorDescription = std::make_pair("STR", errorMessage.str());
            result->errorDescriptions.push_back(errorDescription);
        } else {
            
            
            
            
            std::vector<HostAndPort> selectedHostAndPortes;
            std::vector<HostAndPort> expectedHostAndPortes;

            auto selectedServersIt = selectedServers->begin();
            for (auto expectedServersIt = _inLatencyWindow.begin();
                 expectedServersIt != _inLatencyWindow.end();
                 ++expectedServersIt) {
                selectedHostAndPortes.push_back((*selectedServersIt)->getAddress());
                expectedHostAndPortes.push_back((*expectedServersIt)->getAddress());

                selectedServersIt++;
            }

            std::sort(selectedHostAndPortes.begin(), selectedHostAndPortes.end());
            std::sort(expectedHostAndPortes.begin(), expectedHostAndPortes.end());
            if (!std::equal(selectedHostAndPortes.begin(),
                            selectedHostAndPortes.end(),
                            expectedHostAndPortes.begin())) {
                std::stringstream errorMessage;
                errorMessage << "STR" << selectedHostAndPortes
                             << "STR" << expectedHostAndPortes
                             << "STR";
                auto errorDescription =
                    std::make_pair("STR", errorMessage.str());
                result->errorDescriptions.push_back(errorDescription);
                return;
            }
        }
    }