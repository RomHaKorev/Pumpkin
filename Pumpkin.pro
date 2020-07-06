TEMPLATE = subdirs

SUBDIRS += gauges \
    Sandbox \
    controlers \
    PumpkinML \
    Demo \
    itemviews

Demo.depends = gauges controlers PumpkinML
