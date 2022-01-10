#include "OT_Tests.h"

#include "TwoChooseOne/OTExtInterface.h"

#include "Tools/Tools.h"
#include "Tools/LinearCode.h"
#include "Network/BtChannel.h"
#include "Network/BtEndpoint.h"
#include "Common/Log.h"

#include "TwoChooseOne/IknpOtExtReceiver.h"
#include "TwoChooseOne/IknpOtExtSender.h"

#include "TwoChooseOne/KosOtExtReceiver.h"
#include "TwoChooseOne/KosOtExtSender.h"

#include "TwoChooseOne/LzKosOtExtReceiver.h"
#include "TwoChooseOne/LzKosOtExtSender.h"

#include "NChooseOne/KkrtNcoOtReceiver.h"
#include "NChooseOne/KkrtNcoOtSender.h"

#include "Common.h"
#include <thread>
#include <vector>


#ifdef GetMessage
#undef GetMessage
#endif

#pragma warning(disable: 4800)

using namespace osuCrypto;


void OT_100Receive_Test(BitVector& choiceBits, ArrayView<block> recv, ArrayView<std::array<block, 2>>  sender)
{

    for (int i = 0; i < choiceBits.size(); ++i)
    {

        u8 choice = choiceBits[i];
        const block & revcBlock = recv[i];
        //(i, choice, revcBlock);
        const block& senderBlock = sender[i][choice];

        //if (i==0 || i==128 || i==256 || i==384 ||i==512) {
        //    std::cout << "[" << i << ",0]--" << sender[i][0] << std::endl;
        //    std::cout << "[" << i << ",1]--" << sender[i][1] << std::endl;
        //    std::cout << (int)choice << "-- " << recv[i] << std::endl;
        //}
        if (neq(revcBlock, senderBlock))
            throw UnitTestFail();

        if (eq(revcBlock, sender[i][1 ^ choice]))
            throw UnitTestFail();
    }

}



void BitVector_Indexing_Test_Impl()
{
    BitVector bb(128);
    std::vector<bool>gold(128);


    for (u64 i : std::vector<u64>{ { 2,33,34,26,85,33,99,12,126 } })
    {
        bb[i] = gold[i] = true;
    }


    for (auto i = 0; i < 128; ++i)
    {
        if ((bool)bb[i] != gold[i])
            throw std::runtime_error("");

        if ((bool)bb[i] != gold[i])
            throw UnitTestFail();
    }
}

void BitVector_Parity_Test_Impl()
{
    PRNG prng(ZeroBlock);
    for (u64 i = 0; i < 1000; ++i)
    {
        u8 size = prng.get<u8>();
        u8 parity = 0;

        BitVector bv(size);

        bv.randomize(prng);

        for (u64 j = 0; j < size; ++j)
        {
            parity ^= bv[j];
        }

        if (parity != bv.parity())
            throw UnitTestFail();
    }

}

void BitVector_Append_Test_Impl()
{

    BitVector bv0(3);
    BitVector bv1(6);
    BitVector bv2(9);
    BitVector bv4;


    bv0[0] = 1; bv2[0] = 1;
    bv0[2] = 1; bv2[2] = 1;
    bv1[2] = 1; bv2[3 + 2] = 1;
    bv1[5] = 1; bv2[3 + 5] = 1;

    bv4.append(bv0);
    bv4.append(bv1);

    //std::cout << bv0 << bv1 << std::endl;
    //std::cout << bv2 << std::endl;
    //std::cout << bv4 << std::endl;

    if (bv4 != bv2)
        throw UnitTestFail();
}


void BitVector_Copy_Test_Impl()
{
    u64 offset = 3;
    BitVector bb(128), c(128 - offset);


    for (u64 i : std::vector<u64>{ { 2,33,34,26,85,33,99,12,126 } })
    {
        bb[i] = true;
    }

    c.copy(bb, offset, 128 - offset);


    ////std::cout << "bb ";// << bb << Logger::endl;
    //for (u64 i = 0; i < bb.size(); ++i)
    //{
    //    if (bb[i]) std::cout << "1";
    //    else std::cout << "0";

    //}
    //std::cout << std::endl;
    //std::cout << "c   ";
    //for (u64 i = 0; i < c.size(); ++i)
    //{
    //    if (c[i]) std::cout << "1";
    //    else std::cout << "0";

    //}
    //std::cout << std::endl;

    for (u64 i = 0; i < 128 - offset; ++i)
    {
        if (bb[i + offset] != c[i])
            throw std::runtime_error("");

    }
}

void printMtx(std::array<block, 128>& data)
{
    for (auto& d : data)
    {
        std::cout << d << std::endl;
    }
}

