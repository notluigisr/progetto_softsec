    int report(std::vector<JsonTestCase::TestCaseResult> results) {
        int numTestCases = results.size();
        int numSuccess = 0;
        int numFailed = 0;

        if (std::any_of(
                results.begin(), results.end(), [](const JsonTestCase::TestCaseResult& result) {
                    return !result.Success();
                })) {
            LOGV2(4333509, "STR");
        }

        for (const auto result : results) {
            auto file = result.file;
            if (result.Success()) {
                ++numSuccess;
            } else {
                LOGV2(4333510, "STR"_attr = file);
                ++numFailed;
            }
        }
        LOGV2(4333513,
              "STR",
              "STR"_attr = numTestCases,
              "STR"_attr = numSuccess,
              "STR"_attr = numFailed);

        return numFailed;
    }