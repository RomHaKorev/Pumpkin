TEMPLATE = subdirs

SUBDIRS += gauges \
    spinners \
    PumpkinML \
    Demo


Demo.depends = gauges spinners PumpkinML
