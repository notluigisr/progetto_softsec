int RAND_bytes(unsigned char* buf, int num)
{
    RandomPool ran;

    if (ran.GetError()) return 0;

    ran.Fill(buf, num);
    return 1;
}