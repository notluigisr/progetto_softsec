Header::compression () const
{
    return static_cast <const CompressionAttribute &>
	((*this)["STR"]).value();
}