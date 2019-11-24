# Copyright (c) 2013-2016 The Bitcoin Core developers
# Copyright (c) 2014-2018 The Argoneum Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS) $(ERROR_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

BITCOIN_CONFIG_INCLUDES=-I$(builddir)/config
BITCOIN_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

BITCOIN_INCLUDES += -I$(srcdir)/secp256k1/include
BITCOIN_INCLUDES += $(UNIVALUE_CFLAGS)

LIBBITCOIN_SERVER=libargoneum_server.a
LIBBITCOIN_COMMON=libargoneum_common.a
LIBBITCOIN_CONSENSUS=libargoneum_consensus.a
LIBBITCOIN_CLI=libargoneum_cli.a
LIBBITCOIN_UTIL=libargoneum_util.a
LIBBITCOIN_CRYPTO=crypto/libargoneum_crypto.a
LIBBITCOINQT=qt/libargoneumqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

if ENABLE_ZMQ
LIBBITCOIN_ZMQ=libargoneum_zmq.a
endif
if BUILD_BITCOIN_LIBS
LIBBITCOINCONSENSUS=libargoneumconsensus.la
endif
if ENABLE_WALLET
LIBBITCOIN_WALLET=libargoneum_wallet.a
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBBITCOIN_UTIL) \
  $(LIBBITCOIN_COMMON) \
  $(LIBBITCOIN_CONSENSUS) \
  $(LIBBITCOIN_SERVER) \
  $(LIBBITCOIN_CLI) \
  $(LIBBITCOIN_WALLET) \
  $(LIBBITCOIN_ZMQ)

lib_LTLIBRARIES = $(LIBBITCOINCONSENSUS)

bin_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_BITCOIND
  bin_PROGRAMS += argoneumd
endif

if BUILD_BITCOIN_UTILS
  bin_PROGRAMS += argoneum-cli argoneum-tx
endif

.PHONY: FORCE check-symbols check-security
# argoneum core #
BITCOIN_CORE_H = \
  addrdb.h \
  activemasternode.h \
  addressindex.h \
  spentindex.h \
  addrman.h \
  alert.h \
  base58.h \
  bip39.h \
  bip39_english.h \
  blockencodings.h \
  bloom.h \
  cachemap.h \
  cachemultimap.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  core_io.h \
  core_memusage.h \
  cuckoocache.h \
  privatesend.h \
  privatesend-client.h \
  privatesend-server.h \
  privatesend-util.h \
  dsnotificationinterface.h \
  governance.h \
  governance-classes.h \
  governance-exceptions.h \
  governance-object.h \
  governance-validators.h \
  governance-vote.h \
  governance-votedb.h \
  flat-database.h \
  hdchain.h \
  httprpc.h \
  httpserver.h \
  indirectmap.h \
  init.h \
  instantx.h \
  key.h \
  keepass.h \
  keystore.h \
  dbwrapper.h \
  limitedmap.h \
  masternode.h \
  masternode-payments.h \
  masternode-sync.h \
  masternodeman.h \
  masternodeconfig.h \
  memusage.h \
  merkleblock.h \
  messagesigner.h \
  miner.h \
  net.h \
  net_processing.h \
  netaddress.h \
  netbase.h \
  netfulfilledman.h \
  netmessagemaker.h \
  noui.h \
  policy/fees.h \
  policy/policy.h \
  policy/rbf.h \
  pow.h \
  protocol.h \
  random.h \
  reverselock.h \
  rpc/client.h \
  rpc/protocol.h \
  rpc/server.h \
  rpc/register.h \
  scheduler.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  script/ismine.h \
  spork.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/events.h \
  support/lockedpool.h \
  sync.h \
  threadsafety.h \
  threadinterrupt.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utiltime.h \
  validation.h \
  validationinterface.h \
  versionbits.h \
  wallet/coincontrol.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/rpcwallet.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  warnings.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libargoneum_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between argoneumd and argoneum-qt
libargoneum_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libargoneum_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libargoneum_server_a_SOURCES = \
  activemasternode.cpp \
  addrman.cpp \
  addrdb.cpp \
  alert.cpp \
  bloom.cpp \
  blockencodings.cpp \
  chain.cpp \
  checkpoints.cpp \
  dsnotificationinterface.cpp \
  httprpc.cpp \
  httpserver.cpp \
  init.cpp \
  instantx.cpp \
  dbwrapper.cpp \
  governance.cpp \
  governance-classes.cpp \
  governance-object.cpp \
  governance-validators.cpp \
  governance-vote.cpp \
  governance-votedb.cpp \
  masternode.cpp \
  masternode-payments.cpp \
  masternode-sync.cpp \
  masternodeconfig.cpp \
  masternodeman.cpp \
  merkleblock.cpp \
  messagesigner.cpp \
  miner.cpp \
  net.cpp \
  netfulfilledman.cpp \
  net_processing.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/policy.cpp \
  pow.cpp \
  privatesend.cpp \
  privatesend-server.cpp \
  rest.cpp \
  rpc/blockchain.cpp \
  rpc/masternode.cpp \
  rpc/governance.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/server.cpp \
  script/sigcache.cpp \
  script/ismine.cpp \
  sendalert.cpp \
  spork.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  ui_interface.cpp \
  validation.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(BITCOIN_CORE_H)

