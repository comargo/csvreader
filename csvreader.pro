TEMPLATE = subdirs

SUBDIRS += \
    csvreader \
    cvsreader_test

cvsreader_test.depends = csvreader
