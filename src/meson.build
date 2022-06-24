src = [
  'qrild.c',
  'qrild_qmi.c',
  'qrild_msg.c',
  'qrild_link.c',
  'qmi_tlv.c',
  'util.c',
  # Auto-generated with qmic
  # 'qmi_uim.c',
  # 'qmi_dms.c',
]

subdir('qmi')

executable('qrild', src,
  include_directories: inc,
  dependencies: deps,
  install: true,
  c_args: [],
)
