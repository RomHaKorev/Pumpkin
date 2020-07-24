#include "pumpkin_gauges_plugin.h"
#include "../widgets/verticalgauge.h"

#include <qqml.h>

void Pumpkin_GaugesPlugin::registerTypes(const char* uri)
{
	// @uri korev.romha.pumpkin
	qmlRegisterType<Pumpkin::VerticalGauge>(uri, 1, 0, "VerticalGauges");
}

