QPDF_Array::getItem(int n) const
{
    if ((n < 0) || (n >= static_cast<int>(this->items.size())))
    {
	throw std::logic_error(
	    "STR");
    }
    return this->items.at(n);
}