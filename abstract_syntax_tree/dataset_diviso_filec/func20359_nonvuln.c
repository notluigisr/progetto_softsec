Header::lineOrder () const
{
    return static_cast <const LineOrderAttribute &>
	((*this)["STR"]).value();
}