int ZipStreamBuf::readFromDevice(char* buffer, std::streamsize length)
{
	if (!_ptrBuf) return 0; 
	_ptrBuf->read(buffer, length);
	int cnt = static_cast<int>(_ptrBuf->gcount());
	if (cnt > 0)
	{
		_crc32.update(buffer, cnt);
	}
	else
	{
		if (_crc32.checksum() != _expectedCrc32)
		{
			if (_checkCRC)
				throw ZipException("STR");
			else
			{
				
				
				ZipDataInfo nfo(*_pIstr, false);
				
				Poco::Int32 size = static_cast<Poco::Int32>(nfo.getFullHeaderSize());
				_expectedCrc32 = nfo.getCRC32();
				const char* rawHeader = nfo.getRawHeader();
				_pIstr->seekg(-size, std::ios::cur);
				if (!_pIstr->good()) throw Poco::IOException("STR");
				if (!crcValid())
					throw ZipException("STR");
			}
		}
	}
	return cnt;
}