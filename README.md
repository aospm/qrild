# qrild

qrild is an open source Radio Interface Layer or "Modem HAL" for Android devices
using QRTR/QMI modems such as the OnePlus 6 and PocoPhone F1 supported by AOSPM.

## Status

Development is currently halted, I (caleb) am stepping away from the project. If
you're interested in continuing development, please open an issue (or PR :P) and
I'll be more than happy to help.

The main branch contains a very hacky proof of concept, it implements enough of
the core HAL, however the code is not very readable and the QMI message handling
code (in the libqril subdir) is full of memory leaks. You should only use the
main branch for reference.

Libqril has been rewritten to be a standalone library, [it can be found
here](https://github.com/aospm/libqril). It now has a well defined API and makes
use of new versions of [qmic](https://github.com/aospm/qmic) and
[qrtr](https://github.com/aospm/qrtr).

As it stands, qrild needs to be mostly rewritten to make use of the new libqril
library, this should offer a lot of improvements, reducing the size of the
codebase and being generally a bit more stable. See the libqril repo for
examples.

Previously, QRTR was used from
[shared/vendor/qrtr](https://github.com/aospm/android_device_generic_sdm845/tree/rild/shared/vendor/qrtr)
in device_generic_sdm845. This isn't ideal as it is then only accessible within
the project. Instead, QRTR should be cloned as it's own project - or at least
made available to external projects. In general, some integration and work will
likely be needed to set up a sensible AOSP build environment for this.

The proof of concept in the main branch is capable of setting up a mobile data
connection, however I was never able to get Android to agree and configure DNS,
at least not with the device configuration I had. I would suggest looking at the
[commit history of the rild branch of
android_device_generic_sdm845](https://github.com/aospm/android_device_generic_sdm845/commits/rild)
to understand how to enable the HAL, etc.

## Dependencies

* [Libqril](https://github.com/aospm/libqril)
