print_buffer(Pl_Buffer* bp)
{
    bp->finish();
    Buffer* b = bp->getBuffer();
    unsigned char const* p = b->getBuffer();
    size_t l = b->getSize();
    for (unsigned long i = 0; i < l; ++i)
    {
	printf("STR", static_cast<unsigned int>(p[i]),
	       (i == l - 1) ? "STR");
    }
    printf("STR");
    delete b;
}