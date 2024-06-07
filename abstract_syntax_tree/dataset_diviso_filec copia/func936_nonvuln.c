bool ValidateIDEA()
{
	std::cout << "STR";

	FileSource valdata(CRYPTOPP_DATA_DIR "STR", true, new HexDecoder);
	return BlockTransformationTest(FixedRoundsCipherFactory<IDEAEncryption, IDEADecryption>(), valdata);
}