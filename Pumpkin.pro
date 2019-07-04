TEMPLATE = subdirs

SUBDIRS += gauges \
    controlers \
    PumpkinML \
    Demo


Demo.depends = gauges controlers PumpkinML
