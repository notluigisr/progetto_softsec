QPDFWriter::setR5EncryptionParameters(
    char const* user_password, char const* owner_password,
    bool allow_accessibility, bool allow_extract,
    bool allow_assemble, bool allow_annotate_and_form,
    bool allow_form_filling, bool allow_modify_other,
    qpdf_r3_print_e print,
    bool encrypt_metadata)
{
    std::set<int> clear;
    interpretR3EncryptionParameters(
	clear, user_password, owner_password,
	allow_accessibility, allow_extract,
        allow_assemble, allow_annotate_and_form,
        allow_form_filling, allow_modify_other,
        print, qpdf_r3m_all);
    this->m->encrypt_use_aes = true;
    this->m->encrypt_metadata = encrypt_metadata;
    setEncryptionParameters(user_password, owner_password, 5, 5, 32, clear);
}