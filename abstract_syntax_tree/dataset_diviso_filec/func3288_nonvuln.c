print_p2r (const unsigned char *msg, size_t msglen)
{
  switch (msglen? msg[0]:0)
    {
    case PC_to_RDR_IccPowerOn:
      print_p2r_iccpoweron (msg, msglen);
      break;
    case PC_to_RDR_IccPowerOff:
      print_p2r_iccpoweroff (msg, msglen);
      break;
    case PC_to_RDR_GetSlotStatus:
      print_p2r_getslotstatus (msg, msglen);
      break;
    case PC_to_RDR_XfrBlock:
      print_p2r_xfrblock (msg, msglen);
      break;
    case PC_to_RDR_GetParameters:
      print_p2r_getparameters (msg, msglen);
      break;
    case PC_to_RDR_ResetParameters:
      print_p2r_resetparameters (msg, msglen);
      break;
    case PC_to_RDR_SetParameters:
      print_p2r_setparameters (msg, msglen);
      break;
    case PC_to_RDR_Escape:
      print_p2r_escape (msg, msglen);
      break;
    case PC_to_RDR_IccClock:
      print_p2r_iccclock (msg, msglen);
      break;
    case PC_to_RDR_T0APDU:
      print_p2r_to0apdu (msg, msglen);
      break;
    case PC_to_RDR_Secure:
      print_p2r_secure (msg, msglen);
      break;
    case PC_to_RDR_Mechanical:
      print_p2r_mechanical (msg, msglen);
      break;
    case PC_to_RDR_Abort:
      print_p2r_abort (msg, msglen);
      break;
    case PC_to_RDR_SetDataRate:
      print_p2r_setdatarate (msg, msglen);
      break;
    default:
      print_p2r_unknown (msg, msglen);
      break;
    }
}