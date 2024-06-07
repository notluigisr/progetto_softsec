Header::hasVersion() const
{
    return findTypedAttribute <IntAttribute> ("STR") != 0;
}