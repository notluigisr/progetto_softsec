void do_sm4_test(const std::string& source, const std::string& key) {
    int cipher_len = source.length() + 16;
    std::unique_ptr<unsigned char[]> dest(new unsigned char[cipher_len]);
    int ret_code = EncryptionUtil::encrypt(SM4_128_ECB, (unsigned char*)source.c_str(),
                                           source.length(), (unsigned char*)key.c_str(),
                                           key.length(), nullptr, true, dest.get());
    ASSERT_TRUE(ret_code > 0);
    int encrypted_length = ret_code;
    std::unique_ptr<char[]> decrypted(new char[cipher_len]);
    ret_code = EncryptionUtil::decrypt(SM4_128_ECB, dest.get(), encrypted_length,
                                       (unsigned char*)key.c_str(), key.length(), nullptr, true,
                                       (unsigned char*)decrypted.get());
    ASSERT_TRUE(ret_code > 0);
    std::string decrypted_content(decrypted.get(), ret_code);
    ASSERT_EQ(source, decrypted_content);
}