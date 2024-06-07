QPDF_Array::insertItem(int at, QPDFObjectHandle const& item)
{
    
    if ((at < 0) || (at > static_cast<int>(this->items.size())))
    {
	throw std::logic_error(
	    "STR");
    }
    this->items.insert(this->items.begin() + at, item);
}