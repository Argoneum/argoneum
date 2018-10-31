#!/bin/bash
#
# This script is based on the work of zoldur, https://github.com/zoldur/
# Used according to GNU GPL 3.0 terms and conditions.
#
# If you find it useful, please donate to the original author (zoldur):
#   BTC: 3MNhbUq5smwMzxjU2UmTfeafPD7ag8kq76
#   ETH: 0x26B9dDa0616FE0759273D651e77Fe7dd7751E01E
#   LTC: LeZmPXHuQEhkd8iZY7a2zVAwF7DCWir2FF
#

RUNAS="root"

COIN_NAME="Argoneum Core"
coin_name="argoneum"
COIN_DATA="argoneum"
COIN_PORT=9898

CONFIGFOLDER="$(eval echo "~$RUNAS")/.${COIN_DATA}"
CONFIG_FILE="${coin_name}.conf"
COIN_DAEMON="${coin_name}d"
COIN_SERVICE="${coin_name}"
COIN_CLI="${coin_name}-cli"

TMP_FOLDER=$(mktemp -d)
COIN_PATH='/usr/local/bin/'
KERN_ARCH=$(getconf LONG_BIT)
COIN_TGZ="https://github.com/argoneum/argoneum/releases/download/v1.0.0.0/argoneum-1.0.0-linux${KERN_ARCH}.tar.gz"
COIN_ZIP=$(echo $COIN_TGZ | awk -F'/' '{print $NF}')

NODEIP=$(curl -s4 icanhazip.com)

UFWD="/etc/ufw/applications.d"

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'


function checks() {
  if [[ $(lsb_release -d) != *16.04* ]] && [[ $(lsb_release -d) != *17.10* ]] && [[ $(lsb_release -d) != *18.04* ]]; then
    echo -e "${RED}You are not running Ubuntu 16.04, 17.10 or 18.04. Installation is cancelled.${NC}"
    exit 1
  fi

  if [[ $EUID -ne 0 ]]; then
     echo -e "${RED}$0 must be run as root.${NC}"
     exit 1
  fi

  if [ -n "$(pidof "$COIN_DAEMON")" ] || [ -e "$COIN_DAEMON" ]; then
    echo -e "${RED}$COIN_NAME is already installed.${NC}"
    exit 1
  fi
}

function asksure() {
  echo -e "You are going to install ${GREEN}$COIN_NAME${NC} masternode."
  echo -e "This script will install the complete build environment, so you may compile/install any other coins later."
  echo -e ""
  echo -e "Type ${GREEN}Y${NC} to start installation or ${RED}N${NC} to abort:"
  local answer
  while read -r -n 1 -s answer; do
    if [[ $answer = [YyNn] ]]; then
      [[ $answer = [Yy] ]] && retval=0
      [[ $answer = [Nn] ]] && retval=1
      break
    fi
  done
  echo
  return $retval
}

function prepare_system() {
  echo -e "${GREEN}This process might take up to 15 minutes, please be patient.${NC}"

  echo -e "${GREEN}Updating system packages...${NC}"
  apt-get update
  DEBIAN_FRONTEND=noninteractive apt-get update
  DEBIAN_FRONTEND=noninteractive apt-get -o Dpkg::Options::="--force-confdef" -o Dpkg::Options::="--force-confold" -y -qq upgrade
  apt install -y software-properties-common
  echo -e "${GREEN}Adding bitcoin PPA repository...${NC}"
  apt-add-repository -y ppa:bitcoin/bitcoin
  echo -e "${GREEN}Installing required packages, it may take some time to finish.${NC}"
  apt-get update
  apt-get install -y -o Dpkg::Options::="--force-confdef" -o Dpkg::Options::="--force-confold" \
    sudo ufw git wget curl make automake autoconf build-essential libtool pkg-config libssl-dev \
    libboost-dev libboost-chrono-dev libboost-filesystem-dev libboost-program-options-dev \
    libboost-system-dev libboost-test-dev libboost-thread-dev libdb4.8-dev bsdmainutils \
    libdb4.8++-dev libminiupnpc-dev libgmp3-dev libevent-dev libdb5.3++ unzip libzmq5
  if [ "$?" -gt "0" ]; then
    echo -e "${RED}Not all required packages were installed properly. Try to install them manually by running the following commands:${NC}\n"
    echo "apt-get update"
    echo "apt -y install software-properties-common"
    echo "apt-add-repository -y ppa:bitcoin/bitcoin"
    echo "apt-get update"
    echo "apt-get install sudo ufw git wget curl make automake autoconf build-essential libtool pkg-config libssl-dev \
      libboost-dev libboost-chrono-dev libboost-filesystem-dev libboost-program-options-dev \
      libboost-system-dev libboost-test-dev libboost-thread-dev libdb4.8-dev bsdmainutils \
      libdb4.8++-dev libminiupnpc-dev libgmp3-dev libevent-dev libdb5.3++ unzip libzmq5"
    exit 1
  fi
}

