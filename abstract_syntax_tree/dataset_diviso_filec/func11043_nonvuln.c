Header::hasPreviewImage () const
{
    return findTypedAttribute <PreviewImageAttribute> ("STR") != 0;
}