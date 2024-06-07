unsigned int DNP3_Base::CalcCRC(int len, const u_char* data)
	{
	unsigned int crc = 0x0000;

	for ( int i = 0; i < len; i++ )
		{
		unsigned int index = (crc ^ data[i]) & 0xFF;
		crc = crc_table[index] ^ (crc >> 8);
		}

	return ~crc & 0xFFFF;
	}