void Transpose_Test_Impl()
{
    {

        std::array<block, 128> data;
        memset((u8*)data.data(), 0, sizeof(data));

        data[0] = _mm_set_epi64x(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
        data[1] = _mm_set_epi64x(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
        data[2] = _mm_set_epi64x(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
        data[3] = _mm_set_epi64x(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
        data[4] = _mm_set_epi64x(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
        data[5] = _mm_set_epi64x(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
        data[6] = _mm_set_epi64x(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
        data[7] = _mm_set_epi64x(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);

        //printMtx(data);
        eklundh_transpose128(data);


        for (auto& d : data)
        {
            if (neq(d, _mm_set_epi64x(0, 0xFF)))
            {
                std::cout << "expected" << std::endl;
                std::cout << _mm_set_epi64x(0xF, 0) << std::endl << std::endl;

                printMtx(data);

                throw UnitTestFail();
            }
        }
    }
    {


        std::array<block, 128> data;
        memset((u8*)data.data(), 0, sizeof(data));

        data[0] = _mm_set_epi64x(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
        data[1] = _mm_set_epi64x(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
        data[2] = _mm_set_epi64x(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
        data[3] = _mm_set_epi64x(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
        data[4] = _mm_set_epi64x(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
        data[5] = _mm_set_epi64x(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
        data[6] = _mm_set_epi64x(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
        data[7] = _mm_set_epi64x(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);

        sse_transpose128(data);


        for (auto& d : data)
        {
            if (neq(d, _mm_set_epi64x(0, 0xFF)))
            {
                std::cout << "expected" << std::endl;
                std::cout << _mm_set_epi64x(0xF, 0) << std::endl << std::endl;

                printMtx(data);

                throw UnitTestFail();
            }
        }
    }

    {
        PRNG prng(ZeroBlock);

        std::array<std::array<block, 8>, 128> data;

        prng.get((u8*)data.data(), sizeof(block) * 8 * 128);


        std::array<std::array<block,8>, 128> data2 = data;

        sse_transpose128x1024(data);


        for (u64 i = 0; i < 8; ++i)
        {

            std::array<block, 128> sub;

            for (u64 j = 0; j < 128; ++j)
            {
                sub[j] = data2[j][i];
            }

            sse_transpose128(sub);

            for (u64 j = 0; j < 128; ++j)
            {
                if(neq(sub[j],data[j][i]))
                    throw UnitTestFail();
            }
        }

    }
}


void KosOtExt_100Receive_Test_Impl()
{
    setThreadName("Sender");

    BtIOService ios(0);
    BtEndpoint ep0(ios, "127.0.0.1", 1212, true, "ep");
    BtEndpoint ep1(ios, "127.0.0.1", 1212, false, "ep");
    Channel& senderChannel = ep1.addChannel("chl", "chl");
    Channel& recvChannel = ep0.addChannel("chl", "chl");

    PRNG prng0(_mm_set_epi32(4253465, 3434565, 234435, 23987045));
    PRNG prng1(_mm_set_epi32(4253233465, 334565, 0, 235));

    u64 numOTs = 200;

    std::vector<block> recvMsg(numOTs), baseRecv(128);
    std::vector<std::array<block, 2>> sendMsg(numOTs), baseSend(128);
    BitVector choices(numOTs), baseChoice(128);
    choices.randomize(prng0);
    baseChoice.randomize(prng0);


    for (u64 i = 0; i < 128; ++i)
    {
        baseSend[i][0] = prng0.get<block>();
        baseSend[i][1] = prng0.get<block>();
        baseRecv[i] = baseSend[i][baseChoice[i]];
    }


    KosOtExtSender sender;
    KosOtExtReceiver recv;

    std::thread thrd = std::thread([&]() {
        setThreadName("receiver");

        recv.setBaseOts(baseSend);
        recv.receive(choices, recvMsg, prng0, recvChannel);
    });

    sender.setBaseOts(baseRecv, baseChoice);
    sender.send(sendMsg, prng1, senderChannel);
    thrd.join();

    //for (u64 i = 0; i < baseOTs.receiver_outputs.size(); ++i)
    //{
    //    std::cout << sender.GetMessage(i, 0) << " " << sender.GetMessage(i, 1) << "\n" << recv.GetMessage(1) << "  " << recv.mChoiceBits[i] << std::endl;
    //}

    OT_100Receive_Test(choices, recvMsg, sendMsg);



    senderChannel.close();
    recvChannel.close();


    ep1.stop();
    ep0.stop();

    ios.stop();

    //senderNetMgr.Stop();
    //recvNetMg
}


void LzKosOtExt_100Receive_Test_Impl()
{
    setThreadName("Sender");

    BtIOService ios(0);
    BtEndpoint ep0(ios, "127.0.0.1", 1212, true, "ep");
    BtEndpoint ep1(ios, "127.0.0.1", 1212, false, "ep");
    Channel& senderChannel = ep1.addChannel("chl", "chl");
    Channel& recvChannel = ep0.addChannel("chl", "chl");

    PRNG prng0(_mm_set_epi32(4253465, 3434565, 234435, 23987045));
    PRNG prng1(_mm_set_epi32(4253233465, 334565, 0, 235));

    u64 numOTs = 200;

    std::vector<block> recvMsg(numOTs), baseRecv(128);
    std::vector<std::array<block, 2>> sendMsg(numOTs), baseSend(128);
    BitVector choices(numOTs), baseChoice(128);
    choices.randomize(prng0);
    baseChoice.randomize(prng0);


    for (u64 i = 0; i < 128; ++i)
    {
        baseSend[i][0] = prng0.get<block>();
        baseSend[i][1] = prng0.get<block>();
        baseRecv[i] = baseSend[i][baseChoice[i]];
    }


    LzKosOtExtSender sender;
    LzKosOtExtReceiver recv;

    std::thread thrd = std::thread([&]() {
        setThreadName("receiver");

        recv.setBaseOts(baseSend);
        recv.receive(choices, recvMsg, prng0, recvChannel);
    });

    sender.setBaseOts(baseRecv, baseChoice);
    sender.send(sendMsg, prng1, senderChannel);
    thrd.join();

    //for (u64 i = 0; i < baseOTs.receiver_outputs.size(); ++i)
    //{
    //    std::cout << sender.GetMessage(i, 0) << " " << sender.GetMessage(i, 1) << "\n" << recv.GetMessage(1) << "  " << recv.mChoiceBits[i] << std::endl;
    //}

    OT_100Receive_Test(choices, recvMsg, sendMsg);



    senderChannel.close();
    recvChannel.close();


    ep1.stop();
    ep0.stop();

    ios.stop();

    //senderNetMgr.Stop();
    //recvNetMg
}


void IknpOtExt_100Receive_Test_Impl()
{
    setThreadName("Sender");

    BtIOService ios(0);
    BtEndpoint ep0(ios, "127.0.0.1", 1212, true, "ep");
    BtEndpoint ep1(ios, "127.0.0.1", 1212, false, "ep");
    Channel& senderChannel = ep1.addChannel("chl", "chl");
    Channel& recvChannel = ep0.addChannel("chl", "chl");

    PRNG prng0(_mm_set_epi32(4253465, 3434565, 234435, 23987045));
    PRNG prng1(_mm_set_epi32(4253233465, 334565, 0, 235));

    u64 numOTs = 200;

    std::vector<block> recvMsg(numOTs), baseRecv(128);
    std::vector<std::array<block, 2>> sendMsg(numOTs), baseSend(128);
    BitVector choices(numOTs), baseChoice(128);
    choices.randomize(prng0);
    baseChoice.randomize(prng0);

    prng0.get((u8*)baseSend.data()->data(), sizeof(block) * 2 * baseSend.size());
    for (u64 i = 0; i < 128; ++i)
    {
        baseRecv[i] = baseSend[i][baseChoice[i]];
    }

    IknpOtExtSender sender;
    IknpOtExtReceiver recv;

    std::thread thrd = std::thread([&]() {



        recv.setBaseOts(baseSend);
        recv.receive(choices, recvMsg, prng0, recvChannel);
    });



    //{
    //    std::lock_guard<std::mutex> lock(mMtx);
    //    for (u64 i = 0; i < baseOTs.receiver_outputs.size(); ++i)
    //    {
    //        std::cout << "i  " << baseOTs.receiver_outputs[i] << " " << (int)baseOTs.receiver_inputs[i] << std::endl;
    //    }
    //}
    sender.setBaseOts(baseRecv, baseChoice);
    sender.send(sendMsg, prng1, senderChannel);
    thrd.join();

    //for (u64 i = 0; i < baseOTs.receiver_outputs.size(); ++i)
    //{
    //    std::cout << sender.GetMessage(i, 0) << " " << sender.GetMessage(i, 1) << "\n" << recv.GetMessage(1) << "  " << recv.mChoiceBits[i] << std::endl;
    //}
    OT_100Receive_Test(choices, recvMsg, sendMsg);




    senderChannel.close();
    recvChannel.close();


    ep1.stop();
    ep0.stop();

    ios.stop();

    //senderNetMgr.Stop();
    //recvNetMg
}







