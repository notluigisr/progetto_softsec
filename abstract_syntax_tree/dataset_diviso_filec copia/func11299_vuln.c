check_owner_password_V4(std::string& user_password,
                        std::string const& owner_password,
                        QPDF::EncryptionData const& data)
{
    

    unsigned char key[OU_key_bytes_V4];
    compute_O_rc4_key(user_password, owner_password, data, key);
    unsigned char O_data[key_bytes];
    memcpy(O_data, QUtil::unsigned_char_pointer(data.getO()), key_bytes);
    std::string k1(reinterpret_cast<char*>(key), OU_key_bytes_V4);
    pad_short_parameter(k1, data.getLengthBytes());
    iterate_rc4(O_data, key_bytes, QUtil::unsigned_char_pointer(k1),
                data.getLengthBytes(),
                (data.getR() >= 3) ? 20 : 1, true);
    std::string new_user_password =
        std::string(reinterpret_cast<char*>(O_data), key_bytes);
    bool result = false;
    if (check_user_password(new_user_password, data))
    {
        result = true;
        user_password = new_user_password;
    }
    return result;
}