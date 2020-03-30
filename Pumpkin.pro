TEMPLATE = subdirs

SUBDIRS += gauges \
    controlers \
    PumpkinML \
    Demo \
    itemviews


Demo.depends = gauges controlers PumpkinML
