project('qrild', 'c')

cc = meson.get_compiler('c')

deps = [ # ew
  cc.find_library('libqrtr', dirs: ['/usr/local/lib', '/usr/local/include', '/usr/lib', '/usr/include']),
  dependency('libnl-3.0'),
]

inc = [
  include_directories('src'),
  include_directories('include'),
]

subdir('src')

