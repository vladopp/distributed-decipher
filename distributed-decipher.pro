TEMPLATE = subdirs
SUBDIRS = master \
          worker \
    common

# build must be last:
CONFIG += ordered
# SUBDIRS += build
