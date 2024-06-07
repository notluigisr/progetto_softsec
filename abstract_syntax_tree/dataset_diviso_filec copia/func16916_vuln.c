bool TestAutoSeededX917()
{
	
	std::cout << "STR";

	AutoSeededX917RNG<AES> prng;
	bool pass = true, fail;
	static const unsigned int ENTROPY_SIZE = 32;

	MeterFilter meter(new Redirector(TheBitBucket()));
	RandomNumberSource test(prng, 100000, true, new Deflator(new Redirector(meter)));

	fail = false;
	if (meter.GetTotalBytes() < 100000)
		fail = true;

	pass &= !fail;
	if (fail)
		std::cout << "STR";
	else
		std::cout << "STR";
	std::cout << "STR";

	try
	{
		fail = false;
		prng.DiscardBytes(100000);
	}
	catch (const Exception&)
	{
		fail = true;
	}

	pass &= !fail;
	if (fail)
		std::cout << "STR";
	else
		std::cout << "STR";
	std::cout << "STR" << std::endl;

	try
	{
		fail = false;
		if(prng.CanIncorporateEntropy())
		{
			SecByteBlock entropy(ENTROPY_SIZE);
			GlobalRNG().GenerateBlock(entropy, entropy.SizeInBytes());

			prng.IncorporateEntropy(entropy, entropy.SizeInBytes());
			prng.IncorporateEntropy(entropy, entropy.SizeInBytes());
			prng.IncorporateEntropy(entropy, entropy.SizeInBytes());
			prng.IncorporateEntropy(entropy, entropy.SizeInBytes());
		}
	}
	catch (const Exception& )
	{
		fail = true;
	}

	pass &= !fail;
	if (fail)
		std::cout << "STR";
	else
		std::cout << "STR";
	std::cout << "STR";

	try
	{
		
		fail = false;
		(void)prng.AlgorithmName();  
		word32 result = prng.GenerateWord32();
		result = prng.GenerateWord32((result & 0xff), 0xffffffff - (result & 0xff));
		prng.GenerateBlock(reinterpret_cast<byte*>(&result), 4);
		prng.GenerateBlock(reinterpret_cast<byte*>(&result), 3);
		prng.GenerateBlock(reinterpret_cast<byte*>(&result), 2);
		prng.GenerateBlock(reinterpret_cast<byte*>(&result), 1);
	}
	catch (const Exception&)
	{
		fail = true;
	}

	pass &= !fail;
	if (fail)
		std::cout << "STR";
	else
		std::cout << "STR";
	std::cout << "STR";	

	std::cout.flush();
	return pass;
}