TEST_P(Security, BuiltinAuthenticationAndCryptoPlugin_besteffort_payload_data300kb)
{
    PubSubReader<Data1mbType> reader(TEST_TOPIC_NAME);
    PubSubWriter<Data1mbType> writer(TEST_TOPIC_NAME);

    PropertyPolicy pub_part_property_policy, sub_part_property_policy,
            pub_property_policy, sub_property_policy;

    sub_part_property_policy.properties().emplace_back(Property("STR",
            "STR"));
    sub_part_property_policy.properties().emplace_back(Property("STR",
            "STR"));
    sub_part_property_policy.properties().emplace_back(Property("STR",
            "STR"));
    sub_part_property_policy.properties().emplace_back(Property("STR",
            "STR"));
    sub_part_property_policy.properties().emplace_back(Property("STR",
            "STR"));
    sub_property_policy.properties().emplace_back("STR");

    reader.history_depth(5).
            property_policy(sub_part_property_policy).
            entity_property_policy(sub_property_policy).init();

    ASSERT_TRUE(reader.isInitialized());

    pub_part_property_policy.properties().emplace_back(Property("STR",
            "STR"));
    pub_part_property_policy.properties().emplace_back(Property("STR",
            "STR"));
    pub_part_property_policy.properties().emplace_back(Property("STR",
            "STR"));
    pub_part_property_policy.properties().emplace_back(Property("STR",
            "STR"));
    pub_part_property_policy.properties().emplace_back(Property("STR",
            "STR"));
    pub_property_policy.properties().emplace_back("STR");

    
    
    uint32_t bytesPerPeriod = 65536;
    uint32_t periodInMs = 500;

    writer.history_depth(5).
            reliability(eprosima::fastrtps::BEST_EFFORT_RELIABILITY_QOS).
            asynchronously(eprosima::fastrtps::ASYNCHRONOUS_PUBLISH_MODE).
            add_throughput_controller_descriptor_to_pparams(bytesPerPeriod, periodInMs).
            property_policy(pub_part_property_policy).
            entity_property_policy(pub_property_policy).init();

    ASSERT_TRUE(writer.isInitialized());

    
    reader.waitAuthorized();
    writer.waitAuthorized();

    
    writer.wait_discovery();
    reader.wait_discovery();

    auto data = default_data300kb_data_generator(5);

    reader.startReception(data);

    
    writer.send(data);
    
    ASSERT_TRUE(data.empty());
    
    reader.block_for_at_least(2);
}