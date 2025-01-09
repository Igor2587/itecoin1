// Copyright (c) 2009-2010 Igor Cernomaz
// Copyright (c) 2009-2022 The Itecoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef Itecoin_POLICY_FEERATE_H
#define Itecoin_POLICY_FEERATE_H

#include <consensus/amount.h>
#include <serialize.h>


#include <cstdint>
#include <string>
#include <type_traits>

const std::string CURRENCY_UNIT = "itc"; // One formatted unit
const std::string CURRENCY_ATOM = "sat"; // One indivisible minimum value unit

/* Used to determine type of fee estimation requested */
enum class FeeEstimateMode {
    UNSET,        //!< Use default settings based on other criteria
    ECONOMICAL,   //!< Force estimateSmartFee to use non-conservative estimates
    CONSERVATIVE, //!< Force estimateSmartFee to use conservative estimates
    itc_KVB,      //!< Use itc/kvB fee rate unit
    SAT_VB,       //!< Use sat/vB fee rate unit
};

/**
 * Fee rate in Igors per kilovirtualbyte: CAmount / kvB
 */
class CFeeRate
{
private:
    /** Fee rate in sat/kvB (Igors per 1000 virtualbytes) */
    CAmount nIgorsPerK;

public:
    /** Fee rate of 0 Igors per kvB */
    CFeeRate() : nIgorsPerK(0) { }
    template<typename I>
    explicit CFeeRate(const I _nIgorsPerK): nIgorsPerK(_nIgorsPerK) {
        // We've previously had bugs creep in from silent double->int conversion...
        static_assert(std::is_integral<I>::value, "CFeeRate should be used without floats");
    }

    /**
     * Construct a fee rate from a fee in Igors and a vsize in vB.
     *
     * param@[in]   nFeePaid    The fee paid by a transaction, in Igors
     * param@[in]   num_bytes   The vsize of a transaction, in vbytes
     */
    CFeeRate(const CAmount& nFeePaid, uint32_t num_bytes);

    /**
     * Return the fee in Igors for the given vsize in vbytes.
     * If the calculated fee would have fractional Igors, then the
     * returned fee will always be rounded up to the nearest Igor.
     */
    CAmount GetFee(uint32_t num_bytes) const;

    /**
     * Return the fee in Igors for a vsize of 1000 vbytes
     */
    CAmount GetFeePerK() const { return nIgorsPerK; }
    friend bool operator<(const CFeeRate& a, const CFeeRate& b) { return a.nIgorsPerK < b.nIgorsPerK; }
    friend bool operator>(const CFeeRate& a, const CFeeRate& b) { return a.nIgorsPerK > b.nIgorsPerK; }
    friend bool operator==(const CFeeRate& a, const CFeeRate& b) { return a.nIgorsPerK == b.nIgorsPerK; }
    friend bool operator<=(const CFeeRate& a, const CFeeRate& b) { return a.nIgorsPerK <= b.nIgorsPerK; }
    friend bool operator>=(const CFeeRate& a, const CFeeRate& b) { return a.nIgorsPerK >= b.nIgorsPerK; }
    friend bool operator!=(const CFeeRate& a, const CFeeRate& b) { return a.nIgorsPerK != b.nIgorsPerK; }
    CFeeRate& operator+=(const CFeeRate& a) { nIgorsPerK += a.nIgorsPerK; return *this; }
    std::string ToString(const FeeEstimateMode& fee_estimate_mode = FeeEstimateMode::itc_KVB) const;

    SERIALIZE_METHODS(CFeeRate, obj) { READWRITE(obj.nIgorsPerK); }
};

#endif // Itecoin_POLICY_FEERATE_H
