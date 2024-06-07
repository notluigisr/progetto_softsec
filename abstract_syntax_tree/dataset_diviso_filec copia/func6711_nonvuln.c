TEST(WriterTest, PadWString) {
  EXPECT_EQ(L"STR", 8)).str());
  EXPECT_EQ(L"STR", 10, '*')).str());
  EXPECT_EQ(L"STR", 10, L'*')).str());
}