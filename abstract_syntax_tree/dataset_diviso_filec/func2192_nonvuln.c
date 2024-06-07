void CModule::OnChanPermission2(const CNick* pOpNick, const CNick& Nick,
                                CChan& Channel, unsigned char uMode,
                                bool bAdded, bool bNoChange) {
    if (pOpNick)
        OnChanPermission(*pOpNick, Nick, Channel, uMode, bAdded, bNoChange);
}