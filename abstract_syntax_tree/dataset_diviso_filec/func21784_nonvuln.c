QPDF_String::getUTF8Val() const
{
    if (QUtil::is_utf16(this->val))
    {
        return QUtil::utf16_to_utf8(this->val);
    }
    else
    {
        return QUtil::pdf_doc_to_utf8(this->val);
    }
}