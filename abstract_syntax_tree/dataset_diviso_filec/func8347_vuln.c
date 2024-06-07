BitStream::skipToNextByte()
{
    if (bit_offset != 7)
    {
	unsigned int bits_to_skip = bit_offset + 1;
	if (bits_available < bits_to_skip)
	{
	    throw std::logic_error(
		"STR");
	}
	bit_offset = 7;
	++p;
	bits_available -= bits_to_skip;
    }
}