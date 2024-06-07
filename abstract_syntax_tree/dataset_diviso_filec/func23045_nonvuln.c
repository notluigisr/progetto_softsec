BitStream::getBits(size_t nbits)
{
    return read_bits(this->p, this->bit_offset,
		     this->bits_available, nbits);
}