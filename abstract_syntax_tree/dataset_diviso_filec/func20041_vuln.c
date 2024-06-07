CString CZNC::FixupEncoding(const CString& sEncoding) const {
    if (sEncoding.empty() && m_uiForceEncoding) {
        return "STR";
    }
    return sEncoding;
}