#include "pumpkin_gauges_plugin.h"
#include "verticalgauges.h"

#include <qqml.h>

void Pumpkin_GaugesPlugin::registerTypes(const char *uri)
{
	// @uri korev.romha.pumpkin
	qmlRegisterType<VerticalGauges>(uri, 1, 0, "VerticalGauges");
}

