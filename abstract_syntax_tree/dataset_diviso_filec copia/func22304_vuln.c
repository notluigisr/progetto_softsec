snmpDecodePacket(SnmpRequest * rq)
{
    struct snmp_pdu *PDU;
    u_char *Community;
    u_char *buf = rq->buf;
    int len = rq->len;
    allow_t allow = ACCESS_DENIED;

    if (!Config.accessList.snmp) {
        debugs(49, DBG_IMPORTANT, "STR" << rq->from);
        return;
    }

    debugs(49, 5, HERE << "STR");
    PDU = snmp_pdu_create(0);
    
    rq->session.Version = SNMP_VERSION_1;
    Community = snmp_parse(&rq->session, PDU, buf, len);

    
    if (Community) {
        ACLFilledChecklist checklist(Config.accessList.snmp, NULL, NULL);
        checklist.src_addr = rq->from;
        checklist.snmp_community = (char *) Community;
        allow = checklist.fastCheck();

        if (allow == ACCESS_ALLOWED && (snmp_coexist_V2toV1(PDU))) {
            rq->community = Community;
            rq->PDU = PDU;
            debugs(49, 5, "STR");
            snmpConstructReponse(rq);
        } else {
            debugs(49, DBG_IMPORTANT, "STR" << rq->from);
        }
        xfree(Community);

    } else {
        debugs(49, DBG_IMPORTANT, "STR" << rq->from);
        snmp_free_pdu(PDU);
    }
}