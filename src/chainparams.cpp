// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2014-2017 The Dash Core developers
// Copyright (c) 2018-2018 The Argoneum Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

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
 *
 * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
 *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
 *   vMerkleTree: e0028e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "2018/11/01: Argoneum, the masternode solutions platform was born";
    const CScript genesisOutputScript = CScript() << ParseHex("04480f351d994e150563c3c686e25247513ccfcd98d8826fb450f164f9400659e50b066b6fc2d110b7ed61a27a2b932e3f4e5564da19716dd3e5d5fc0e4bfed625") << OP_CHECKSIG;
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
        consensus.nSubsidyHalvingStartBlock = 525600; // (60 / 2.5 * 24 * 365.25) = 210384 blocks/year
        consensus.nSubsidyHalvingInterval = 525600;    // 17600 average number of block per month
        consensus.nSubsidyHalvingRate = 4; // every nSubsidyHalvingInterval since nSubsidyHalvingStartBlock nSubsidy /= nSubsidyHalvingRate
        consensus.nMasternodePaymentsStartBlock = 0;
        consensus.nMasternodePaymentsIncreaseBlock = 5000;
        consensus.nMasternodePaymentsIncreasePeriod = 0;
        consensus.nInstantSendKeepLock = 24;
        consensus.nBudgetPaymentsStartBlock = 999999998;
        consensus.nBudgetPaymentsCycleBlocks = 43200;
        consensus.nBudgetPaymentsWindowBlocks = 100;
        consensus.nBudgetProposalEstablishingTime = 60*60*24;
        consensus.nSuperblockStartBlock = 999999999; // NOTE: Should satisfy nSuperblockStartBlock > nBudgetPeymentsStartBlock
        consensus.nSuperblockCycle = 43200;
        consensus.nGovernanceMinQuorum = 10;
        consensus.nGovernanceFilterElements = 20000;
        consensus.nMasternodeMinimumConfirmations = 15;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 0;  // genesis
        consensus.BIP34Hash = uint256S("0x0000019913c8bb39636467e961b8c0f4d3d656437de2cd876f2da6a05cc8d393");   // genesis
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // Argoneum: 1 day, legacy PoW calculation
        consensus.nPowTargetSpacing = 1 * 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nPowKGWHeight = 0;   // nPowKGWHeight >= nPowDGWHeight means "no KGW"
        consensus.nPowDGWHeight = 0;   // since start
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1572393600; // Oct 30, 2019 // 1486252800; // Feb 5th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1577836800; // Jan 01, 2020 // 1517788800; // Feb 5th, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nWindowSize = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nThreshold = 1612; // 80% of 2016

        // Deployment of DIP0001
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 1572393600; // Oct 30, 2019 // 1508025600; // Oct 15th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 1588291200; // May 01, 2020 // 1539561600; // Oct 15th, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nWindowSize = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nThreshold = 1612; // 80% of 2016

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000000000001f000000000");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0000000016c59e2bdda3ec47c79cf35abda8c95b8268487c97195f4e6596c689"); // 467870

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x41;
        pchMessageStart[1] = 0x47;
        pchMessageStart[2] = 0x4d;
        pchMessageStart[3] = 0x00;
        vAlertPubKey = ParseHex("040219e8060882c33d8cf14b651439427158213ff1761cbd52d736b6f2e0abbd2bb7371f9e0e9324176f9a62260378f0b7e686c76d9f927f5a4c1a8bfa2e69d7d4");
        nDefaultPort = 9898;
        nMaxTipAge = 6 * 60 * 60; // ~144 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in bitcoin
        nDelayGetHeadersTime = 24 * 60 * 60;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1541005200, 1533603, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000019913c8bb39636467e961b8c0f4d3d656437de2cd876f2da6a05cc8d393"));
        assert(genesis.hashMerkleRoot == uint256S("0xeda45c4cb6ce5b81fa5bc5ce6a9648e00059f4e9e527d7587dacbc42d9e41384"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("argoneum.net", "seed1.argoneum.net"));
        vSeeds.push_back(CDNSSeedData("argoneum.net", "seed2.argoneum.net"));
        vSeeds.push_back(CDNSSeedData("argoneum.net", "seed3.argoneum.net"));
        vSeeds.push_back(CDNSSeedData("argoneum.net", "seed4.argoneum.net"));
        vSeeds.push_back(CDNSSeedData("argoneum.net", "seed5.argoneum.net"));

        // Argoneum addresses
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,0x32);
        // Argoneum script addresses
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,0x61);
        // Argoneum private keys start with '7'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,0xbf); // 191
        // Argoneum BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Argoneum BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        // Argoneum BIP44 coin type
        nExtCoinType = 5;

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 60*60; // fulfilled requests expire in 1 hour
        strSporkPubKey = "0452fd622b78642e426094dcd7cf682a8d23979c593b33d38707b040d2399d9c37bf1eeef5f3e662c2278044522d9afe0a7ac9a56643cd7b8054ea5087157789f2";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (    100, uint256S("0x0000000760ee58284cd534b6e6c25536ce9f9afaca754276dd3b65e362fa494d"))
            (  14000, uint256S("0x00000000000139bd49235ffe699ce86042ebd48aea661f51e2c4a634f3c04841"))
            ( 467870, uint256S("0x0000000016c59e2bdda3ec47c79cf35abda8c95b8268487c97195f4e6596c689"))
            ,
            1570541470, // * UNIX timestamp of last checkpoint block
            761387,     // * total number of transactions between genesis and last checkpoint
            3000        // * estimated number of transactions per day after checkpoint
        };

        founderAddress = "M8CbM4XHV35PsEQKKQBPqbUNaA6u5JLbNU";
        founderFee = 0.05;
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
        consensus.nSubsidyHalvingStartBlock = 525600;
        consensus.nSubsidyHalvingInterval = 525600;
        consensus.nSubsidyHalvingRate = 4;
        consensus.nMasternodePaymentsStartBlock = 0;
        consensus.nMasternodePaymentsIncreaseBlock = 5000;
        consensus.nMasternodePaymentsIncreasePeriod = 0;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 999999998;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 999999999; // NOTE: Should satisfy nSuperblockStartBlock > nBudgetPeymentsStartBlock
        consensus.nSuperblockCycle = 24; // Superblocks can be issued hourly on testnet
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 500;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.BIP34Height = 0; // genesis
        consensus.BIP34Hash = uint256S("0x00000e91f3a63b1b81797a52348931a7078c0eba642bb79e64090cdf38764e83"); // genesis
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // Argoneum: 1 day
        consensus.nPowTargetSpacing = 1 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nPowKGWHeight = 0; // nPowKGWHeight >= nPowDGWHeight means "no KGW"
        consensus.nPowDGWHeight = 0;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;

        // Deployment of DIP0001
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nWindowSize = 100;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nThreshold = 50; // 50% of 100

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00"); // unknown yet

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00"); // unknown yet

        pchMessageStart[0] = 0x41;
        pchMessageStart[1] = 0x47;
        pchMessageStart[2] = 0x4d;
        pchMessageStart[3] = 0x01;
        vAlertPubKey = ParseHex("0435fe2935037b916e8cb9626802c49a64ecf7062454226ddfa3f2f6735c4d9b0bc31934622f3ae140b0c7fda53c8233eecf7c9fb8e88925fb3d1e5afb83cf00b7");
        nDefaultPort = 10898;
        nMaxTipAge = 0x7fffffff; // allow mining on top of old blocks for testnet
        nDelayGetHeadersTime = 24 * 60 * 60;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1541005201, 261628, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000e91f3a63b1b81797a52348931a7078c0eba642bb79e64090cdf38764e83"));
        assert(genesis.hashMerkleRoot == uint256S("0xeda45c4cb6ce5b81fa5bc5ce6a9648e00059f4e9e527d7587dacbc42d9e41384"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("argoneum.net", "testnet-seed1.argoneum.net"));
        vSeeds.push_back(CDNSSeedData("argoneum.net", "testnet-seed2.argoneum.net"));
        vSeeds.push_back(CDNSSeedData("argoneum.net", "testnet-seed3.argoneum.net"));

        // Testnet Argoneum addresses
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,0x80);
        // Testnet Argoneum script addresses
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,0x42);
        // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239); // 0xEF
        // Testnet Argoneum BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet Argoneum BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        // Testnet Argoneum BIP44 coin type is '1' (All coin's testnet default)
        nExtCoinType = 1;

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes
        strSporkPubKey = "04da26a423de1493d1f34d3fd1dddaad771228c226e9eaf2110a840b1c7651cb3a4078dfec7cb175f183e8d3c6d6196f98898821c396d7e8a44dfaf4d0b0a2a9c0";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0x00000e91f3a63b1b81797a52348931a7078c0eba642bb79e64090cdf38764e83")),
            0,          // * UNIX timestamp of last checkpoint block
            0,          // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            500         // * estimated number of transactions per day after checkpoint
        };

        founderAddress = "tt43RVJKA3J59g2XQiGXPZhrxmp7wPdz9v";
        founderFee = 0.05;
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
        consensus.nSubsidyHalvingStartBlock = 525;
        consensus.nSubsidyHalvingInterval = 525;
        consensus.nSubsidyHalvingRate = 4;
        consensus.nMasternodePaymentsStartBlock = 0;
        consensus.nMasternodePaymentsIncreaseBlock = 50;
        consensus.nMasternodePaymentsIncreasePeriod = 0;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 999999998;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 999999999;
        consensus.nSuperblockCycle = 24;
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 100;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = -1; // BIP34 has not necessarily activated on regtest
        consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // Argoneum: 1 day
        consensus.nPowTargetSpacing = 1 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nPowKGWHeight = 0; // same as mainnet
        consensus.nPowDGWHeight = 0; // same as mainnet
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0x41;
        pchMessageStart[1] = 0x47;
        pchMessageStart[2] = 0x4d;
        pchMessageStart[3] = 0x02;
        vAlertPubKey = ParseHex("04dd388c457c16bbecae4ffff174491e1ff01dfc822b35327d07851ba273f31d38a2935a3710b0aa4603d38386628579cbf4c2409ac4dc67cf42e40c6003b29792");
        nMaxTipAge = 6 * 60 * 60; // ~144 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in bitcoin
        nDelayGetHeadersTime = 0; // never delay GETHEADERS in regtests
        nDefaultPort = 20898;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1541005202, 606056, 0x207fffff, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000002476efd1ec76d1ac35100783a269cc273778e656e7fdb5a00a43184450f"));
        assert(genesis.hashMerkleRoot == uint256S("0xeda45c4cb6ce5b81fa5bc5ce6a9648e00059f4e9e527d7587dacbc42d9e41384"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes
        strSporkPubKey = "043ad99dff1ca8ac6812d9d98e116f27e75f1e74987858dcde0e200a353aaacd0d34f856606a876f8081d47e5d5a82ae26e372bcf7fd309d35ef2b548ec9c79559";

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x000002476efd1ec76d1ac35100783a269cc273778e656e7fdb5a00a43184450f")),
            0,
            0,
            0
        };

        founderAddress = "trztJft4k4jF6BiiiTJFabupHNj1SfdSD3";
        founderFee = 0.05;

        // Regtest Argoneum addresses
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,0x80);
        // Regtest Argoneum script addresses
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,0x42);
        // Regtest private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        // Regtest Argoneum BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Regtest Argoneum BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        // Regtest Argoneum BIP44 coin type is '1' (All coin's testnet default)
        nExtCoinType = 1;
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
