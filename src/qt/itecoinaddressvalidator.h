// Copyright (c) 2011-2020 The Itecoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef Itecoin_QT_ItecoinADDRESSVALIDATOR_H
#define Itecoin_QT_ItecoinADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class ItecoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit ItecoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** Itecoin address widget validator, checks for a valid Itecoin address.
 */
class ItecoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit ItecoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // Itecoin_QT_ItecoinADDRESSVALIDATOR_H
