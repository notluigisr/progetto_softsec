cmsBool  _cmsRegisterTagTypePlugin(cmsContext id, cmsPluginBase* Data)
{
    return RegisterTypesPlugin(id, Data, SupportedTagTypes, DEFAULT_TAG_TYPE_COUNT);
}