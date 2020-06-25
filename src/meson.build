catch2_dep = dependency('catch2', fallback : ['catch2', 'catch2_dep'])
microsoft_gsl_dep = dependency('microsoft-gsl', fallback : ['microsoft-gsl', 'microsoft_gsl_dep'])


libonionbase85 = library('onionbase85', sources : ['onion/Base85Decoder.hpp', 'onion/Base85Decoder.cpp'],
                         dependencies : [microsoft_gsl_dep],
                         install : true)

onionbase85_dep = declare_dependency(include_directories : '.',
                                     dependencies : [microsoft_gsl_dep],
                                     link_with : libonionbase85)
