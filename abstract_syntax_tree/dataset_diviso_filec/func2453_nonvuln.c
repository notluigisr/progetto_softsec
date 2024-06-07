static __u8 map_line_status(__u8 ti_lsr)
{
	__u8 lsr = 0;


	if (ti_lsr & flagUmp) \
		lsr |= flagUart;

	MAP_FLAG(UMP_UART_LSR_OV_MASK, LSR_OVER_ERR)	
	MAP_FLAG(UMP_UART_LSR_PE_MASK, LSR_PAR_ERR)	
	MAP_FLAG(UMP_UART_LSR_FE_MASK, LSR_FRM_ERR)	
	MAP_FLAG(UMP_UART_LSR_BR_MASK, LSR_BREAK)	
	MAP_FLAG(UMP_UART_LSR_RX_MASK, LSR_RX_AVAIL)	
	MAP_FLAG(UMP_UART_LSR_TX_MASK, LSR_TX_EMPTY)	

#undef MAP_FLAG

	return lsr;
}