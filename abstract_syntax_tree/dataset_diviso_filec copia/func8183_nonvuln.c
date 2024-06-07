TEST_P(Security, BuiltinAuthenticationAndCryptoPlugin_reliable_payload_ok)
{
    PubSubReader<HelloWorldType> reader(TEST_TOPIC_NAME);
    PubSubWriter<HelloWorldType> writer(TEST_TOPIC_NAME);

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

    reader.history_depth(10).
            reliability(eprosima::fastrtps::RELIABLE_RELIABILITY_QOS).
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

    writer.history_depth(10).
            property_policy(pub_part_property_policy).
            entity_property_policy(pub_property_policy).init();

    ASSERT_TRUE(writer.isInitialized());

    
    reader.waitAuthorized();
    writer.waitAuthorized();

    
    writer.wait_discovery();
    reader.wait_discovery();

    auto data = default_helloworld_data_generator();

    reader.startReception(data);

    
    writer.send(data);
    
    ASSERT_TRUE(data.empty());
    
    reader.block_for_all();
}