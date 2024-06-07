JVM_SocketAvailable(jint descriptor, jint* result)
{
	jint retVal = 0;

	Trc_SC_SocketAvailable_Entry(descriptor, result);

#ifdef WIN32
	
	Assert_SC_unreachable();
#endif
#if defined(J9UNIX) || defined(J9ZOS390)
	if (0 <= descriptor) {
		do {
			retVal = ioctl(descriptor, FIONREAD, result);
		} while ((-1 == retVal) && (EINTR == errno));

		if (0 <= retVal) {
			
			retVal = 1;
		} else {
			
			retVal = 0;
		}
	}
#endif 

	Trc_SC_SocketAvailable_Exit(retVal, *result);

	return retVal;
}