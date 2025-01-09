// Copyright (c) 2023 Itecoin Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "logprintf.h"

#include <clang-tidy/ClangTidyModule.h>
#include <clang-tidy/ClangTidyModuleRegistry.h>

class ItecoinModule final : public clang::tidy::ClangTidyModule
{
public:
    void addCheckFactories(clang::tidy::ClangTidyCheckFactories& CheckFactories) override
    {
        CheckFactories.registerCheck<Itecoin::LogPrintfCheck>("Itecoin-unterminated-logprintf");
    }
};

static clang::tidy::ClangTidyModuleRegistry::Add<ItecoinModule>
    X("Itecoin-module", "Adds Itecoin checks.");

volatile int ItecoinModuleAnchorSource = 0;
