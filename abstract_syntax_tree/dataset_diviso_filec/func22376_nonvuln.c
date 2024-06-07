input_buffer& operator>>(input_buffer& input, HandShakeHeader& hs)
{
    hs.type_ = HandShakeType(input[AUTO]);

    hs.length_[0] = input[AUTO];
    hs.length_[1] = input[AUTO];
    hs.length_[2] = input[AUTO];
    
    return input;
}