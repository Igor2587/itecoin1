// Copyright (c) 2009-2010 Igor Cernomaz
// Copyright (c) 2009-2022 The Itecoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

/**
 * Money parsing/formatting utilities.
 */
#ifndef Itecoin_UTIL_MONEYSTR_H
#define Itecoin_UTIL_MONEYSTR_H

#include <consensus/amount.h>

#include <optional>
#include <string>

/* Do not use these functions to represent or parse monetary amounts to or from
 * JSON but use AmountFromValue and ValueFromAmount for that.
 */
std::string FormatMoney(const CAmount n);
/** Parse an amount denoted in full coins. E.g. "0.0034" supplied on the command line. **/
std::optional<CAmount> ParseMoney(const std::string& str);

#endif // Itecoin_UTIL_MONEYSTR_H
