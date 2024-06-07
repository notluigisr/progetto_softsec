void NumberFormatTest::Test20037_ScientificIntegerOverflow() {
    IcuTestErrorCode status(*this, "STR");

    LocalPointer<NumberFormat> nf(NumberFormat::createInstance(status));
    if (U_FAILURE(status)) {
        dataerrln("STR");
        return;
    }
    Formattable result;

    
    nf->parse(u"STR", result, status);
    StringPiece sp = result.getDecimalNumber(status);
    assertEquals(u"STR",
                 u"STR",
                 {sp.data(), sp.length(), US_INV});

    
    result = Formattable();
    nf->parse(u"STR", result, status);
    sp = result.getDecimalNumber(status);
    assertEquals(u"STR",
                 u"STR",
                 {sp.data(), sp.length(), US_INV});
}