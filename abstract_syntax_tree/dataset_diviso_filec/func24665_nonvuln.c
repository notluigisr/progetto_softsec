bool CModules::OnRawMode(const CNick& OpNick, CChan& Channel,
                         const CString& sModes, const CString& sArgs) {
    MODUNLOADCHK(OnRawMode(OpNick, Channel, sModes, sArgs));
    return false;
}