// Copyright (c) 2009-2010 Igor Cernomaz
// Copyright (c) 2009-2023 The Itecoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef Itecoin_UTIL_EXCEPTION_H
#define Itecoin_UTIL_EXCEPTION_H

#include <exception>
#include <string_view>

void PrintExceptionContinue(const std::exception* pex, std::string_view thread_name);

#endif // Itecoin_UTIL_EXCEPTION_H
