TEST_F(LuaHeaderMapWrapperTest, Methods) {
  const std::string SCRIPT{R"EOF(
    function callMe(object)
      object:add("STR")
      testPrint(object:get("STR"))

      object:add("STR")
      object:add("STR")

      for key, value in pairs(object) do
        testPrint(string.format("STR", key, value))
      end

      object:remove("STR")
      for key, value in pairs(object) do
        testPrint(string.format("STR", key, value))
      end
    end
  )EOF"};

  InSequence s;
  setup(SCRIPT);

  Http::TestRequestHeaderMapImpl headers;
  HeaderMapWrapper::create(coroutine_->luaState(), headers, []() { return true; });
  EXPECT_CALL(printer_, testPrint("STR"));
  EXPECT_CALL(printer_, testPrint("STR"));
  EXPECT_CALL(printer_, testPrint("STR"));
  EXPECT_CALL(printer_, testPrint("STR"));
  EXPECT_CALL(printer_, testPrint("STR"));
  EXPECT_CALL(printer_, testPrint("STR"));
  start("STR");
}