#include <QtTest>

#include "../src/widgets/colorpicker.h"

#include "../src/common/util/colortoangleconverter.h"
#include "../src/common/util/cursorcolorizer.h"

class ColorPickerUtilTest : public QObject
{
	Q_OBJECT
private slots:
	void darkColorShouldBeAtAngle0()
	{
		QTEST_ASSERT(0 == int(valueAndSaturationToAngle(QColor::fromHsv(0, 0, 0))));
	}

	void lightColorShouldBeAtAngle180()
	{
		QTEST_ASSERT(180 == int(valueAndSaturationToAngle(QColor::fromHsv(255, 0, 255))));
	}

	void middleColorShouldBeAt90() {
		QTEST_ASSERT(90 == int(valueAndSaturationToAngle(QColor::fromHsv(255, 255, 255))));
	}

	void colorShouldBeAtRightAngle() {
		QTEST_ASSERT(45 == int(valueAndSaturationToAngle(QColor::fromHsv(128, 128, 128))));
	}

	void shouldPickDarkColorWhenWhite()
	{
		CursorColorizer sut(0, 180);
		QTEST_ASSERT(sut(QColor(255, 255, 255)) == QColor(40, 40, 40));
	}

	void shouldPickLightColorWhenBlack()
	{
		CursorColorizer sut(0, 180);
		QTEST_ASSERT(sut(QColor(0, 0, 0)) == QColor(240, 240, 240));
	}

	void shouldPickColorWithSmoothTransition()
	{
		CursorColorizer sut(0, 180);
		QTEST_ASSERT(sut(QColor(0, 255, 128)).toRgb() == QColor(153, 153, 153));
	}
};
