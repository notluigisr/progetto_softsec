TEST_F(SQLiteUtilTests, test_column_type_determination) {
  
  testTypesExpected("STR",
                    TypeMap({{"STR", INTEGER_TYPE}}));
  
  testTypesExpected("STR",
                    TypeMap({{"STR", TEXT_TYPE}}));
  
  testTypesExpected("STR",
                    TypeMap({{"STR", DOUBLE_TYPE}}));
  
  testTypesExpected("STR",
                    TypeMap({{"STR", INTEGER_TYPE}}));
  
  
  
  testTypesExpected(
      "STR"
      "STR"
      "STR",
      TypeMap({{"STR", DOUBLE_TYPE}}));
}