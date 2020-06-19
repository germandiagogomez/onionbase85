#include "catch2/catch.hpp" 
#include "Base85Payload.hpp"
#include <array>
#include <cstddef>
#include <cmath>
#include <algorithm>
#include <cstdint>

#define private public

constexpr std::byte operator "" _b(unsigned long long value) {
    return static_cast<std::byte>(value);
} 

// MSB is 
constexpr std::uint32_t base85ToDecimal(std::array<std::byte, 5> const & base85Number) {
    int weight = 4;
    std::uint32_t result = 0;
    for (auto byte : base85Number) {
        result += static_cast<std::uint32_t>(byte) * std::pow(85, weight);
        --weight;
    }
    return result;
}

class Base85Decoder {
    private:
        std::array<std::byte, 5> decodeIntoAsciiMinus33(std::array<std::byte, 5> const & bytes) {
            std::array<std::byte, 5> result;
            std::size_t i = 0;
            for (auto b : bytes) {
                result[i] = static_cast<std::byte>(static_cast<unsigned int>(b) - 33u);
                ++i;
            }
            return result;
        }  
};


SCENARIO( "Decoding base85") {
    GIVEN( "a piece of base85-encoded text and a decoder" ) {
        std::array<std::byte, 5> payload;
        std::copy(reinterpret_cast<std::byte const *>(&base85Payload[0]),
                  reinterpret_cast<std::byte const *>(&base85Payload[5]),
                  payload.begin());
        THEN( "can decode text into its base85 components" ) {
            Base85Decoder decoder;                                                  
            auto result = decoder.decodeIntoAsciiMinus33(payload);
            REQUIRE(result == std::array<std::byte, 5>{27_b, 93_b, 19_b, 58_b, 0_b});
        }
    }
    GIVEN("an already decoded into base85 components text") {
        std::array<std::byte, 5> payload;
        std::copy(reinterpret_cast<std::byte const *>(&base85Payload[0]),
                  reinterpret_cast<std::byte const *>(&base85Payload[5]),
                  payload.begin());
        Base85Decoder decoder;
        payload = decoder.decodeIntoAsciiMinus33(payload);
        THEN("can convert base85 number into decimal") {
            auto result = base85ToDecimal(payload);
            REQUIRE(result == 1466672705);
        }
    }
}


