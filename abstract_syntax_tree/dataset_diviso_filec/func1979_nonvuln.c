DocumentSourceMatch::extractMatchOnFieldsAndRemainder(const std::set<std::string>& fields,
                                                      const StringMap<std::string>& renames) && {
    return std::move(*this).splitSourceByFunc(fields, renames, expression::isOnlyDependentOn);
}