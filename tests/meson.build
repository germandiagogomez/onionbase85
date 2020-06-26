catch2_dep = dependency('catch2', fallback : ['catch2', 'catch2_dep'])

test_decoding = executable('testDecoding', ['TestDecoding.cpp', 'TestMain.cpp'],
                           dependencies :
                           [catch2_dep, onionbase85_dep])

test('Base85 decoding tests', test_decoding)
