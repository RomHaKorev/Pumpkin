TEMPLATE = subdirs

SUBDIRS += indicators \
    Sandbox \
    controlers \
    PumpkinML \
    Demo \
    itemviews

Demo.depends = indicators controlers PumpkinML
