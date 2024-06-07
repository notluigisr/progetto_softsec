TEST(OverflowArithmetic, HeterogeneousArguments) {
    {
        int r;
        ASSERT_FALSE(overflow::mul(1L, 2ULL, &r));
        ASSERT_EQ(r, 2);
    }
    {
        unsigned long long r;
        ASSERT_TRUE(overflow::mul(-1, 2, &r));
    }
}