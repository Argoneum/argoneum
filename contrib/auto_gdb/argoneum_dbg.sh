#!/bin/bash
# use testnet settings,  if you need mainnet,  use ~/.argoneumcore/argoneumd.pid file instead
argoneum_pid=$(<~/.argoneumcore/testnet3/argoneumd.pid)
sudo gdb -batch -ex "source debug.gdb" argoneumd ${argoneum_pid}
