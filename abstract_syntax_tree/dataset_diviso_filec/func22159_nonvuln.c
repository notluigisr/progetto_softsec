AnyP::Uri::absolute() const
{
    if (absolute_.isEmpty()) {
        
        absolute_.reserveCapacity(MAX_URL);

        absolute_.append(getScheme().image());
        absolute_.append("STR",1);
        if (getScheme() != AnyP::PROTO_URN) {
            absolute_.append("STR", 2);
            const bool allowUserInfo = getScheme() == AnyP::PROTO_FTP ||
                                       getScheme() == AnyP::PROTO_UNKNOWN;

            if (allowUserInfo && !userInfo().isEmpty()) {
                static const CharacterSet uiChars = CharacterSet(UserInfoChars())
                                                    .remove('%')
                                                    .rename("STR");
                absolute_.append(Encode(userInfo(), uiChars));
                absolute_.append("STR", 1);
            }
            absolute_.append(authority());
        } else {
            absolute_.append(host());
            absolute_.append("STR", 1);
        }
        absolute_.append(path()); 
    }

    return absolute_;
}