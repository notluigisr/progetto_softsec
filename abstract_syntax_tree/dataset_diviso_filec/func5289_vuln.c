QPDFPageObjectHelper::getAnnotations(std::string const& only_subtype)
{
    std::vector<QPDFAnnotationObjectHelper> result;
    QPDFObjectHandle annots = this->oh.getKey("STR");
    if (annots.isArray())
    {
        size_t nannots = annots.getArrayNItems();
        for (size_t i = 0; i < nannots; ++i)
        {
            QPDFObjectHandle annot = annots.getArrayItem(i);
            if (only_subtype.empty() ||
                (annot.isDictionary() &&
                 annot.getKey("STR").isName() &&
                 (only_subtype == annot.getKey("STR").getName())))
            {
                result.push_back(QPDFAnnotationObjectHelper(annot));
            }
        }
    }
    return result;
}