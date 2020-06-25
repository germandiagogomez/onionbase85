#include "onion/Base85Decoder.hpp"
#include <cassert>
#include <algorithm>
#include <iostream>
#include <cmath>

namespace {
    static auto readBytes(std::istream & s,
                          gsl::span<std::byte> buffer,
                          std::int64_t numBytes) {
        assert(static_cast<std::int64_t>(buffer.size()) >= numBytes);
        s.read(reinterpret_cast<char *>(&buffer[0]),
               numBytes);
        auto readBytes = s.gcount();
        return readBytes;
    }

    auto removeWhitespaceBytes(gsl::span<std::byte> input) {
        using namespace std;
        return remove_if(input.begin(), input.end(),
                         [](std::byte c) { return isspace(static_cast<int>(c)); });
    }
}


namespace onion {

    std::array<char, 4> base85ToAscii(std::uint32_t number) {
        std::array<char, 4> result{};
        std::copy(reinterpret_cast<char *>(&number), reinterpret_cast<char *>(&number) + 4,
                  result.rbegin());
        return result;
    }


    std::vector<char> Base85Decoder::decodeAll() {
        using namespace gsl;
        using namespace std;
        std::array<std::byte, 5> inputBlock;
        std::vector<char> result;
        while (1) {
            auto numBytesRead = readBytes(*stream_.stream,
                                          inputBlock, 5);
            if (numBytesRead == 0)
                break;
            assert(numBytesRead >= 1 && numBytesRead <= 5);
            auto inputSubBlock = gsl::span(inputBlock.begin(), inputBlock.end());
            do {
                auto nextBufReadPos = removeWhitespaceBytes(inputSubBlock);
                if (nextBufReadPos == inputSubBlock.end())
                    break;
                auto numNonWhitespaces = std::distance(inputSubBlock.begin(), nextBufReadPos);
                numBytesRead = numNonWhitespaces;
                inputSubBlock = inputSubBlock.subspan(numNonWhitespaces);
                numBytesRead += readBytes(*stream_.stream, inputSubBlock, inputSubBlock.size());
            } while (1);
            // Fill with 'u' the bytes that have not been read
            std::fill(inputBlock.begin() + numBytesRead,
                      inputBlock.end(),
                      117_b);
            auto asciiMinus33Block = convertToAsciiMinus33(inputBlock);
            auto asciiText = base85ToAscii(blockToBase85(asciiMinus33Block));
            std::copy(asciiText.begin(), std::next(asciiText.begin(), 4 - (5 - numBytesRead)),
                      std::back_inserter(result));
        }
        return result;
    }

    std::array<std::byte, 5> Base85Decoder::convertToAsciiMinus33(gsl::span<std::byte, 5> bytes) {
        std::array<std::byte, 5> result{};
        std::size_t i = 0;
        for (auto b : bytes) {
            result[i] = static_cast<std::byte>(static_cast<unsigned int>(b) - 33u);
            ++i;
        }
        return result;
    }
}
