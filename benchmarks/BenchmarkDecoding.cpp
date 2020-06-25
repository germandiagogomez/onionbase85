#include "catch2/catch.hpp" 
#include "Base85Payload.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include "BenchmarkConfig.hpp"


#define private public
#include "onion/Base85Decoder.hpp"
#undef private

using namespace onion;
namespace cfg = onion::benchmarkconfig;

TEST_CASE("Base85Decoder baseline. Reading data from file and decoding.") {
    auto inputStream = std::make_unique<std::ifstream>(
        std::string(cfg::MESON_BENCHMARK_DIR.begin(),
                    cfg::MESON_BENCHMARK_DIR.end())
        + "testData/TomsDataOnionPayload.base85");
    
    if (!inputStream->is_open()) {
        throw std::runtime_error("File not found where expected");
    }

    auto decoder = Base85Decoder(Base85Stream{std::move(inputStream)});
    auto decodedText = decoder.decodeAll();
    std::cout << decodedText.size() << std::endl;
    std::cout << std::string_view(decodedText.data(), decodedText.size()) << std::endl;
}
