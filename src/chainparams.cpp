// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2014-2018 The Anodos Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"
#include "arith_uint256.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

#define GENESIS_MERKLE_ROOT "0x9213715ba35de2b59fe4acc846e504a5c8061d175c53fb2f9c280b9ae21e5a86"

#define MAINNET_GENESIS_HASH "0x00000a0c7d3651a452b177e9b52c340fc169ae1f7a335aa618df523c92bec66b"
#define MAINNET_GENESIS_NONCE 58016UL
#define MAINNET_GENESIS_TIMESTAMP 1534068426UL

#define TESTNET_GENESIS_HASH "0x0000011af7ee5f71436978f568986571e4eb2b029d3cf9d9e2a5028e3aad346b"
#define TESTNET_GENESIS_NONCE 332722UL
#define TESTNET_GENESIS_TIMESTAMP 1534120314UL

#define REGTEST_GENESIS_HASH "0x65720dc63e37ead3cb4f280b11cbd1734309b64f4d32bd10a9f513483de15b72"
#define REGTEST_GENESIS_NONCE 1UL
#define REGTEST_GENESIS_TIMESTAMP 1534120443UL

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "08/12/2018 Anodos 2.0 Is Born";
    const CScript genesisOutputScript = CScript() << ParseHex("040d9499d6bcd8fe2e1d15bfd369990e5d8e2ba4fa31541d1a6ecea9ed4d74ba1f6dd485319dbca113000cb4b45a6d6499d8965bf9eebac2b907eb97ec99603aab") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nAnodosHeight = 90000;
        consensus.nSubsidyHalvingInterval = 262800; // one year
        consensus.nFirstSubsidyReduceBlock = 262800;
        consensus.nBudgetPaymentsStartBlock = 92000; // year 10000+
		consensus.nBudgetPaymentsCycleBlocks = 16616;
		consensus.nBudgetPaymentsWindowBlocks = 100;
		consensus.nBudgetProposalEstablishingTime = 60*60*24;
        consensus.nSuperblockStartBlock = 92000; // year 10000+
		consensus.nSuperblockCycle = 16616;
		consensus.nGovernanceMinQuorum = 10;
		consensus.nGovernanceFilterElements = 20000;
		consensus.nMasternodeMinimumConfirmations = 15;
		consensus.nMajorityEnforceBlockUpgrade = 750;
		consensus.nMajorityRejectBlockOutdated = 950;
		consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 92000;
        consensus.BIP34Hash = uint256S("0x00000001d76d0aec1deaa4ec32405ed03e8a025307a0da9b60d18d3b0f7ef9db");
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 30 * 60; // Anodos: 2 blocks
		consensus.nPowTargetSpacing = 2 * 60; // Anodos old rule: 2 minutes
        consensus.nPowNewTargetSpacing = 2 * 60; // Anodos new block time: 3 minutes
		consensus.fPowAllowMinDifficultyBlocks = false;
		consensus.fPowNoRetargeting = false;
		consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
		consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.nTriHashAlgoChangeStart = 11531612800;//july 15 2018 UTC
        consensus.nAnodosForkBlock = 9200000000;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999;   // December 31, 2008

                // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1502280000; // Aug 9th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1533816000;   // Aug 9th, 2018
        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000000003e1771746eb14f"); //121429
        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0000000009cc1f28c974798e6222442be48a61a8f23a1497d4cdada1c38a76c4"); //1938

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x1c;
        pchMessageStart[1] = 0x41;
        pchMessageStart[2] = 0xd2;
        pchMessageStart[3] = 0xe4;
        vAlertPubKey = ParseHex("0243B9048EAF71917BA52581C9B6C9DC428A5A3B947B5DD7EC3CF7CE3298F2C906");
        nDefaultPort = 1929;
        nMaxTipAge = 6 * 60 * 60; // ~144 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in bitcoin
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(MAINNET_GENESIS_TIMESTAMP, MAINNET_GENESIS_NONCE, 0x1e0ffff0, 1, 50 * COIN);
        
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S(MAINNET_GENESIS_HASH));
        assert(genesis.hashMerkleRoot == uint256S(GENESIS_MERKLE_ROOT));

        //vSeeds.push_back(CDNSSeedData("anodos1", "seed1.anodos.info"));
       // vSeeds.push_back(CDNSSeedData("anodos2", "seed2.anodos.info"));
       // vSeeds.push_back(CDNSSeedData("anodos3", "seed3.anodos.info"));
       // vSeeds.push_back(CDNSSeedData("anodos4", "seed4.anodos.info"));
        //vSeeds.push_back(CDNSSeedData("dnsseed", "dnsseed.anodos.info"));

        // Anodos addresses start with 'A'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,23);
        // Anodos script addresses start with 'a'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,18);
        // Anodos private keys start with '7' or 'P' (?)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,191);
        // Anodos BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Anodos BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // Anodos BIP44 coin type is '5'
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x05).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 60*60; // fulfilled requests expire in 1 hour
        //strSporkPubKey = "04d9491a6cf40a2afaf51de3939eadca259a95843b637f82c772a5719bc64051409031803a1c33f1f9b14c24a2d6937fe5b76ffa99a9730aa27726f9934cabf7f4";
        strSporkPubKey =              "042D80570F286F137F0846AC0D89B7ADB6626794A13A37A8EE3FB62DAA53AB32DE2B344880CE38BC1AAC9F42E77BD67DE06E91EA5F18CE4F137EAF65705F629B7A"; //"VLNBCt7v9VxHzw19ezz6dhi5pFF7EJpHrqG8mVHwhPqftEsAVn3V";
        strMasternodePaymentsPubKey = "0243B9048EAF71917BA52581C9B6C9DC428A5A3B947B5DD7EC3CF7CE3298F2C905";

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of(0, uint256S(TESTNET_GENESIS_HASH)),
            0, // * UNIX timestamp of last checkpoint block
            0,          // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            0};

    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 2000;
        consensus.nFirstSubsidyReduceBlock = 2000;
        consensus.nMasternodePaymentsStartBlock = 100; // not true, but it's ok as long as it's less then nMasternodePaymentsIncreaseBlock
        consensus.nMasternodePaymentsIncreaseBlock = 158000;
        consensus.nMasternodePaymentsIncreasePeriod = 576 * 30;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 2100000000;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 2100000000; // NOTE: Should satisfy nSuperblockStartBlock > nBudgetPeymentsStartBlock
        consensus.nSuperblockCycle = 24; // Superblocks can be issued hourly on testnet
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 500;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.BIP34Height = 21111; // FIX
        consensus.BIP34Hash = uint256S("0x0000000023b3a96d3484e5abb3755c413e7d41500f8e2a5c3f0dd01299cd8ef8"); // FIX
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 60 * 60; // Anodos: 1 hour
        consensus.nPowTargetSpacing = 2 * 60; // Anodos: 2 minutes
        consensus.nPowNewTargetSpacing = 180; // Anodos new block time: 3 minutes
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.nTriHashAlgoChangeStart = 1531612800;//july 15 2018 UTC
        consensus.nAnodosForkBlock = 90000;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1502280000; // Aug 9th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1533816000; // Aug 9th, 2018

        pchMessageStart[0] = 0x2b;
        pchMessageStart[1] = 0x4a;
        pchMessageStart[2] = 0xf3;
        pchMessageStart[3] = 0xa2;
        vAlertPubKey = ParseHex("02AD1FCAC38C0EAAE88EB522617B0E3DB516C8AF42884953CC53DC04015FE6DAE4");
        nDefaultPort = 23323;
        nMaxTipAge = 0x7fffffff; // allow mining on top of old blocks for testnet
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(TESTNET_GENESIS_TIMESTAMP, TESTNET_GENESIS_NONCE, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S(TESTNET_GENESIS_HASH));
        assert(genesis.hashMerkleRoot == uint256S(GENESIS_MERKLE_ROOT));

        // Testnet Anodos addresses start with 'n'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 83);
        // Testnet Anodos script addresses start with '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 20);
        // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 240);
        // Testnet Anodos BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet Anodos BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet Anodos BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds.clear();
        vSeeds.clear();

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 5 * 60; // fulfilled requests expire in 5 minutes

        strSporkPubKey = "049EB63DAEDA649F6E70D42F7B032B43031D1638620A2A127E98C96CA59FDB194F4FAD27FF6455E667E7A6E369375019DE6D0E532212180AE8557CCE3A7CF6A3DA";
        strMasternodePaymentsPubKey = "02AD1FCAC38C0EAAE88EB522617B0E3DB516C8AF42884953CC53DC04015FE6DAE3";

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of(0, uint256S(TESTNET_GENESIS_HASH)),
            0, // * UNIX timestamp of last checkpoint block
            0,          // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            0};
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMasternodePaymentsStartBlock = 240;
        consensus.nMasternodePaymentsIncreaseBlock = 350;
        consensus.nMasternodePaymentsIncreasePeriod = 10;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 1000;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 1500;
        consensus.nSuperblockCycle = 10;
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 100;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = -1; // BIP34 has not necessarily activated on regtest
        consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 60 * 60; // Anodos: 1 hour
        consensus.nPowTargetSpacing = 2 * 60; // Anodos: 2 minutes
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;

        pchMessageStart[0] = 0x1a;
        pchMessageStart[1] = 0x3e;
        pchMessageStart[2] = 0xe5;
        pchMessageStart[3] = 0xb4;
        nMaxTipAge = 6 * 60 * 60; // ~144 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in bitcoin
        nDefaultPort = 17617;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(REGTEST_GENESIS_TIMESTAMP, REGTEST_GENESIS_NONCE, 0x207fffff, 1, 50 * COIN);

        consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S(REGTEST_GENESIS_HASH));
        //assert(genesis.hashMerkleRoot == uint256S(GENESIS_MERKLE_ROOT));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes

        //checkpointData = (CCheckpointData){
        //    boost::assign::map_list_of
        //    ( 0, uint256S(REGTEST_GENESIS_HASH)),
        //    0,
        //    0,
        //    0
        //};
        
        // Regtest Anodos addresses start with 'n'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,112);
        // Regtest Anodos script addresses start with '5'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,10);
        // Regtest private keys start with '5' or 'c' (Bitcoin defaults) (?)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,240);
        // Regtest Anodos BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Regtest Anodos BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Regtest Anodos BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();
   }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}