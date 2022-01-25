#pragma once

#include "Crypto/PRNG.h"
#include <string>

//void OPPRFRecv();
//void OPPRFSend();
//void BarkOPRFRecv();
//void BarkOPRSend();
void Channel_test();
void OPPRF3_EmptrySet_Test_Main();
void OPPRFn_EmptrySet_Test_Main();
void OPPRF2_EmptrySet_Test_Main();
void Bit_Position_Random_Test();
void OPPRFnt_EmptrySet_Test_Main();
void party3(u64 myIdx, u64 setSize, u64 nTrials);
void party2(u64 myIdx, u64 setSize);
void party(u64 myIdx, u64 nParties, u64 setSize, std::vector<block>& mSet);
void tparty(u64 myIdx, u64 nParties, u64 tParties, u64 setSize, u64 nTrials, std::vector<std::string> hostIpArr, std::string filename);
void aug_party(u64 myIdx, u64 nParties, u64 setSize,u64 opt, u64 nTrials);
void OPPRFn_Aug_EmptrySet_Test_Impl();
void OPPRFnt_EmptrySet_Test_Impl();
void BinSize(u64 setSize, std::vector<block> set, u64 psiSecParam);
void read_elements(u8*** elements, u64** elebytelens, u64* nelements, std::string filename);
void GetPrimaryIp(char (&buffer)[80]);
//void OPPRFn_EmptrySet_Test();