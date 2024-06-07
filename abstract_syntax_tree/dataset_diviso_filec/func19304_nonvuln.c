StringVal EncryptionFunctions::aes_encrypt(FunctionContext* ctx, const StringVal& src,
                                           const StringVal& key, const StringVal& iv,
                                           const StringVal& mode) {
    EncryptionMode encryption_mode = AES_128_ECB;
    if (mode.len != 0 && !mode.is_null) {
        std::string mode_str(reinterpret_cast<char*>(mode.ptr), mode.len);
        if (aes_mode_map.count(mode_str) == 0) {
            return StringVal::null();
        }
        encryption_mode = aes_mode_map.at(mode_str);
    }
    return encrypt(ctx, src, key, iv, encryption_mode);
}