if ENABLE_ZMQ
libargoneum_zmq_a_CPPFLAGS = $(BITCOIN_INCLUDES) $(ZMQ_CFLAGS)
libargoneum_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libargoneum_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp
endif


# wallet: shared between argoneumd and argoneum-qt, but only linked
# when wallet enabled
libargoneum_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libargoneum_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libargoneum_wallet_a_SOURCES = \
  keepass.cpp \
  privatesend-client.cpp \
  privatesend-util.cpp \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  policy/rbf.cpp \
  $(BITCOIN_CORE_H)


# crypto primitives library
crypto_libargoneum_crypto_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_CONFIG_INCLUDES) $(PIC_FLAGS)
crypto_libargoneum_crypto_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) $(PIC_FLAGS)
crypto_libargoneum_crypto_a_SOURCES = \
  $(crypto_libargoneum_crypto_a_common) \
  $(crypto_libargoneum_crypto_a_algos) \
  $(crypto_libargoneum_crypto_a_sha3)

crypto_libargoneum_crypto_a_common = \
  crypto/aes.h \
  crypto/aes.cpp \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h

crypto_libargoneum_crypto_a_algos = \
  crypto/algos/common.h \
  crypto/algos/gost.c \
  crypto/algos/gost.h \
  crypto/algos/groestl.c \
  crypto/algos/groestl.h \
  crypto/algos/keccak.c \
  crypto/algos/keccak.h \
  crypto/algos/lbk3.c \
  crypto/algos/lbk3.h \
  crypto/algos/luffa.c \
  crypto/algos/luffa.h \
  crypto/algos/lyra2-z.c \
  crypto/algos/lyra2-z.h \
  crypto/algos/lyra2.c \
  crypto/algos/lyra2.h \
  crypto/algos/lyra2re.c \
  crypto/algos/lyra2re.h \
  crypto/algos/lyra2v2.c \
  crypto/algos/lyra2v2.h \
  crypto/algos/lyra2z.c \
  crypto/algos/lyra2z.h \
  crypto/algos/neoscrypt.c \
  crypto/algos/neoscrypt.h \
  crypto/algos/nist5.c \
  crypto/algos/nist5.h \
  crypto/algos/phi.c \
  crypto/algos/phi.h \
  crypto/algos/phi2.c \
  crypto/algos/phi2.h \
  crypto/algos/scrypt.c \
  crypto/algos/scryptn.c \
  crypto/algos/scryptn.h \
  crypto/algos/sha256.c \
  crypto/algos/sha256.h \
  crypto/algos/sha256_y.c \
  crypto/algos/sha256_y.h \
  crypto/algos/sha256t.c \
  crypto/algos/sha256t.h \
  crypto/algos/sib.c \
  crypto/algos/sib.h \
  crypto/algos/skein.c \
  crypto/algos/skein.h \
  crypto/algos/skein2.c \
  crypto/algos/skein2.h \
  crypto/algos/skunk.c \
  crypto/algos/skunk.h \
  crypto/algos/sm3.c \
  crypto/algos/sm3.h \
  crypto/algos/sponge.c \
  crypto/algos/sponge.h \
  crypto/algos/sysendian.h \
  crypto/algos/x11.c \
  crypto/algos/x11.h

crypto_libargoneum_crypto_a_sha3 = \
  crypto/sha3/sph_blake.c \
  crypto/sha3/sph_blake.h \
  crypto/sha3/sph_bmw.c \
  crypto/sha3/sph_bmw.h \
  crypto/sha3/sph_cubehash.c \
  crypto/sha3/sph_cubehash.h \
  crypto/sha3/sph_echo.c \
  crypto/sha3/sph_echo.h \
  crypto/sha3/sph_fugue.c \
  crypto/sha3/sph_fugue.h \
  crypto/sha3/sph_groestl.c \
  crypto/sha3/sph_groestl.h \
  crypto/sha3/sph_hamsi.c \
  crypto/sha3/sph_hamsi.h \
  crypto/sha3/sph_haval.c \
  crypto/sha3/sph_haval.h \
  crypto/sha3/sph_hefty1.c \
  crypto/sha3/sph_hefty1.h \
  crypto/sha3/sph_jh.c \
  crypto/sha3/sph_jh.h \
  crypto/sha3/sph_keccak.c \
  crypto/sha3/sph_keccak.h \
  crypto/sha3/sph_luffa.c \
  crypto/sha3/sph_luffa.h \
  crypto/sha3/sph_ripemd.c \
  crypto/sha3/sph_ripemd.h \
  crypto/sha3/sph_sha2.c \
  crypto/sha3/sph_sha2.h \
  crypto/sha3/sph_sha2big.c \
  crypto/sha3/sph_shabal.c \
  crypto/sha3/sph_shabal.h \
  crypto/sha3/sph_shavite.c \
  crypto/sha3/sph_shavite.h \
  crypto/sha3/sph_simd.c \
  crypto/sha3/sph_simd.h \
  crypto/sha3/sph_skein.c \
  crypto/sha3/sph_skein.h \
  crypto/sha3/sph_tiger.c \
  crypto/sha3/sph_tiger.h \
  crypto/sha3/sph_types.h \
  crypto/sha3/sph_whirlpool.c \
  crypto/sha3/sph_whirlpool.h

