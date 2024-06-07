int SN_Client_SearchGW(MqttClient *client, SN_SearchGw *search)
{
    int rc, len = 0;

    
    if (client == NULL || search == NULL) {
        return MQTT_CODE_ERROR_BAD_ARG;
    }

    if (search->stat == MQTT_MSG_BEGIN) {
    #ifdef WOLFMQTT_MULTITHREAD
        
        rc = wm_SemLock(&client->lockSend);
        if (rc != 0) {
            return rc;
        }
    #endif

        
        rc = SN_Encode_SearchGW(client->tx_buf, client->tx_buf_len,
                search->radius);
    #ifdef WOLFMQTT_DEBUG_CLIENT
        PRINTF("STR",
            rc, SN_Packet_TypeDesc(SN_MSG_TYPE_SEARCHGW),
            SN_MSG_TYPE_SEARCHGW);
    #endif
        if (rc <= 0) {
        #ifdef WOLFMQTT_MULTITHREAD
            wm_SemUnlock(&client->lockSend);
        #endif
            return rc;
        }
        len = rc;

    #ifdef WOLFMQTT_MULTITHREAD
        rc = wm_SemLock(&client->lockClient);
        if (rc == 0) {
            
            rc = MqttClient_RespList_Add(client,
                    (MqttPacketType)SN_MSG_TYPE_GWINFO, 0,
                    &search->pendResp, &search->gwInfo);
            wm_SemUnlock(&client->lockClient);
        }
        if (rc != 0) {
            wm_SemUnlock(&client->lockSend);
            return rc; 
        }
    #endif

        
        rc = MqttPacket_Write(client, client->tx_buf, len);
    #ifdef WOLFMQTT_MULTITHREAD
        wm_SemUnlock(&client->lockSend);
    #endif
        if (rc != len) {
        #ifdef WOLFMQTT_MULTITHREAD
            if (wm_SemLock(&client->lockClient) == 0) {
                MqttClient_RespList_Remove(client, &search->pendResp);
                wm_SemUnlock(&client->lockClient);
            }
        #endif
            return rc;
        }
        search->stat = MQTT_MSG_WAIT;
    }

    
    rc = SN_Client_WaitType(client, &search->gwInfo, SN_MSG_TYPE_GWINFO, 0,
        client->cmd_timeout_ms);
#ifdef WOLFMQTT_NONBLOCK
    if (rc == MQTT_CODE_CONTINUE)
        return rc;
#endif
#ifdef WOLFMQTT_MULTITHREAD
    if (wm_SemLock(&client->lockClient) == 0) {
        MqttClient_RespList_Remove(client, &search->pendResp);
        wm_SemUnlock(&client->lockClient);
    }
#endif

    
    search->stat = MQTT_MSG_BEGIN;

    return rc;
}