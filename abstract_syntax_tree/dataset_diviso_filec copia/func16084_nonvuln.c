TEST_P(Security, BuiltinAuthenticationAndAccessAndCryptoPlugin_PermissionsEnableDiscoveryEnableAccessNone_validation_ok_enable_discovery_disable_access_encrypt)

{
    PubSubReader<HelloWorldType> reader(TEST_TOPIC_NAME);
    PubSubWriter<HelloWorldType> writer(TEST_TOPIC_NAME);
    std::string governance_file("STR");

    BuiltinAuthenticationAndAccessAndCryptoPlugin_Permissions_validation_ok_common(reader, writer, governance_file);
}