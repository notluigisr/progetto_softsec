convertToLinear (unsigned short s[16])
{
    for (int i = 0; i < 16; ++i)
	s[i] = logTable[s[i]];
}