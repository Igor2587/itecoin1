// Copyright (c) 2016-2021 The Itecoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef Itecoin_WALLET_RPC_WALLET_H
#define Itecoin_WALLET_RPC_WALLET_H

#include <span.h>

class CRPCCommand;

namespace wallet {
Span<const CRPCCommand> GetWalletRPCCommands();
} // namespace wallet

#endif // Itecoin_WALLET_RPC_WALLET_H
