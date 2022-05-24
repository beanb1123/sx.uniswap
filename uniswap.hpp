#pragma once

#include <sx.safemath/safemath.hpp>

namespace uniswap {

    static uint64_t get_amount_out( const uint64_t amount_in, const uint64_t reserve_in, const uint64_t reserve_out, const uint16_t fee = 30 )
    {
        // checks
        eosio::check(amount_in > 0, "SX.Uniswap: INSUFFICIENT_INPUT_AMOUNT");
        eosio::check(reserve_in > 0 && reserve_out > 0, "SX.Uniswap: INSUFFICIENT_LIQUIDITY");

        // calculations
        const uint128_t amount_in_with_fee = static_cast<uint128_t>(amount_in) * (10000 - fee);
        const uint128_t numerator = amount_in_with_fee * reserve_out;
        const uint128_t denominator = (static_cast<uint128_t>(reserve_in) * 10000) + amount_in_with_fee;
        const uint64_t amount_out = numerator / denominator;

        return amount_out;
    }

    static uint64_t get_amount_in( const uint64_t amount_out, const uint64_t reserve_in, const uint64_t reserve_out, const uint16_t fee = 30 )
    {
        // checks
        eosio::check(amount_out > 0, "SX.Uniswap: INSUFFICIENT_OUTPUT_AMOUNT");
        eosio::check(reserve_in > 0 && reserve_out > 0, "SX.Uniswap: INSUFFICIENT_LIQUIDITY");

        const uint128_t numerator = static_cast<uint128_t>(reserve_in) * amount_out * 10000;
        const uint128_t denominator = static_cast<uint128_t>(reserve_out - amount_out) * (10000 - fee);
        const uint64_t amount_in = (numerator / denominator) + 1;

        return amount_in;
    }

    static uint64_t quote( const uint64_t amount_a, const uint64_t reserve_a, const uint64_t reserve_b )
    {
        eosio::check(amount_a > 0, "SX.Uniswap: INSUFFICIENT_AMOUNT");
        eosio::check(reserve_a > 0 && reserve_b > 0, "SX.Uniswap: INSUFFICIENT_LIQUIDITY");
        const uint64_t amount_b = safemath::mul(amount_a, reserve_b) / reserve_a;
        return amount_b;
    }
}
