int crxParamInit(CrxBandParam **param, uint64_t subbandMdatOffset,
                 uint64_t subbandDataSize, uint32_t subbandWidth,
                 uint32_t subbandHeight, int32_t supportsPartial,
                 uint32_t roundedBitsMask, LibRaw_abstract_datastream *input)
{
  int32_t progrDataSize = supportsPartial ? 0 : sizeof(int32_t) * subbandWidth;
  int32_t paramLength = 2 * subbandWidth + 4;
  uint8_t *paramBuf = (uint8_t *)calloc(
      1, sizeof(CrxBandParam) + sizeof(int32_t) * paramLength + progrDataSize);

  if (!paramBuf)
    return -1;

  *param = (CrxBandParam *)paramBuf;

  paramBuf += sizeof(CrxBandParam);

  (*param)->paramData = (int32_t *)paramBuf;
  (*param)->nonProgrData =
      progrDataSize ? (*param)->paramData + paramLength : 0;
  (*param)->subbandWidth = subbandWidth;
  (*param)->subbandHeight = subbandHeight;
  (*param)->roundedBits = 0;
  (*param)->curLine = 0;
  (*param)->roundedBitsMask = roundedBitsMask;
  (*param)->supportsPartial = supportsPartial;
  (*param)->bitStream.bitData = 0;
  (*param)->bitStream.bitsLeft = 0;
  (*param)->bitStream.mdatSize = subbandDataSize;
  (*param)->bitStream.curPos = 0;
  (*param)->bitStream.curBufSize = 0;
  (*param)->bitStream.curBufOffset = subbandMdatOffset;
  (*param)->bitStream.input = input;

  crxFillBuffer(&(*param)->bitStream);

  return 0;
}