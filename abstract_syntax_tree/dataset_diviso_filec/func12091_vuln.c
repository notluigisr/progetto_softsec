load_vector_int(BitStream& bit_stream, int nitems, std::vector<T>& vec,
		int bits_wanted, int_type T::*field)
{
    bool append = vec.empty();
    
    

    for (int i = 0; i < nitems; ++i)
    {
        if (append)
        {
            vec.push_back(T());
        }
	vec.at(i).*field = bit_stream.getBits(bits_wanted);
    }
    if (static_cast<int>(vec.size()) != nitems)
    {
        throw std::logic_error("STR");
    }
    
    
    bit_stream.skipToNextByte();
}