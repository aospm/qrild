project('libqril', 'cpp')
cc = meson.get_compiler('c')
fs = import('fs')

qmic = find_program('qmic')

qmi_srcs = [
  'qmi/qril_dms.qmi',
  'qmi/qril_dpm.qmi',
  'qmi/qril_nas.qmi',
  'qmi/qril_uim.qmi',
  'qmi/qril_wda.qmi',
  'qmi/qril_wds.qmi',
]

qmi_generated = []

foreach qmi : qmi_srcs
  basename = qmi.split('_')[1].split('.')[0]
  qmi_generated += custom_target('qmi_@0@.[ch]'.format(basename),
    output: ['qmi_@0@.h'.format(basename),
             'qmi_@0@.c'.format(basename)],
    input: qmi,
    command: [qmic, '-f', '@INPUT@', '-o', '@OUTDIR@'],
    install: true,
    install_dir: '@OUTDIR@',
  )
endforeach

qmi_dep = declare_dependency(sources: qmi_generated)

libqril_deps = [ # ew
  cc.find_library('libqrtr', dirs: ['/usr/local/lib', '/usr/local/include', '/usr/lib', '/usr/include']),
  qmi_dep,
]

libqril_include = [
  include_directories('.'),
  include_directories('include'),
]

libqril_headers = [
  'qrild_link.h',
  'qrild_msg.h',
  'qrild_qmi.h',
  'qrild.h',
  'util.h',
]

libqril_src = [
  'qrild_msg.c',
  'qrild_qmi.c',
  'qrild_link.cc',
  'util.c',
]

foreach qmi : qmi_generated
  libqril_src += qmi
  # libqril_headers += 'qmi/@0@'.format(fs.name(qmi[0].full_path()))
  # libqril_src += 'qmi/@0@'.format(fs.name(qmi[1].full_path()))
  # message('qmi/@0@'.format(fs.name(qmi[1].full_path())))
endforeach

libqril = static_library('libqril', libqril_src,
  sources: libqril_src,
  include_directories: libqril_include,
  dependencies: libqril_deps,
  install: true,
)

install_headers(libqril_headers, subdir: 'libqril')
libqril_dep = declare_dependency(
  include_directories: libqril_include,
  link_with: libqril,
)
