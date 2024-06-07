TEST_P(Security, BuiltinAuthenticationAndAccessAndCryptoPlugin_PermissionsEnableDiscoveryDisableAccessEncrypt_validation_ok_enable_discovery_enable_access_none)

{
    PubSubReader<HelloWorldType> reader(TEST_TOPIC_NAME);
    PubSubWriter<HelloWorldType> writer(TEST_TOPIC_NAME);
    std::string governance_file("STR");

    BuiltinAuthenticationAndAccessAndCryptoPlugin_Permissions_validation_ok_common(reader, writer, governance_file);
}