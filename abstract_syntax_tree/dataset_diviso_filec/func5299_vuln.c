bool_t auth_gssapi_unwrap_data(
     OM_uint32 *major,
     OM_uint32 *minor,
     gss_ctx_id_t context,
     uint32_t seq_num,
     XDR *in_xdrs,
     bool_t (*xdr_func)(),
     caddr_t xdr_ptr)
{
     gss_buffer_desc in_buf, out_buf;
     XDR temp_xdrs;
     uint32_t verf_seq_num;
     int conf, qop;
     unsigned int length;

     PRINTF(("STR"));

     *major = GSS_S_COMPLETE;
     *minor = 0; 

     in_buf.value = NULL;
     out_buf.value = NULL;
     if (! xdr_bytes(in_xdrs, (char **) &in_buf.value,
		     &length, (unsigned int) -1)) {
	 PRINTF(("STR"));
	 temp_xdrs.x_op = XDR_FREE;
	 (void)xdr_bytes(&temp_xdrs, (char **) &in_buf.value, &length,
			 (unsigned int) -1);
	 return FALSE;
     }
     in_buf.length = length;

     *major = gss_unseal(minor, context, &in_buf, &out_buf, &conf,
			 &qop);
     free(in_buf.value);
     if (*major != GSS_S_COMPLETE)
	  return FALSE;

     PRINTF(("STR",
	     (unsigned long long)out_buf.length,
	     (unsigned long long)in_buf.length));

     xdrmem_create(&temp_xdrs, out_buf.value, out_buf.length, XDR_DECODE);

     
     if (! xdr_u_int32(&temp_xdrs, &verf_seq_num)) {
	  PRINTF(("STR"));
	  gss_release_buffer(minor, &out_buf);
	  XDR_DESTROY(&temp_xdrs);
	  return FALSE;
     }
     if (verf_seq_num != seq_num) {
	  PRINTF(("STR",
		  seq_num, verf_seq_num));
	  gss_release_buffer(minor, &out_buf);
	  XDR_DESTROY(&temp_xdrs);
	  return FALSE;
     }
     PRINTF(("STR", verf_seq_num));

     
     if (! (*xdr_func)(&temp_xdrs, xdr_ptr)) {
	  PRINTF(("STR"));
	  gss_release_buffer(minor, &out_buf);
	  xdr_free(xdr_func, xdr_ptr);
	  XDR_DESTROY(&temp_xdrs);
	  return FALSE;
     }

     PRINTF(("STR"));

     gss_release_buffer(minor, &out_buf);
     XDR_DESTROY(&temp_xdrs);
     return TRUE;
}