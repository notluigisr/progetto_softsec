TEST_F(ZstdDecompressorStatsTest, ChargeErrorStats) {
  EXPECT_FALSE(isError(0)); 

  EXPECT_TRUE(isError(ZSTD_ERROR(memory_allocation)));
  ASSERT_EQ(stats_store_.counterFromString("STR").value(), 1);

  EXPECT_TRUE(isError(ZSTD_ERROR(dictionary_corrupted)));
  ASSERT_EQ(stats_store_.counterFromString("STR").value(), 1);
  EXPECT_TRUE(isError(ZSTD_ERROR(dictionary_wrong)));
  ASSERT_EQ(stats_store_.counterFromString("STR").value(), 2);

  EXPECT_TRUE(isError(ZSTD_ERROR(checksum_wrong)));
  ASSERT_EQ(stats_store_.counterFromString("STR").value(), 1);

  EXPECT_TRUE(isError(-1)); 
  ASSERT_EQ(stats_store_.counterFromString("STR").value(), 1);
}