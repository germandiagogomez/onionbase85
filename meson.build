project('onionbase85',
        'cpp',
        default_options : ['cpp_std=c++2a'])

subdir('src')
if get_option('build-tests')
  subdir('tests')
endif

if get_option('build-benchmarks')
  subdir('benchmarks')
endif
