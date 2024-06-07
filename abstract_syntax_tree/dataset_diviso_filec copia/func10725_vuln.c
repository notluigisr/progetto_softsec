TEST_F(HeaderTableTests, set_capacity) {
  HPACKHeader accept("STR");
  uint32_t max = 10;
  uint32_t capacity = accept.bytes() * max;
  HeaderTable table(capacity);

  
  for (size_t i = 0; i < max; i++) {
    EXPECT_EQ(table.add(accept), true);
  }
  
  table.setCapacity(capacity / 2);
  EXPECT_EQ(table.size(), max / 2);
  EXPECT_EQ(table.bytes(), capacity / 2);
}