EXTRA_DIST = \
  crypto/sha3/aes_helper.c \
  crypto/sha3/hamsi_helper.c \
  crypto/sha3/haval_helper.c \
  crypto/sha3/md_helper.c

# consensus: shared between all executables that validate any consensus rules.
libargoneum_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libargoneum_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libargoneum_consensus_a_SOURCES = \
  amount.h \
  arith_uint256.cpp \
  arith_uint256.h \
  consensus/merkle.cpp \
  consensus/merkle.h \
  consensus/params.h \
  consensus/validation.h \
  hash.cpp \
  hash.h \
  prevector.h \
  primitives/block.cpp \
  primitives/block.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/argoneumconsensus.cpp \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
  tinyformat.h \
  uint256.cpp \
  uint256.h \
  utilstrencodings.cpp \
  utilstrencodings.h \
  version.h

# common: shared between argoneumd, and argoneum-qt and non-server tools
libargoneum_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libargoneum_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libargoneum_common_a_SOURCES = \
  amount.cpp \
  base58.cpp \
  bip39.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  hdchain.cpp \
  key.cpp \
  keystore.cpp \
  netaddress.cpp \
  netbase.cpp \
  protocol.cpp \
  scheduler.cpp \
  script/sign.cpp \
  script/standard.cpp \
  warnings.cpp \
  $(BITCOIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libargoneum_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libargoneum_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libargoneum_util_a_SOURCES = \
  support/lockedpool.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  random.cpp \
  rpc/protocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  threadinterrupt.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(BITCOIN_CORE_H)

if GLIBC_BACK_COMPAT
libargoneum_util_a_SOURCES += compat/glibc_compat.cpp
endif

# cli: shared between argoneum-cli and argoneum-qt
libargoneum_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libargoneum_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libargoneum_cli_a_SOURCES = \
  rpc/client.cpp \
  $(BITCOIN_CORE_H)

nodist_libargoneum_util_a_SOURCES = $(srcdir)/obj/build.h
#

# argoneumd binary #
argoneumd_SOURCES = argoneumd.cpp
argoneumd_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
argoneumd_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
argoneumd_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
argoneumd_SOURCES += argoneumd-res.rc
endif

argoneumd_LDADD = \
  $(LIBBITCOIN_SERVER) \
  $(LIBBITCOIN_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_UTIL) \
  $(LIBBITCOIN_WALLET) \
  $(LIBBITCOIN_ZMQ) \
  $(LIBBITCOIN_CONSENSUS) \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

argoneumd_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS)

# argoneum-cli binary #
argoneum_cli_SOURCES = argoneum-cli.cpp
argoneum_cli_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(EVENT_CFLAGS)
argoneum_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
argoneum_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
argoneum_cli_SOURCES += argoneum-cli-res.rc
endif

argoneum_cli_LDADD = \
  $(LIBBITCOIN_CLI) \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_UTIL) \
  $(LIBBITCOIN_CRYPTO)
argoneum_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
#

# argoneum-tx binary #
argoneum_tx_SOURCES = argoneum-tx.cpp
argoneum_tx_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
argoneum_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
argoneum_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
argoneum_tx_SOURCES += argoneum-tx-res.rc
endif

argoneum_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_COMMON) \
  $(LIBBITCOIN_UTIL) \
  $(LIBBITCOIN_CONSENSUS) \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBSECP256K1)

argoneum_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# argoneumconsensus library #
if BUILD_BITCOIN_LIBS
include_HEADERS = script/argoneumconsensus.h
libargoneumconsensus_la_SOURCES = $(crypto_libargoneum_crypto_a_SOURCES) $(libargoneum_consensus_a_SOURCES)

if GLIBC_BACK_COMPAT
  libargoneumconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libargoneumconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libargoneumconsensus_la_LIBADD = $(LIBSECP256K1)
libargoneumconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_BITCOIN_INTERNAL
libargoneumconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST += $(CTAES_DIST)


config/argoneum-config.h: config/stamp-h1
	@$(MAKE) -C $(top_builddir) $(subdir)/$(@)
config/stamp-h1: $(top_srcdir)/$(subdir)/config/argoneum-config.h.in $(top_builddir)/config.status
	$(AM_V_at)$(MAKE) -C $(top_builddir) $(subdir)/$(@)
$(top_srcdir)/$(subdir)/config/argoneum-config.h.in:  $(am__configure_deps)
	$(AM_V_at)$(MAKE) -C $(top_srcdir) $(subdir)/config/argoneum-config.h.in

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(AM_CXXFLAGS) $(PIE_FLAGS) $(CXXFLAGS) -c -o $@ $<

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(<D) $<

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
