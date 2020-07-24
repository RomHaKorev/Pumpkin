TEMPLATE = subdirs

SUBDIRS += indicators \
    controlers \
    PumpkinML \
    Demo \
    itemviews \
    tests

Demo.depends = indicators controlers PumpkinML
tests.depends = indicators controlers
