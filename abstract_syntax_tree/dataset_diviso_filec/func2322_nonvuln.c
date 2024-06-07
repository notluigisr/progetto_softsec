static int entersafe_write_large_rsa_key(sc_card_t *card,u8 key_id,struct sc_pkcs15_prkey_rsa *rsa)
{
	 int r;

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);

	 {
		  r = entersafe_write_rsa_key_factor(card,key_id,0x22,0x01,rsa->p);
		  SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "STR");
		  r = entersafe_write_rsa_key_factor(card,key_id,0x22,0x02,rsa->q);
		  SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "STR");
		  r = entersafe_write_rsa_key_factor(card,key_id,0x22,0x03,rsa->dmp1);
		  SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "STR");
		  r = entersafe_write_rsa_key_factor(card,key_id,0x22,0x04,rsa->dmq1);
		  SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "STR");
		  r = entersafe_write_rsa_key_factor(card,key_id,0x22,0x05,rsa->iqmp);
		  SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "STR");
	 }

	 {
		  u8 sbuff[SC_MAX_APDU_BUFFER_SIZE];
		  sc_apdu_t apdu;

		  
		  sbuff[0]=0x83;
		  sbuff[1]=0x02;
		  sbuff[2]=key_id;
		  sbuff[3]=0x2A;
		  sbuff[4]=0x89;
		  sbuff[5]=0x40;
		  memcpy(sbuff+6,rsa->modulus.data,0x40);

		  sc_format_apdu(card,&apdu,SC_APDU_CASE_3_SHORT,0x22,0x01,0xB8);
		  apdu.data=sbuff;
		  apdu.lc=apdu.datalen=0x46;

		  r=entersafe_transmit_apdu(card,&apdu,0,0,0,0);
		  SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "STR");
		  SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, sc_check_sw(card, apdu.sw1, apdu.sw2),"STR");

		  
		  sc_format_apdu(card,&apdu,SC_APDU_CASE_3_SHORT,0x46,0x0B,0x00);
		  apdu.data=rsa->modulus.data+0x40;
		  apdu.lc=apdu.datalen=0xC0;

		  r=entersafe_transmit_apdu(card,&apdu,0,0,0,0);
		  SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "STR");
		  SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, sc_check_sw(card, apdu.sw1, apdu.sw2),"STR");

		  
		  r = entersafe_write_rsa_key_factor(card,key_id,0x2A,0x0D,rsa->exponent);
		  SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "STR");
	 }
	SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE,SC_SUCCESS);
}