function download_node() {
  echo -e "${GREEN}Fetching $COIN_NAME binary distribution...${NC}"
  cd $TMP_FOLDER
  wget $COIN_TGZ
  if [ "$?" -gt "0" ];
   then
    echo -e "${RED}Failed to download $COIN_NAME. Please investigate.${NC}"
    exit 1
  fi
  tar xvzf $COIN_ZIP --strip-components=2
  cp $COIN_DAEMON $COIN_CLI $COIN_PATH
  cd - &>/dev/null
  rm -rf $TMP_FOLDER
}

function get_ip() {
  declare -a NODE_IPS
  for ips in $(netstat -i | awk '!/Kernel|Iface|lo/ {print $1," "}'); do
    NODE_IPS+=($(curl --interface $ips --connect-timeout 2 -s4 icanhazip.com))
  done

  if [ ${#NODE_IPS[@]} -gt 1 ]
    then
      echo -e "${GREEN}More than one IP. Please type 0 to use the first IP, 1 for the second and so on...${NC}"
      INDEX=0
      for ip in "${NODE_IPS[@]}"; do
        echo ${INDEX} $ip
        let INDEX=${INDEX}+1
      done
      read -e choose_ip
      NODEIP=${NODE_IPS[$choose_ip]}
  else
    NODEIP=${NODE_IPS[0]}
  fi
}

function create_config() {
  mkdir -p $CONFIGFOLDER
  RPCUSER=$(tr -cd '[:alnum:]' < /dev/urandom | fold -w10 | head -n1)
  RPCPASSWORD=$(tr -cd '[:alnum:]' < /dev/urandom | fold -w22 | head -n1)
  cat <<EOF >$CONFIGFOLDER/$CONFIG_FILE
rpcuser=$RPCUSER
rpcpassword=$RPCPASSWORD

#bind=$NODEIP
port=$COIN_PORT

listen=1
server=1
daemon=0

EOF
}

function create_key() {
  echo -e "Enter your ${RED}$COIN_NAME Masternode Private Key${NC}. Leave it blank to generate a new ${RED}Masternode Private Key${NC} for you:"
  read -e COINKEY
  if [[ -z "$COINKEY" ]]; then
    $COIN_PATH$COIN_DAEMON -daemon
    sleep 30
    if [ -z "$(ps axo cmd:100 | grep $COIN_DAEMON)" ]; then
      echo -e "${RED}$COIN_NAME server could not start. Check /var/log/syslog for errors.{$NC}"
      exit 1
    fi
    COINKEY=$($COIN_PATH$COIN_CLI masternode genkey)
    if [ "$?" -gt "0" ]; then
      echo -e "${RED}Wallet not fully loaded. Let us wait and try again to generate the Private Key${NC}"
      sleep 30
      COINKEY=$($COIN_PATH$COIN_CLI masternode genkey)
    fi
    $COIN_PATH$COIN_CLI stop
  fi
}

function update_config() {
  cat <<EOF >>$CONFIGFOLDER/$CONFIG_FILE
masternode=1
masternodeprivkey=$COINKEY
externalip=$NODEIP:$COIN_PORT
EOF
}

function enable_firewall() {
  echo -e "Installing and setting up firewall to allow ingress on port ${GREEN}$COIN_PORT${NC}"
  ufw allow $COIN_PORT/tcp comment "$COIN_NAME P2P port"
  ufw allow ssh comment "SSH"
  ufw limit ssh/tcp
  ufw default allow outgoing
  echo "y" | ufw enable
}

function enable_firewall_app() {
  echo -e "Installing and setting up ${GREEN}OpenSSH${NC} and ${GREEN}${COIN_NAME}${NC} firewall applications"

  if [ ! -f "$UFWD/openssh-server" ]; then
    cat <<EOF >$UFWD/openssh-server
[OpenSSH]
title=Secure shell server, an rshd replacement
description=OpenSSH is a free implementation of the Secure Shell protocol.
ports=22/tcp
EOF
  fi

  cat <<EOF >$UFWD/$coin_name
[$COIN_NAME]
title=$COIN_NAME daemon
description=$COIN_NAME daemon P2P port.
ports=$COIN_PORT/tcp
EOF

  ufw allow "OpenSSH"
  ufw allow "$COIN_NAME"
  ufw default allow outgoing
  echo "y" | ufw enable
}

function configure_systemd() {
  cat <<EOF >/etc/systemd/system/$COIN_SERVICE.service
[Unit]
Description=$COIN_NAME service
After=network.target

[Service]
User=$RUNAS
Group=$RUNAS

Type=forking
#PIDFile=$CONFIGFOLDER/$COIN_NAME.pid

ExecStart=$COIN_PATH$COIN_DAEMON -datadir=$CONFIGFOLDER -conf=$CONFIGFOLDER/$CONFIG_FILE -daemon
ExecStop=-$COIN_PATH$COIN_CLI -datadir=$CONFIGFOLDER -conf=$CONFIGFOLDER/$CONFIG_FILE stop

Restart=always
PrivateTmp=true
TimeoutStopSec=60s
TimeoutStartSec=10s
StartLimitInterval=120s
StartLimitBurst=5

[Install]
WantedBy=multi-user.target
EOF

  systemctl daemon-reload
  sleep 3
  systemctl start $COIN_SERVICE.service
  systemctl enable $COIN_SERVICE.service

  if [[ -z "$(ps axo cmd:100 | egrep $COIN_DAEMON)" ]]; then
    echo -e "${RED}$COIN_NAME is not running${NC}, please investigate. You should start by running the following commands as $RUNAS:"
    echo -e "${GREEN}systemctl start $COIN_SERVICE.service"
    echo -e "systemctl status $COIN_SERVICE.service"
    echo -e "less /var/log/syslog${NC}"
    exit 1
  fi
}

function important_information() {
  echo
  echo
  echo -e "${GREEN}================================================================================================================================${NC}"
  echo -e "$COIN_NAME masternode is up and running listening on ${RED}$NODEIP:$COIN_PORT${NC}."
  echo -e "Configuration file is: ${RED}$CONFIGFOLDER/$CONFIG_FILE${NC}"
  echo -e "Start:  ${RED}systemctl start  $COIN_SERVICE.service${NC}"
  echo -e "Stop:   ${RED}systemctl stop   $COIN_SERVICE.service${NC}"
  echo -e "Status: ${RED}systemctl status $COIN_SERVICE.service${NC}"
  echo -e "Masternode status: ${RED}$COIN_CLI masternode status${NC}"
  echo -e "MASTERNODE PRIVATEKEY is: ${RED}$COINKEY${NC}"
  if [[ -n $SENTINEL_REPO ]]; then
    echo -e "${RED}Sentinel${NC} is installed in ${RED}$CONFIGFOLDER/sentinel${NC}"
    echo -e "Sentinel logs is: ${RED}$CONFIGFOLDER/sentinel.log${NC}"
  fi
  echo -e "${GREEN}================================================================================================================================${NC}"
  echo -e "Send exactly 10000 coins to an own address using your cold wallet."
  echo -e "After at least 1 confirmation enter the following command in your wallet debug console: ${RED}masternode outputs${NC}"
  echo -e "You should have a masternode collateral transaction hash and index (usually 0 or 1)."
  echo -e "Edit ${RED}masternode.conf${NC} file in your cold wallet data directory and add the following line:"
  echo -e "${GREEN}mn1 $NODEIP:$COIN_PORT $COINKEY your-tx-hash your-tx-index${NC}"
  echo -e "(on Windows you may use 'Tools -> Open Masternode Configurtion File' menu item to edit it)"
  echo -e "Restart your wallet, wait for at least 15 confirmations of collateral tx and start your masternode."
  echo -e "${GREEN}================================================================================================================================${NC}"
  echo -e "This script is based on the work of zoldur, ${RED}https://github.com/zoldur/${NC}"
  echo -e "Used according to GNU GPL 3.0 terms and conditions."
  echo
  echo -e "If you find it useful, please donate to the original author (${RED}zoldur${NC}):"
  echo -e "  BTC: 3MNhbUq5smwMzxjU2UmTfeafPD7ag8kq76"
  echo -e "  ETH: 0x26B9dDa0616FE0759273D651e77Fe7dd7751E01E"
  echo -e "  LTC: LeZmPXHuQEhkd8iZY7a2zVAwF7DCWir2FF"
  echo -e "${GREEN}================================================================================================================================${NC}"
}

##### Entry point #####
clear
checks
if asksure; then
  prepare_system
  download_node
  get_ip
  create_config
  create_key
  update_config
  #enable_firewall
  enable_firewall_app
  configure_systemd
  important_information
fi
