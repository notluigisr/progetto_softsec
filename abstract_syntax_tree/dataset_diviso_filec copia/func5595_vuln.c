TEST_P(WasmTest, DivByZero) {
  Stats::IsolatedStoreImpl stats_store;
  Api::ApiPtr api = Api::createApiForTest(stats_store);
  Upstream::MockClusterManager cluster_manager;
  Event::DispatcherPtr dispatcher(api->allocateDispatcher());
  auto scope = Stats::ScopeSharedPtr(stats_store.createScope("STR"));
  NiceMock<LocalInfo::MockLocalInfo> local_info;
  auto name = "";
  auto root_id = "";
  auto vm_id = "";
  auto vm_configuration = "";
  auto plugin = std::make_shared<Extensions::Common::Wasm::Plugin>(
      name, root_id, vm_id, envoy::api::v2::core::TrafficDirection::UNSPECIFIED, local_info,
      nullptr);
  auto wasm = std::make_unique<Extensions::Common::Wasm::Wasm>(
      absl::StrCat("STR", GetParam()), vm_id, vm_configuration, plugin, scope,
      cluster_manager, *dispatcher);
  EXPECT_NE(wasm, nullptr);
  const auto code = TestEnvironment::readFileToStringForTest(TestEnvironment::substitute(
      "STR"));
  EXPECT_FALSE(code.empty());
  auto context = std::make_unique<TestContext>(wasm.get());
  EXPECT_CALL(*context, scriptLog_(spdlog::level::err, Eq("STR")));
  EXPECT_TRUE(wasm->initialize(code, false));
  wasm->setContext(context.get());

  if (GetParam() == "STR") {
    EXPECT_THROW_WITH_MESSAGE(
        context->onLog(), Extensions::Common::Wasm::WasmException,
        "STR");
  } else if (GetParam() == "STR") {
    EXPECT_THROW_WITH_REGEX(context->onLog(), Extensions::Common::Wasm::WasmException,
                            "STR");
  } else {
    ASSERT_FALSE(true); 
  }
}