project('qrild', 'c')

cc = meson.get_compiler('c')

deps = [ # ew
  cc.find_library('libqrtr', dirs: ['/usr/local/lib', '/usr/local/include', '/usr/lib', '/usr/include']),
]

inc = [
  include_directories('src'),
  include_directories('include'),
]

subdir('src')

