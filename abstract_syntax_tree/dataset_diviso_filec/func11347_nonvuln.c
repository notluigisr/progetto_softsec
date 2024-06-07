void NumberFormatTest::runIndexedTest( int32_t index, UBool exec, const char* &name, char*  )
{
  TESTCASE_AUTO_BEGIN;
  TESTCASE_AUTO(TestCurrencySign);
  TESTCASE_AUTO(TestCurrency);
  TESTCASE_AUTO(TestParse);
  TESTCASE_AUTO(TestRounding487);
  TESTCASE_AUTO(TestQuotes);
  TESTCASE_AUTO(TestExponential);
  TESTCASE_AUTO(TestPatterns);

  
  TESTCASE_AUTO(TestExponent);
  TESTCASE_AUTO(TestScientific);
  TESTCASE_AUTO(TestPad);
  TESTCASE_AUTO(TestPatterns2);
  TESTCASE_AUTO(TestSecondaryGrouping);
  TESTCASE_AUTO(TestSurrogateSupport);
  TESTCASE_AUTO(TestAPI);

  TESTCASE_AUTO(TestCurrencyObject);
  TESTCASE_AUTO(TestCurrencyPatterns);
  
  TESTCASE_AUTO(TestWhiteSpaceParsing);
  TESTCASE_AUTO(TestComplexCurrency);  
  TESTCASE_AUTO(TestRegCurrency);
  TESTCASE_AUTO(TestSymbolsWithBadLocale);
  TESTCASE_AUTO(TestAdoptDecimalFormatSymbols);

  TESTCASE_AUTO(TestScientific2);
  TESTCASE_AUTO(TestScientificGrouping);
  TESTCASE_AUTO(TestInt64);

  TESTCASE_AUTO(TestPerMill);
  TESTCASE_AUTO(TestIllegalPatterns);
  TESTCASE_AUTO(TestCases);

  TESTCASE_AUTO(TestCurrencyNames);
  TESTCASE_AUTO(TestCurrencyAmount);
  TESTCASE_AUTO(TestCurrencyUnit);
  TESTCASE_AUTO(TestCoverage);
  TESTCASE_AUTO(TestLocalizedPatternSymbolCoverage);
  TESTCASE_AUTO(TestJB3832);
  TESTCASE_AUTO(TestHost);
  TESTCASE_AUTO(TestHostClone);
  TESTCASE_AUTO(TestCurrencyFormat);
  TESTCASE_AUTO(TestRounding);
  TESTCASE_AUTO(TestNonpositiveMultiplier);
  TESTCASE_AUTO(TestNumberingSystems);
  TESTCASE_AUTO(TestSpaceParsing);
  TESTCASE_AUTO(TestMultiCurrencySign);
  TESTCASE_AUTO(TestCurrencyFormatForMixParsing);
  TESTCASE_AUTO(TestMismatchedCurrencyFormatFail);
  TESTCASE_AUTO(TestDecimalFormatCurrencyParse);
  TESTCASE_AUTO(TestCurrencyIsoPluralFormat);
  TESTCASE_AUTO(TestCurrencyParsing);
  TESTCASE_AUTO(TestParseCurrencyInUCurr);
  TESTCASE_AUTO(TestFormatAttributes);
  TESTCASE_AUTO(TestFieldPositionIterator);
  TESTCASE_AUTO(TestDecimal);
  TESTCASE_AUTO(TestCurrencyFractionDigits);
  TESTCASE_AUTO(TestExponentParse);
  TESTCASE_AUTO(TestExplicitParents);
  TESTCASE_AUTO(TestLenientParse);
  TESTCASE_AUTO(TestAvailableNumberingSystems);
  TESTCASE_AUTO(TestRoundingPattern);
  TESTCASE_AUTO(Test9087);
  TESTCASE_AUTO(TestFormatFastpaths);
  TESTCASE_AUTO(TestFormattableSize);
  TESTCASE_AUTO(TestUFormattable);
  TESTCASE_AUTO(TestSignificantDigits);
  TESTCASE_AUTO(TestShowZero);
  TESTCASE_AUTO(TestCompatibleCurrencies);
  TESTCASE_AUTO(TestBug9936);
  TESTCASE_AUTO(TestParseNegativeWithFaLocale);
  TESTCASE_AUTO(TestParseNegativeWithAlternateMinusSign);
  TESTCASE_AUTO(TestCustomCurrencySignAndSeparator);
  TESTCASE_AUTO(TestParseSignsAndMarks);
  TESTCASE_AUTO(Test10419RoundingWith0FractionDigits);
  TESTCASE_AUTO(Test10468ApplyPattern);
  TESTCASE_AUTO(TestRoundingScientific10542);
  TESTCASE_AUTO(TestZeroScientific10547);
  TESTCASE_AUTO(TestAccountingCurrency);
  TESTCASE_AUTO(TestEquality);
  TESTCASE_AUTO(TestCurrencyUsage);
  TESTCASE_AUTO(TestDoubleLimit11439);
  TESTCASE_AUTO(TestGetAffixes);
  TESTCASE_AUTO(TestToPatternScientific11648);
  TESTCASE_AUTO(TestBenchmark);
  TESTCASE_AUTO(TestCtorApplyPatternDifference);
  TESTCASE_AUTO(TestFractionalDigitsForCurrency);
  TESTCASE_AUTO(TestFormatCurrencyPlural);
  TESTCASE_AUTO(Test11868);
  TESTCASE_AUTO(Test11739_ParseLongCurrency);
  TESTCASE_AUTO(Test13035_MultiCodePointPaddingInPattern);
  TESTCASE_AUTO(Test13737_ParseScientificStrict);
  TESTCASE_AUTO(Test10727_RoundingZero);
  TESTCASE_AUTO(Test11376_getAndSetPositivePrefix);
  TESTCASE_AUTO(Test11475_signRecognition);
  TESTCASE_AUTO(Test11640_getAffixes);
  TESTCASE_AUTO(Test11649_toPatternWithMultiCurrency);
  TESTCASE_AUTO(Test13327_numberingSystemBufferOverflow);
  TESTCASE_AUTO(Test13391_chakmaParsing);
  TESTCASE_AUTO(Test11735_ExceptionIssue);
  TESTCASE_AUTO(Test11035_FormatCurrencyAmount);
  TESTCASE_AUTO(Test11318_DoubleConversion);
  TESTCASE_AUTO(TestParsePercentRegression);
  TESTCASE_AUTO(TestMultiplierWithScale);
  TESTCASE_AUTO(TestFastFormatInt32);
  TESTCASE_AUTO(Test11646_Equality);
  TESTCASE_AUTO(TestParseNaN);
  TESTCASE_AUTO(Test11897_LocalizedPatternSeparator);
  TESTCASE_AUTO(Test13055_PercentageRounding);
  TESTCASE_AUTO(Test11839);
  TESTCASE_AUTO(Test10354);
  TESTCASE_AUTO(Test11645_ApplyPatternEquality);
  TESTCASE_AUTO(Test12567);
  TESTCASE_AUTO(Test11626_CustomizeCurrencyPluralInfo);
  TESTCASE_AUTO(Test20073_StrictPercentParseErrorIndex);
  TESTCASE_AUTO(Test13056_GroupingSize);
  TESTCASE_AUTO(Test11025_CurrencyPadding);
  TESTCASE_AUTO(Test11648_ExpDecFormatMalPattern);
  TESTCASE_AUTO(Test11649_DecFmtCurrencies);
  TESTCASE_AUTO(Test13148_ParseGroupingSeparators);
  TESTCASE_AUTO(Test12753_PatternDecimalPoint);
  TESTCASE_AUTO(Test11647_PatternCurrencySymbols);
  TESTCASE_AUTO(Test11913_BigDecimal);
  TESTCASE_AUTO(Test11020_RoundingInScientificNotation);
  TESTCASE_AUTO(Test11640_TripleCurrencySymbol);
  TESTCASE_AUTO(Test13763_FieldPositionIteratorOffset);
  TESTCASE_AUTO(Test13777_ParseLongNameNonCurrencyMode);
  TESTCASE_AUTO(Test13804_EmptyStringsWhenParsing);
  TESTCASE_AUTO(Test20037_ScientificIntegerOverflow);
  TESTCASE_AUTO(Test13840_ParseLongStringCrash);
  TESTCASE_AUTO(Test13850_EmptyStringCurrency);
  TESTCASE_AUTO_END;
}