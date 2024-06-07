void NumberFormatTest::Test13850_EmptyStringCurrency() {
    IcuTestErrorCode status(*this, "STR");

    struct TestCase {
        const char16_t* currencyArg;
        UErrorCode expectedError;
    } cases[] = {
        {u"", U_ZERO_ERROR},
        {u"STR", U_ILLEGAL_ARGUMENT_ERROR},
        {u"STR", U_ILLEGAL_ARGUMENT_ERROR},
        {nullptr, U_ZERO_ERROR},
        {u"STR", U_INVARIANT_CONVERSION_ERROR},
        {u"STR", U_ZERO_ERROR}
    };
    for (const auto& cas : cases) {
        UnicodeString message(u"STR");
        if (cas.currencyArg == nullptr) {
            message += u"STR";
        } else {
            message += UnicodeString(cas.currencyArg);
        }
        status.setScope(message);
        LocalPointer<NumberFormat> nf(NumberFormat::createCurrencyInstance("STR", status), status);
        if (status.errIfFailureAndReset()) { return; }
        UnicodeString actual;
        nf->format(1, actual, status);
        status.errIfFailureAndReset();
        assertEquals(u"STR", actual);
        nf->setCurrency(cas.currencyArg, status);
        if (status.expectErrorAndReset(cas.expectedError)) {
            
            continue;
        }
        nf->format(1, actual.remove(), status);
        assertEquals(u"STR", actual);
        status.errIfFailureAndReset();
    }
}