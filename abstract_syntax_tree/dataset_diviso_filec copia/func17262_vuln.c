compute_U_value_R3(std::string const& user_password,
		   QPDF::EncryptionData const& data)
{
    

    std::string k1 = QPDF::compute_encryption_key(user_password, data);
    MD5 md5;
    md5.encodeDataIncrementally(
	pad_or_truncate_password_V4("").c_str(), key_bytes);
    md5.encodeDataIncrementally(data.getId1().c_str(),
                                data.getId1().length());
    MD5::Digest digest;
    md5.digest(digest);
    pad_short_parameter(k1, data.getLengthBytes());
    iterate_rc4(digest, sizeof(MD5::Digest),
		QUtil::unsigned_char_pointer(k1),
                data.getLengthBytes(), 20, false);
    char result[key_bytes];
    memcpy(result, digest, sizeof(MD5::Digest));
    
    
    for (unsigned int i = sizeof(MD5::Digest); i < key_bytes; ++i)
    {
	result[i] = static_cast<char>((i * i) % 0xff);
    }
    return std::string(result, key_bytes);
}