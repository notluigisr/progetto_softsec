InsecureRandomDataProvider::random()
{
    if (! this->seeded_random)
    {
	
	
	
        QUtil::srandom(static_cast<unsigned int>(
                           QUtil::get_current_time() ^ 0xcccc));
	this->seeded_random = true;
    }

#  ifdef HAVE_RANDOM
    return ::random();
#  else
    return rand();
#  endif
}