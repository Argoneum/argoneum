// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "primitives/block.h"

#include "hash.h"
#include "tinyformat.h"
#include "utilstrencodings.h"
#include "crypto/common.h"
#include "crypto/skein.h"
#include "crypto/lyra2z/lyra2z.h"

// Define hashing function
#define HASH_SKEIN

uint256 CBlockHeader::GetHash() const
{
#ifdef HASH_X11
    return HashX11(BEGIN(nVersion), END(nNonce));
#endif
#ifdef HASH_X16R
    return HashX16R(BEGIN(nVersion), END(nNonce), hashPrevBlock);
#endif
#ifdef HASH_LYRA2Z
    uint256 thash;
    lyra2z_hash(BEGIN(nVersion), BEGIN(thash));
    return thash;
#endif
#ifdef HASH_SKEIN
    uint256 thash;
    uint32_t len = (END(nNonce) - BEGIN(nVersion)) * sizeof(BEGIN(nVersion)[0]);
    skein_hash(&BEGIN(nVersion)[0], (char *) &thash, len);
    return thash;
#endif
#if !(defined(HASH_X11) || defined(HASH_X16R) || defined(HASH_LYRA2Z) || defined(HASH_SKEIN))
#error No hashing function defined (HASH_X11 | HASH_X16R | HASH_LYRA2Z | HASH_SKEIN)
#endif
}

std::string CBlock::ToString() const
{
    std::stringstream s;
    s << strprintf("CBlock(hash=%s, ver=%d, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, vtx=%u)\n",
        GetHash().ToString(),
        nVersion,
        hashPrevBlock.ToString(),
        hashMerkleRoot.ToString(),
        nTime, nBits, nNonce,
        vtx.size());
    for (unsigned int i = 0; i < vtx.size(); i++)
    {
        s << "  " << vtx[i].ToString() << "\n";
    }
    return s.str();
}
