static int protocol_client_auth(VncState *vs, uint8_t *data, size_t len)
{
    
    if (data[0] != vs->auth) { 
       trace_vnc_auth_reject(vs, vs->auth, (int)data[0]);
       authentication_failed(vs);
    } else { 
       trace_vnc_auth_start(vs, vs->auth);
       switch (vs->auth) {
       case VNC_AUTH_NONE:
           if (vs->minor >= 8) {
               vnc_write_u32(vs, 0); 
               vnc_flush(vs);
           }
           trace_vnc_auth_pass(vs, vs->auth);
           start_client_init(vs);
           break;

       case VNC_AUTH_VNC:
           start_auth_vnc(vs);
           break;

       case VNC_AUTH_VENCRYPT:
           start_auth_vencrypt(vs);
           break;

#ifdef CONFIG_VNC_SASL
       case VNC_AUTH_SASL:
           start_auth_sasl(vs);
           break;
#endif 

       default: 
           trace_vnc_auth_fail(vs, vs->auth, "STR");
           authentication_failed(vs);
       }
    }
    return 0;
}