
#include <iostream>
#include "Network/BtChannel.h"
#include "Network/BtEndpoint.h"

using namespace std;
#include "Common/Defines.h"
using namespace osuCrypto;

#include "OtBinMain.h"
#include "bitPosition.h"

#include <numeric>
#include <string>
#include "Common/Log.h"
//int miraclTestMain();


void usage(const char* argv0)
{
	std::cout << "Error! Please use:" << std::endl;
	std::cout << "\t 1. For unit test: " << argv0 << " -u" << std::endl;
	std::cout << "\t 2. For simulation (5 parties <=> 5 terminals): " << std::endl;;
	std::cout << "\t\t each terminal: " << argv0 << " -n 5 -t 2 -m 12 -p [pIdx]" << std::endl;

}
int main(int argc, char** argv)
{

	//myCuckooTest_stash();
	//Table_Based_Random_Test();
	//OPPRF2_EmptrySet_Test_Main();
	//OPPRFn_EmptrySet_Test_Main();
	//Transpose_Test();
	//OPPRF3_EmptrySet_Test_Main();
	//OPPRFnt_EmptrySet_Test_Main();
	//OPPRFnt_EmptrySet_Test_Main();
	//OPPRFn_Aug_EmptrySet_Test_Impl();
	//OPPRFnt_EmptrySet_Test_Main();
	//OPPRF2_EmptrySet_Test_Main();
	//return 0;

	u64 trials = 1;
	u64 pSetSize = 5, psiSecParam = 40, bitSize = 128;

	u64 nParties, tParties, opt_basedOPPRF, setSize, isAug;

	u64 roundOPPRF;

	std::string filename;

	switch (argc) {
	case 2: //unit test
		if (argv[1][0] == '-' && argv[1][1] == 'u')
			OPPRFnt_EmptrySet_Test_Main();
		break;

	case 7: //2PSI 
		if (argv[1][0] == '-' && argv[1][1] == 'n')
			nParties = atoi(argv[2]);
		else
		{
			usage(argv[0]);
			return 0;
		}

		if (argv[3][0] == '-' && argv[3][1] == 'm')
			setSize = 1 << atoi(argv[4]);
		else
		{
			usage(argv[0]);
			return 0;
		}

		if (argv[5][0] == '-' && argv[5][1] == 'p') {
			u64 pIdx = atoi(argv[6]);
			if (nParties == 2)
				party2(pIdx, setSize);
			else
			{
				usage(argv[0]);
				return 0;
			}
		}
		else
		{
			usage(argv[0]);
			return 0;
		}
		break;
	// case 9: //nPSI or optimized 3PSI
	case 11: //nPSI or optimized 3PSI
		cout << "nPSI or optimized 3PSI: argc=11\n";
		// comment by zengzc 20211231
		// -n：number of parties
		if (argv[1][0] == '-' && argv[1][1] == 'n')
			// comment by zengzc 20211231
			// int atoi(const char *str) 把参数 str 所指向的字符串转换为一个整数（类型为 int 型）
			// nParties：参与方数量
			nParties = atoi(argv[2]); 
		else
		{
			usage(argv[0]);
			return 0;
		}
		// comment by zengzc 20220104
		// -r：optimized 3PSI when r = 1
		if (argv[3][0] == '-' && argv[3][1] == 'r' && nParties == 3)
		{
			roundOPPRF = atoi(argv[4]);
			tParties = 2; // tParties：不诚实方数量
		}
		// comment by zengzc 20220104
		// -t：number of corrupted parties (in semihonest setting)
		else if (argv[3][0] == '-' && argv[3][1] == 't')
			tParties = atoi(argv[4]);
		// comment by zengzc 20220104
		// -a：run in augmented semihonest model. Table-based OPPRF is by default.
		//	0: Table-based; 1: POLY-seperated; 2-POLY-combined; 3-BloomFilter
		else if (argv[3][0] == '-' && argv[3][1] == 'a')
			opt_basedOPPRF = atoi(argv[4]);
		else
		{
			usage(argv[0]);
			return 0;
		}

		// comment by zengzc 20220104
		// -m：set size
		if (argv[5][0] == '-' && argv[5][1] == 'm')
			setSize = 1 << atoi(argv[6]); // 1左移x位，即为2^x
		else
		{
			usage(argv[0]);
			return 0;
		}

		if (argv[9][0] == '-' && argv[9][1] == 'f')
		{
			filename = argv[10];
			cout << "argv[10] filename:"<< filename <<"\n";
		}
		else
		{
			usage(argv[0]);
			return 0;
		}

		// comment by zengzc 20220104
		// -p：party ID
		if (argv[7][0] == '-' && argv[7][1] == 'p') {
			u64 pIdx = atoi(argv[8]);
			if (roundOPPRF == 1 && nParties == 3)
			{
				//cout << nParties  << " " << roundOPPRF << " " << setSize << " " << pIdx << "\n";
				party3(pIdx, setSize, trials);
			}
			else if (argv[3][1] == 't') //zengzc:重点关注这个分支
			{
				cout << "zengzc log: =======================exec tparty=======================\n";
				cout << "pIdx:" << pIdx << " nParties:" << nParties << " tParties:" << tParties << " setSize:" << setSize << " trials:" << trials << " filename:" << filename << "\n";
				tparty(pIdx, nParties, tParties, setSize, trials, filename);
			}
			else if (argv[3][1] == 'a')
			{
				aug_party(pIdx, nParties, setSize, opt_basedOPPRF, trials);
			}
		}
		else
		{
			usage(argv[0]);
			return 0;
		}
		break;
	}

	return 0;
}
