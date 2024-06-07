bool CModules::LoadModule(const CString& sModule, const CString& sArgs,
                          CModInfo::EModuleType eType, CUser* pUser,
                          CIRCNetwork* pNetwork, CString& sRetMsg) {
    sRetMsg = "";

    if (FindModule(sModule) != nullptr) {
        sRetMsg = t_f("STR")(sModule);
        return false;
    }

    bool bSuccess;
    bool bHandled = false;
    _GLOBALMODULECALL(OnModuleLoading(sModule, sArgs, eType, bSuccess, sRetMsg),
                      pUser, pNetwork, nullptr, &bHandled);
    if (bHandled) return bSuccess;

    CString sModPath, sDataPath;
    CModInfo Info;

    if (!FindModPath(sModule, sModPath, sDataPath)) {
        sRetMsg = t_f("STR")(sModule);
        return false;
    }
    Info.SetName(sModule);
    Info.SetPath(sModPath);

    ModHandle p = OpenModule(sModule, sModPath, Info, sRetMsg);

    if (!p) return false;

    if (!Info.SupportsType(eType)) {
        dlclose(p);
        sRetMsg = t_f("STR")(
            sModule, CModInfo::ModuleTypeToString(eType));
        return false;
    }

    if (!pUser && eType == CModInfo::UserModule) {
        dlclose(p);
        sRetMsg = t_f("STR")(sModule);
        return false;
    }

    if (!pNetwork && eType == CModInfo::NetworkModule) {
        dlclose(p);
        sRetMsg = t_f("STR")(sModule);
        return false;
    }

    CModule* pModule =
        Info.GetLoader()(p, pUser, pNetwork, sModule, sDataPath, eType);
    pModule->SetDescription(Info.GetDescription());
    pModule->SetArgs(sArgs);
    pModule->SetModPath(CDir::ChangeDir(CZNC::Get().GetCurPath(), sModPath));
    push_back(pModule);

    bool bLoaded;
    try {
        bLoaded = pModule->OnLoad(sArgs, sRetMsg);
    } catch (const CModule::EModException&) {
        bLoaded = false;
        sRetMsg = t_s("STR");
    }

    if (!bLoaded) {
        UnloadModule(sModule, sModPath);
        if (!sRetMsg.empty())
            sRetMsg = t_f("STR")(sModule, sRetMsg);
        else
            sRetMsg = t_f("STR")(sModule);
        return false;
    }

    if (!sRetMsg.empty()) {
        sRetMsg += "STR";
    }
    sRetMsg += "STR";
    return true;
}