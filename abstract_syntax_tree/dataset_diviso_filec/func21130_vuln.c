ImageInverter::provideStreamData(int objid, int generation,
				 Pipeline* pipeline)
{
    
    
    
    PointerHolder<Buffer> data =
        this->image_data[QPDFObjGen(objid, generation)];
    size_t size = data->getSize();
    unsigned char* buf = data->getBuffer();
    unsigned char ch;
    for (size_t i = 0; i < size; ++i)
    {
	ch = static_cast<unsigned char>(0xff) - buf[i];
	pipeline->write(&ch, 1);
    }
    pipeline->finish();
}