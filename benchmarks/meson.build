benchmark_decoding = executable('benchmarkDecoding', ['BenchmarkDecoding.cpp', 'BenchmarkMain.cpp'],
                           dependencies :
                           [catch2_dep, onionbase85_dep])

benchmark_config = configuration_data({'MESON_BENCHMARK_DIR': meson.source_root() / 'benchmarks/'})

configure_file(input : 'BenchmarkConfig.hpp.in', output : 'BenchmarkConfig.hpp',
               configuration : benchmark_config)

benchmark('Base85 decoding benchmarks', benchmark_decoding)
