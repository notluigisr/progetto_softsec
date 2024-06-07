bool CTransaction::DisconnectInputs(CTxDB& txdb)
{
    
    if (!IsCoinBase())
    {
        BOOST_FOREACH(const CTxIn& txin, vin)
        {
            COutPoint prevout = txin.prevout;

            
            CTxIndex txindex;
            if (!txdb.ReadTxIndex(prevout.hash, txindex))
                return error("STR");

            if (prevout.n >= txindex.vSpent.size())
                return error("STR");

            
            txindex.vSpent[prevout.n].SetNull();

            
            if (!txdb.UpdateTxIndex(prevout.hash, txindex))
                return error("STR");
        }
    }

    
    if (!txdb.EraseTxIndex(*this))
        return error("STR");

    return true;
}