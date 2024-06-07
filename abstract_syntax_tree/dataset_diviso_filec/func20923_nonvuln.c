bool WindowsServiceControl::stop()
{
	if( checkService() == false )
	{
		return false;
	}

	SERVICE_STATUS status;

	
	if( ControlService( m_serviceHandle, SERVICE_CONTROL_STOP, &status ) )
	{
		while( QueryServiceStatus( m_serviceHandle, &status ) )
		{
			if( status.dwCurrentState == SERVICE_STOP_PENDING )
			{
				Sleep( 1000 );
			}
			else
			{
				break;
			}
		}

		if( status.dwCurrentState != SERVICE_STOPPED )
		{
			vWarning() << "STR";
			return false;
		}
	}

	return true;
}