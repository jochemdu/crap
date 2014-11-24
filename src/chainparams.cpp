// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
    0x12345678
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xff;
        pchMessageStart[1] = 0xd9;
        pchMessageStart[2] = 0xc6;
        pchMessageStart[3] = 0xcd;
        vAlertPubKey = ParseHex("04F04441C4757F356290A37C313C3772C5BC5003E898EB2E0CF365795543A7BF690C8BBBFA32EE3A3325477CE2000B7D0453EFBB203329D0F9DF34D5927D022BC9");
        nDefaultPort = 12028;
        nRPCPort = 14028;

        bnProofOfWorkLimit[ALGO_SHA256D] = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_SCRYPT]  = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_GROESTL] = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_SKEIN]   = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_QUBIT]   = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        const char* pszTimestamp = "27/09/2014 - Microsoft: Windows 8-gebruikers kunnen gratis upgraden naar Windows 9";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 8000;
        txNew.vout[0].scriptPubKey = CScript() << 0x0 << OP_CHECKSIG;          
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1411832479;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 4348642; //2447652
 
		printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("genesis.nTime = %u \n", genesis.nTime);
        printf("genesis.nNonce = %u \n", genesis.nNonce);
        printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
 		hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xd9693b5ae46b91e8dfe26c3c0d693f28947b0bce3bec3d26c8179ca4ebaad60d")); //0x7497ea1b465eb39f1c8f507bc877078fe016d6fcb6dfad3a64c98dcc6e1e8496
		assert(genesis.hashMerkleRoot == uint256("0x0d0d10b5c418abb25d36b52c99c1921b0f3971ef742fe09d4753cf94f1296b6b"));


       // If genesis block hash does not match, then generate new genesis hash.
	   // first run, take merklehash, insert and then recompile and run for genesis hash
    if (genesis.GetHash() != hashGenesisBlock)
    {
        printf("Searching for genesis block...\n");
        // This will figure out a valid hash and Nonce if you're
        // creating a different genesis block:
        uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
        uint256 thash;
		char scratchpad[SCRYPT_SCRATCHPAD_SIZE];
        while(true)
        {
            #if defined(USE_SSE2)
                // Detection would work, but in cases where we KNOW it always has SSE2,
                // it is faster to use directly than to use a function pointer or conditional.
			#if defined(_M_X64) || defined(__x86_64__) || defined(_M_AMD64) || (defined(MAC_OSX) && defined(__i386__))
                // Always SSE2: x86_64 or Intel MacOS X
                scrypt_1024_1_1_256_sp_sse2(BEGIN(genesis.nVersion), BEGIN(thash), scratchpad);
			#else
                // Detect SSE2: 32bit x86 Linux or Windows
                scrypt_1024_1_1_256_sp(BEGIN(genesis.nVersion), BEGIN(thash), scratchpad);
			#endif
			#else
                // Generic scrypt
                scrypt_1024_1_1_256_sp_generic(BEGIN(genesis.nVersion), BEGIN(thash), scratchpad);
			#endif
            if (thash <= hashTarget)
                break;
            if ((genesis.nNonce & 0xFFF) == 0)
            {
                printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
            }
            ++genesis.nNonce;
            if (genesis.nNonce == 0)
            {
                printf("NONCE WRAPPED, incrementing time\n");
                ++genesis.nTime;
            }
        }
		printf("genesis.hashMerkleRoot =%s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("genesis.nTime = %u \n", genesis.nTime);
        printf("genesis.nNonce = %u \n", genesis.nNonce);
        printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
	}
        vSeeds.push_back(CDNSSeedData("seed #0", "node1.unat.ga"));
        vSeeds.push_back(CDNSSeedData("seed #1", "192.168.154.128"));
        vSeeds.push_back(CDNSSeedData("seed #2", "192.168.154.129"));
		vSeeds.push_back(CDNSSeedData("seed #3", "192.168.2.46"));
		vSeeds.push_back(CDNSSeedData("seed #4", "192.168.2.39"));
		vSeeds.push_back(CDNSSeedData("seed #5", "82.75.141.118:12022"));
		vSeeds.push_back(CDNSSeedData("seed #6", "82.75.141.118:12028"));
		vSeeds.push_back(CDNSSeedData("seed #6", "82.75.141.118"));
		vSeeds.push_back(CDNSSeedData("seed #7", "192.168.2.46:12022"));
		vSeeds.push_back(CDNSSeedData("seed #8", "192.168.2.46"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(130);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(8);
        base58Prefixes[SECRET_KEY] =     list_of(128);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);
        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;



//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xac;
        pchMessageStart[1] = 0xa1;
        pchMessageStart[2] = 0xa7;
        pchMessageStart[3] = 0xac;
        vAlertPubKey = ParseHex("b5dca8039e300198e5fe7cd23bdd1728e2a444af34c447dbd0916fa3430a68c2");
        nDefaultPort = 14027;
        nRPCPort = 12027;
        strDataDir = "testnet3";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1411832479;
        genesis.nNonce = 4348642;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xd9693b5ae46b91e8dfe26c3c0d693f28947b0bce3bec3d26c8179ca4ebaad60d")); //0x7497ea1b465eb39f1c8f507bc877078fe016d6fcb6dfad3a64c98dcc6e1e8496
		assert(genesis.hashMerkleRoot == uint256("0x0d0d10b5c418abb25d36b52c99c1921b0f3971ef742fe09d4753cf94f1296b6b"));
		// If genesis block hash does not match, then generate new genesis hash.
	    // first run, take merklehash, insert and then recompile and run for genesis hash
    if (genesis.GetHash() != hashGenesisBlock)
    {
        printf("Searching for genesis block...\n");
        // This will figure out a valid hash and Nonce if you're
        // creating a different genesis block:
        uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
        uint256 thash;
		char scratchpad[SCRYPT_SCRATCHPAD_SIZE];
        while(true)
        {
            #if defined(USE_SSE2)
                // Detection would work, but in cases where we KNOW it always has SSE2,
                // it is faster to use directly than to use a function pointer or conditional.
			#if defined(_M_X64) || defined(__x86_64__) || defined(_M_AMD64) || (defined(MAC_OSX) && defined(__i386__))
                // Always SSE2: x86_64 or Intel MacOS X
                scrypt_1024_1_1_256_sp_sse2(BEGIN(genesis.nVersion), BEGIN(thash), scratchpad);
			#else
                // Detect SSE2: 32bit x86 Linux or Windows
                scrypt_1024_1_1_256_sp(BEGIN(genesis.nVersion), BEGIN(thash), scratchpad);
			#endif
			#else
                // Generic scrypt
                scrypt_1024_1_1_256_sp_generic(BEGIN(genesis.nVersion), BEGIN(thash), scratchpad);
			#endif
            if (thash <= hashTarget)
                break;
            if ((genesis.nNonce & 0xFFF) == 0)
            {
                printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
            }
            ++genesis.nNonce;
            if (genesis.nNonce == 0)
            {
                printf("NONCE WRAPPED, incrementing time\n");
                ++genesis.nTime;
            }
        }
		printf("genesis.hashMerkleRoot =%s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("genesis.nTime = %u \n", genesis.nTime);
        printf("genesis.nNonce = %u \n", genesis.nNonce);
        printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
	}
        //assert(hashGenesisBlock == uint256("0xb5dca8039e300198e5fe7cd23bdd1728e2a444af34c447dbd0916fa3430a68c2"));

        vFixedSeeds.clear();
        vSeeds.clear();
        //vSeeds.push_back(CDNSSeedData("unattainiumv2.petertodd.org", "testnet-seed.unattainiumv2.petertodd.org"));
        //vSeeds.push_back(CDNSSeedData("bluematt.me", "testnet-seed.bluematt.me"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(111);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xb3;
        pchMessageStart[2] = 0xb2;
        pchMessageStart[3] = 0xdb;
        //nSubsidyHalvingInterval = 150;
       // bnProofOfWorkLimit = CBigNum();
        genesis.nTime = 1392796564;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 961533;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
        //assert(hashGenesisBlock == uint256("0x0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
