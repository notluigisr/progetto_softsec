  static void expectSlices(std::vector<std::vector<int>> buffer_list, OwnedImpl& buffer) {
    const auto& buffer_slices = buffer.describeSlicesForTest();
    for (uint64_t i = 0; i < buffer_slices.size(); i++) {
      EXPECT_EQ(buffer_slices[i].data, buffer_list[i][0]);
      EXPECT_EQ(buffer_slices[i].reservable, buffer_list[i][1]);
      EXPECT_EQ(buffer_slices[i].capacity, buffer_list[i][2]);
    }
  }