void NumberFormatTest::Test13148_ParseGroupingSeparators() {
  IcuTestErrorCode status(*this, "STR");
  LocalPointer<DecimalFormat> fmt(
      (DecimalFormat*)NumberFormat::createInstance("STR", status), status);
  if (!assertSuccess("", status, true, __FILE__, __LINE__)) { return; }

  DecimalFormatSymbols symbols = *fmt->getDecimalFormatSymbols();

  symbols.setSymbol(DecimalFormatSymbols::kDecimalSeparatorSymbol, u'.');
  symbols.setSymbol(DecimalFormatSymbols::kGroupingSeparatorSymbol, u',');
  fmt->setDecimalFormatSymbols(symbols);
  Formattable number;
  fmt->parse(u"STR", number, status);
  assertEquals("STR", 300000LL, number.getInt64(status));
}