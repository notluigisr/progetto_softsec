output_buffer& HandShakeHeader::get(output_buffer& out) const
{
    return out << *this;
}