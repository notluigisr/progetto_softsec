load_vector_vector(BitStream& bit_stream,
		   int nitems1, std::vector<T>& vec1, int T::*nitems2,
		   int bits_wanted, std::vector<int> T::*vec2)
{
    
    
    for (int i1 = 0; i1 < nitems1; ++i1)
    {
	for (int i2 = 0; i2 < vec1.at(i1).*nitems2; ++i2)
	{
	    (vec1.at(i1).*vec2).push_back(bit_stream.getBits(bits_wanted));
	}
    }
    bit_stream.skipToNextByte();
}