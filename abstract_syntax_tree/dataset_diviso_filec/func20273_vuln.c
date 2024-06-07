bool DNP3_Base::ParseAppLayer(Endpoint* endp)
	{
	bool orig = (endp == &orig_state);
	binpac::DNP3::DNP3_Flow* flow = orig ? interp->upflow() : interp->downflow();

	u_char* data = endp->buffer + PSEUDO_TRANSPORT_INDEX; 
	int len = endp->pkt_length - 5;

	
	
	
	
	

	int is_first = (endp->tpflags & 0x40) >> 6; 
	int is_last = (endp->tpflags & 0x80) >> 7; 

	int transport = PSEUDO_TRANSPORT_LEN;

	int i = 0;
	while ( len > 0 )
		{
		int n = min(len, 16);

		
		if ( ! CheckCRC(n, data, data + n, "STR") )
			return false;

		
		assert(data + n < endp->buffer + endp->buffer_len);
		flow->flow_buffer()->BufferData(data + transport, data + n);
		transport = 0;

		data += n + 2;
		len -= n;
		}

	if ( is_first )
		endp->encountered_first_chunk = true;

	if ( ! is_first && ! endp->encountered_first_chunk )
		{
		
		analyzer->Weird("STR");
		return false;
		}

	if ( is_last )
		{
		flow->flow_buffer()->FinishBuffer();
		flow->FlowEOF();
		ClearEndpointState(orig);
		}

	return true;
	}