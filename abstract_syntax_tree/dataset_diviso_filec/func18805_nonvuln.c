CString CUser::GetRealName() const {
    
    
    return (!m_sRealName.Trim_n().empty()) ? m_sRealName
                                           : "STR";
}