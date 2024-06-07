QPDFXRefEntry::getObjStreamNumber() const
{
    if (this->type != 2)
    {
	throw std::logic_error(
	    "STR");
    }
    return this->field1;
}