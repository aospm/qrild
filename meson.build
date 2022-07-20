project('qrild', 'c')

cc = meson.get_compiler('c')

libqril_proj = subproject('libqril')
libqril_dep = libqril_proj.get_variable('libqril_dep')

deps = [ # ew
  cc.find_library('libqrtr', dirs: ['/usr/local/lib', '/usr/local/include', '/usr/lib', '/usr/include']),
  libqril_dep,
]

############################################
## qrild

qrild_src = [
  'qrild/qrild.c',
]

executable('qrild', qrild_src,
  dependencies: deps,
  install: true,
  c_args: [],
)

############################################
## tlv_dump

tlv_dump_src = [
  'tools/tlv_dump.c',
]

executable('tlv_dump', tlv_dump_src,
  dependencies: deps,
  install: true,
  c_args: [],
)
