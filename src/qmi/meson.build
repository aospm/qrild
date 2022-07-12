qmic = find_program('qmic')

qmi_srcs = [
  'qrild_dms.qmi',
  'qrild_dpm.qmi',
  'qrild_nas.qmi',
  'qrild_uim.qmi',
  'qrild_wda.qmi',
  'qrild_wds.qmi',
]

foreach qmi : qmi_srcs
  basename = qmi.split('_')[1].split('.')[0]
  src += custom_target('qmi_@0@.[ch]'.format(basename),
    output: ['qmi_@0@.h'.format(basename),
             'qmi_@0@.c'.format(basename)],
    input: qmi,
    command: [qmic, '-f', '@INPUT@', '-o', '@OUTDIR@'])
endforeach
