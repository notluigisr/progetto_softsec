Header::hasType() const
{
    return findTypedAttribute <StringAttribute> ("STR") != 0;
}