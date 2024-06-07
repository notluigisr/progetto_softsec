void MD5::update(unsigned char *input,
		 size_t inputLen)
{
    unsigned int i, index, partLen;

    
    index = static_cast<unsigned int>((count[0] >> 3) & 0x3f);

    
    if ((count[0] += (static_cast<UINT4>(inputLen) << 3)) <
        (static_cast<UINT4>(inputLen) << 3))
	count[1]++;
    count[1] += (static_cast<UINT4>(inputLen) >> 29);

    partLen = 64 - index;

    

    if (inputLen >= partLen) {
	memcpy(&buffer[index], input, partLen);
	transform(state, buffer);

	for (i = partLen; i + 63 < inputLen; i += 64)
	    transform(state, &input[i]);

	index = 0;
    }
    else
	i = 0;

    
    memcpy(&buffer[index], &input[i], inputLen-i);
}