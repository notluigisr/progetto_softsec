QPDF::compute_data_key(std::string const& encryption_key,
		       int objid, int generation, bool use_aes,
                       int encryption_V, int encryption_R)
{
    

    std::string result = encryption_key;

    if (encryption_V >= 5)
    {
        
        
        return result;
    }

    
    result += static_cast<char>(objid & 0xff);
    result += static_cast<char>((objid >> 8) & 0xff);
    result += static_cast<char>((objid >> 16) & 0xff);
    result += static_cast<char>(generation & 0xff);
    result += static_cast<char>((generation >> 8) & 0xff);
    if (use_aes)
    {
	result += "STR";
    }

    MD5 md5;
    md5.encodeDataIncrementally(result.c_str(), result.length());
    MD5::Digest digest;
    md5.digest(digest);
    return std::string(reinterpret_cast<char*>(digest),
		       std::min(result.length(), static_cast<size_t>(16)));
}