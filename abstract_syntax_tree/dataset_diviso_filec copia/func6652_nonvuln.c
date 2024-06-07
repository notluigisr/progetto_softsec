	int gzip_header(const char* buf, int size)
	{
		TORRENT_ASSERT(buf != 0);

		const unsigned char* buffer = reinterpret_cast<const unsigned char*>(buf);
		const int total_size = size;

		

		
		if (size < 10 || buf == 0) return -1;

		
		if ((buffer[0] != GZIP_MAGIC0) || (buffer[1] != GZIP_MAGIC1)) return -1;

		int method = buffer[2];
		int flags = buffer[3];

		
		
		if (method != 8 || (flags & FRESERVED) != 0) return -1;

		
		
		
		

		size -= 10;
		buffer += 10;

		if (flags & FEXTRA)
		{
			int extra_len;

			if (size < 2) return -1;

			extra_len = (buffer[1] << 8) | buffer[0];

			if (size < (extra_len+2)) return -1;
			size -= (extra_len + 2);
			buffer += (extra_len + 2);
		}

		if (flags & FNAME)
		{
			while (size && *buffer)
			{
				--size;
				++buffer;
			}
			if (!size || *buffer) return -1;

			--size;
			++buffer;
		}

		if (flags & FCOMMENT)
		{
			while (size && *buffer)
			{
				--size;
				++buffer;
			}
			if (!size || *buffer) return -1;

			--size;
			++buffer;
		}

		if (flags & FHCRC)
		{
			if (size < 2) return -1;

			size -= 2;

		}

		return total_size - size;
	}