TEST_F(OwnedImplTest, ReserveCommitReuse) {
  Buffer::OwnedImpl buffer;
  static constexpr uint64_t NumIovecs = 2;
  Buffer::RawSlice iovecs[NumIovecs];

  
  
  
  
  
  
  uint64_t num_reserved = buffer.reserve(8192, iovecs, NumIovecs);
  EXPECT_EQ(1, num_reserved);
  iovecs[0].len_ = 8000;
  buffer.commit(iovecs, 1);
  EXPECT_EQ(8000, buffer.length());

  
  
  num_reserved = buffer.reserve(16384, iovecs, NumIovecs);
  EXPECT_EQ(2, num_reserved);
  const void* first_slice = iovecs[0].mem_;
  iovecs[0].len_ = 1;
  expectSlices({{8000, 4248, 12248}, {0, 12248, 12248}}, buffer);
  buffer.commit(iovecs, 1);
  EXPECT_EQ(8001, buffer.length());
  EXPECT_EQ(first_slice, iovecs[0].mem_);
  
  expectSlices({{8001, 4247, 12248}}, buffer);

  
  num_reserved = buffer.reserve(16384, iovecs, NumIovecs);
  expectSlices({{8001, 4247, 12248}, {0, 12248, 12248}}, buffer);
  EXPECT_EQ(2, num_reserved);
  EXPECT_EQ(static_cast<const uint8_t*>(first_slice) + 1,
            static_cast<const uint8_t*>(iovecs[0].mem_));
}