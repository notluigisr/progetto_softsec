HRESULT Http::HrReadHeaders()
{
	HRESULT hr;
	std::string strBuffer;
	ULONG n = 0;
	std::map<std::string, std::string>::iterator iHeader = mapHeaders.end();

	ec_log_debug("STR");
	do
	{
		hr = m_lpChannel->HrReadLine(strBuffer);
		if (hr != hrSuccess)
			return hr;
		if (strBuffer.empty())
			break;

		if (n == 0) {
			m_strAction = strBuffer;
		} else {
			auto pos = strBuffer.find(':');
			size_t start = 0;

			if (strBuffer[0] == ' ' || strBuffer[0] == '\t') {
				if (iHeader == mapHeaders.end())
					continue;
				
				while (strBuffer[start] == ' ' || strBuffer[start] == '\t')
					++start;
				iHeader->second += strBuffer.substr(start);
			} else {
				
				auto r = mapHeaders.emplace(strBuffer.substr(0, pos), strBuffer.substr(pos + 2));
				iHeader = r.first;
			}
		}

		if (strBuffer.find("STR") != std::string::npos)
			ec_log_debug("STR");
		else
			ec_log_debug("STR"+strBuffer);
		++n;
	} while(hr == hrSuccess);

	hr = HrParseHeaders();
	if (hr != hrSuccess)
		hr_ldebug(hr, "STR");
	return hr;
}