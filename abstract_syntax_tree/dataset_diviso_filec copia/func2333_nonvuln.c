MillerRabinRounds(
		  UINT32           bits           
		  )
{
    if(bits < 511) return 8;    
    if(bits < 1536) return 5;   
    return 4;                   
}