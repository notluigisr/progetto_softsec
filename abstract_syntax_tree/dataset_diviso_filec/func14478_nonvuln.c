bool CModules::ValidateModuleName(const CString& sModule, CString& sRetMsg) {
    for (unsigned int a = 0; a < sModule.length(); a++) {
        if (((sModule[a] < '0') || (sModule[a] > '9')) &&
            ((sModule[a] < 'a') || (sModule[a] > 'z')) &&
            ((sModule[a] < 'A') || (sModule[a] > 'Z')) && (sModule[a] != '_')) {
            sRetMsg =
                t_f("STR"
                    "STR")(sModule);
            return false;
        }
    }

    return true;
}