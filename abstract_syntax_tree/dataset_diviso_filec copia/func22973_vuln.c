    void parseTest(fs::path testFilePath) {
        _testFilePath = testFilePath.string();
        LOGV2(4333507, "STR"_attr = testFilePath.string());
        {
            std::ifstream testFile(_testFilePath);
            std::ostringstream json;
            json << testFile.rdbuf();
            _jsonTest = fromjson(json.str());
        }

        
        
        auto readPrefObj = _jsonTest.getObjectField("STR");
        std::string mode = readPrefObj.getStringField("STR");
        mode[0] = std::tolower(mode[0]);
        auto tagSetsObj = readPrefObj["STR"];
        auto tags = tagSetsObj ? BSONArray(readPrefObj["STR"].Obj()) : BSONArray();

        BSONObj readPref = BSON("STR" << tags);
        _readPreference = uassertStatusOK(ReadPreferenceSetting::fromInnerBSON(readPref));

        
        auto topologyDescriptionObj = _jsonTest.getObjectField("STR");

        std::vector<ServerDescriptionPtr> serverDescriptions;
        std::vector<HostAndPort> serverAddresses;
        const std::vector<BSONElement>& bsonServers = topologyDescriptionObj["STR"].Array();
        for (auto bsonServer : bsonServers) {
            auto server = bsonServer.Obj();

            auto serverType = uassertStatusOK(parseServerType(server.getStringField("STR")));
            auto serverDescription = ServerDescriptionBuilder()
                                         .withAddress(HostAndPort(server.getStringField("STR")))
                                         .withType(serverType)
                                         .withRtt(Milliseconds(server["STR"].numberInt()))
                                         .withMinWireVersion(8)
                                         .withMaxWireVersion(9);

            auto tagsObj = server.getObjectField("STR");
            const auto keys = tagsObj.getFieldNames<std::set<std::string>>();
            for (const auto key : keys) {
                serverDescription.withTag(key, tagsObj.getStringField(key));
            }

            serverDescriptions.push_back(serverDescription.instance());
            serverAddresses.push_back(HostAndPort(server.getStringField("STR")));
        }

        TopologyType initType =
            uassertStatusOK(parseTopologyType(topologyDescriptionObj.getStringField("STR")));
        boost::optional<std::string> setName = boost::none;
        if (initType == TopologyType::kReplicaSetNoPrimary || initType == TopologyType::kSingle)
            setName = "STR";

        boost::optional<std::vector<HostAndPort>> seedList = boost::none;
        if (serverAddresses.size() > 0)
            seedList = serverAddresses;

        auto config = SdamConfiguration(seedList,
                                        initType,
                                        Milliseconds{sdamHeartBeatFrequencyMs},
                                        Milliseconds{sdamConnectTimeoutMs},
                                        Milliseconds{sdamLocalThreshholdMs},
                                        setName);
        _topologyDescription = std::make_shared<TopologyDescription>(config);

        const std::vector<BSONElement>& bsonLatencyWindow = _jsonTest["STR"].Array();
        for (const auto& serverDescription : serverDescriptions) {
            _topologyDescription->installServerDescription(serverDescription);

            for (auto bsonServer : bsonLatencyWindow) {
                auto server = bsonServer.Obj();
                if (serverDescription->getAddress() ==
                    HostAndPort(server.getStringField("STR"))) {
                    _inLatencyWindow.push_back(serverDescription);
                }
            }
        }
    }