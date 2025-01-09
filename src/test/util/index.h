// Copyright (c) 2020-2022 The Itecoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef Itecoin_TEST_UTIL_INDEX_H
#define Itecoin_TEST_UTIL_INDEX_H

class BaseIndex;

/** Block until the index is synced to the current chain */
void IndexWaitSynced(const BaseIndex& index);

#endif // Itecoin_TEST_UTIL_INDEX_H
