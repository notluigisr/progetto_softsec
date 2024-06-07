duint32 dwgCompressor::long20CompressionOffset(){

    duint32 cont = 0x0F;
    duint8 ll = bufC[pos++];
    while (ll == 0x00){

        ll = bufC[pos++];
    }
    cont += ll;
    return cont;
}