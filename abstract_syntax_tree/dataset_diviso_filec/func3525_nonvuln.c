RC4::process(unsigned char *in_data, size_t len, unsigned char* out_data)
{
    if (out_data == 0)
    {
	
	out_data = in_data;
    }

    for (size_t i = 0; i < len; ++i)
    {
	key.x = static_cast<unsigned char>((key.x + 1) % 256);
	key.y = static_cast<unsigned char>((key.state[key.x] + key.y) % 256);
	swap_byte(key.state[key.x], key.state[key.y]);
	int xor_index = (key.state[key.x] + key.state[key.y]) % 256;
	out_data[i] = in_data[i] ^ key.state[xor_index];
    }
}