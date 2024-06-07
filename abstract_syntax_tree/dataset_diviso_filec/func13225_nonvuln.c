input_buffer& ServerHello::set(input_buffer& in)
{
    return in  >> *this;
}