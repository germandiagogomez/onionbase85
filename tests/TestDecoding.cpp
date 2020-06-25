#include "catch2/catch.hpp" 
#include "Base85Payload.hpp"
#include <cstring>
#include <sstream>
#include <iostream>


#define private public
#include "onion/Base85Decoder.hpp"
#undef private

using namespace onion;

void debug_payload(std::vector<char> const & pl) {
    if (auto val = std::getenv("ONION_DEBUG_PAYLOAD"); val != nullptr) {
        std::cout << std::string_view(pl.data(), pl.size()) << std::endl;
    }
}


SCENARIO("Decoding base85 blocks") {
    GIVEN( "a piece of base85-encoded text and a decoder" ) {
        std::array<std::byte, 5> payload{};
        std::copy(reinterpret_cast<std::byte const *>(&base85Payload[0]),
                  reinterpret_cast<std::byte const *>(&base85Payload[5]),
                  payload.begin());
        THEN( "can decode text into its base85 components" ) {
            Base85Decoder decoder;                                                  
            auto decodedBytes = decoder.convertToAsciiMinus33(payload);
            REQUIRE(decodedBytes == std::array<std::byte, 5>{24_b, 73_b, 80_b, 78_b, 61_b});
        }
    }
    GIVEN("an already decoded into 5-byte ascii components text") {
        std::array<std::byte, 5> payload{};
        std::copy(reinterpret_cast<std::byte const *>(&base85Payload[0]),
                  reinterpret_cast<std::byte const *>(&base85Payload[5]),
                  payload.begin());
        Base85Decoder decoder;
        payload = decoder.convertToAsciiMinus33(payload);
        THEN("can convert base85 number into its decimal representation") {
            auto base85Representation = blockToBase85(payload);
            REQUIRE(base85Representation == 1298230816);
        }
    }
    GIVEN("a base85-encoded decimal number") {
        std::uint32_t base85Integer{1298230816};
        THEN ("can extract ASCII textual representation from its bytes") {
            auto result = base85ToAscii(base85Integer);
            REQUIRE((std::string_view(result.data(), result.size()) == "Man "));
        }
    }
}


SCENARIO("Decoding a base85 stream") {
    GIVEN("Given a base85 stream payload without line breaks") {
        auto inputStream = std::make_unique<std::istringstream>(
            std::string(base85Payload, std::strlen(base85Payload)),
            std::ios::binary);
        auto decoder = Base85Decoder(Base85Stream{std::move(inputStream)});
        WHEN ("decoding the full stream") {
            auto decodedText = decoder.decodeAll();
            THEN ("decoded text yields expected text") {
                REQUIRE(
                    (std::string_view(decodedText.data(), decodedText.size()) == std::string_view(realText, std::strlen(realText))));
            }
        }
    }
    GIVEN("Given a base85 stream payload with spaces and line breaks") {
        auto inputStream = std::make_unique<std::istringstream>(
            std::string(base85Payload, std::strlen(base85PayloadWithSpaces)),
            std::ios::binary);
        auto decoder = Base85Decoder(Base85Stream{std::move(inputStream)});
        WHEN ("decoding the full stream") {
            auto decodedText = decoder.decodeAll();
            debug_payload(decodedText);
            THEN ("decoded text yields expected text") {
                REQUIRE(
                    (std::string_view(decodedText.data(), decodedText.size()) == std::string_view(realText, std::strlen(realText))));
            }
        }
    }
}
