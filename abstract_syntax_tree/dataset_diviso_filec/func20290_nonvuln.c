static int gasp_source_id(__be32 *p)
{
	return be32_to_cpu(p[0]) >> 16;
}