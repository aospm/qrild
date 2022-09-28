project('libqril', 'c', 'cpp')
cc = meson.get_compiler('c')
fs = import('fs')

qmic = find_program('qmic')

libqril_include = [
  include_directories('.'),
  include_directories('lib'),
  include_directories('qmi'),
]

libqril_headers = [
  'lib/libqril.h',
  'lib/libqril_qmi.h',
  'lib/libqril_client.hh',
  # FIXME: these aren't super well suited here
  'lib/list.h',
  'lib/q_log.h',
  'lib/workqueue.h',
]

libqril_src = [
  'libqril.c',
  'libqril_client.cc',
  'libqril_events.c',
  'libqril_messages.c',
  'libqril_qmi.c',
  'libqril_services.c',
  'libqril_services.h',
  'lock_tracker.c',
  'lock_tracker.h',
  'q_log.c',
  'qmi_tlv.c',
  #'qrild_link.cc',
  'timespec.c',
  'timespec.h',
  'util.c',
  'workqueue.c',
]

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
    command: [qmic, '-k', '-f', '@INPUT@', '-o', '@OUTDIR@'],
  )
endforeach

qmi_dep = declare_dependency(sources: qmi_generated)

libqril_deps = [ # ew
  cc.find_library('libqrtr', dirs: ['/usr/lib', '/usr/include']),
  qmi_dep,
]

foreach qmi : qmi_generated
  # libqril_src += 'qmi/@0@'.format(fs.name(qmi[1].full_path()))
  # libqril_headers += '@0@'.format(fs.name(qmi[0].full_path()))
  # libqril_src += 'qmi/@0@'.format(fs.name(qmi[1].full_path()))
  # message('qmi/@0@'.format(fs.name(qmi[1].full_path())))
endforeach

libqril = shared_library('qril', libqril_src,
  sources: libqril_src,
  include_directories: libqril_include,
  dependencies: libqril_deps,
  install: true,
  cpp_args: '-Wno-missing-braces'
)

install_headers(libqril_headers, subdir: 'libqril')
libqril_dep = declare_dependency(
  include_directories: libqril_include,
  link_with: libqril,
)

subdir('examples')
