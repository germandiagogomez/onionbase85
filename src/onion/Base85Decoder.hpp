#ifndef _ONION_BASE85DECODER_HPP_
#define _ONION_BASE85DECODER_HPP_

#include <iosfwd>
#include <memory>
#include <cstddef>
#include <vector>
#include <gsl/span>
#include <cstdint>
#include <array>
#include <cmath>

namespace onion {

    struct Base85Stream {
        std::unique_ptr<std::istream> stream;
    };

    class Base85Decoder {
        public:
            Base85Decoder() = default;
            explicit Base85Decoder(Base85Stream stream) : stream_(std::move(stream)) {}
            std::vector<char> decodeAll();
        private:
            std::array<std::byte, 5> convertToAsciiMinus33(gsl::span<std::byte, 5> bytes);
            Base85Stream stream_;
    };

    std::array<char, 4> base85ToAscii(std::uint32_t number);

    constexpr std::byte operator "" _b(unsigned long long value) {
        return static_cast<std::byte>(value);
    }

    constexpr std::uint32_t blockToBase85(gsl::span<std::byte, 5> base85Number) {
        int weight = 4;
        std::uint32_t result = 0;
        for (auto byte : base85Number) {
            result += static_cast<std::uint32_t>(byte) * std::pow(85, weight);
            --weight;
        }
        return result;
    }

} // namespace onion

#endif 
