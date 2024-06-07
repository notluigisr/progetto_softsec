SecureElementStatus_t SecureElementSetKey( KeyIdentifier_t keyID, uint8_t* key )
{
    if( key == NULL )
    {
        return SECURE_ELEMENT_ERROR_NPE;
    }

    SecureElementStatus_t status = SECURE_ELEMENT_ERROR;

    if( ( keyID == MC_KEY_0 ) || ( keyID == MC_KEY_1 ) || ( keyID == MC_KEY_2 ) || ( keyID == MC_KEY_3 ) )
    {  

        lr1110_crypto_derive_and_store_key( &LR1110, ( lr1110_crypto_status_t* ) &status,
                                            convert_key_id_from_se_to_lr1110( MC_KE_KEY ),
                                            convert_key_id_from_se_to_lr1110( keyID ), key );

        if( status == SECURE_ELEMENT_SUCCESS )
        {
            lr1110_crypto_store_to_flash( &LR1110, ( lr1110_crypto_status_t* ) &status );
        }
        return status;
    }
    else
    {
        lr1110_crypto_set_key( &LR1110, ( lr1110_crypto_status_t* ) &status, convert_key_id_from_se_to_lr1110( keyID ),
                               key );
        if( status == SECURE_ELEMENT_SUCCESS )
        {
            lr1110_crypto_store_to_flash( &LR1110, ( lr1110_crypto_status_t* ) &status );
        }
        return status;
    }
}