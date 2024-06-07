unsigned short atalk_checksum(struct ddpehdr *ddp, int len)
{
	unsigned long sum = 0;	
	unsigned char *data = (unsigned char *)ddp;

	len  -= 4;		
	data += 4;

	
	while (len--) {
		sum += *data;
		sum <<= 1;
		if (sum & 0x10000) {
			sum++;
			sum &= 0xFFFF;
		}
		data++;
	}
	
	return sum ? htons((unsigned short)sum) : 0xFFFF;
}