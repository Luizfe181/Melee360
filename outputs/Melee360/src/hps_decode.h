#ifndef MELEE360_HPS_DECODE_H
#define MELEE360_HPS_DECODE_H
#include <vector>
bool Melee360DecodeHPSBlock(const unsigned char* data,unsigned int bytes,unsigned int block,std::vector<short>& pcm,unsigned int& rate,unsigned int& channels,unsigned int& next);
#endif
