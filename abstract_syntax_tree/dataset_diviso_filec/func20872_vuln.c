    std::vector<JsonTestCase::TestCaseResult> runTests() {
        std::vector<JsonTestCase::TestCaseResult> results;
        const auto testFiles = getTestFiles();
        for (auto jsonTest : testFiles) {
            auto testCase = [jsonTest]() -> std::unique_ptr<JsonTestCase> {
                if (jsonTest.string().find("STR")) {
                    return std::make_unique<JsonRttTestCase>(jsonTest);
                }
                return std::make_unique<JsonServerSelectionTestCase>(jsonTest);
            }();

            try {
                LOGV2(
                    4333508, "STR"_attr = testCase->FilePath());
                results.push_back(testCase->execute());
            } catch (const DBException& ex) {
                std::stringstream error;
                error << "STR" << ex.toString();
                std::string errorStr = error.str();
                results.push_back(JsonTestCase::TestCaseResult{
                    {std::make_pair("STR", errorStr)}, jsonTest.string()});
                std::cerr << errorStr;
            }
        }
        return results;
    }