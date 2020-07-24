#include <QtTest>

#include "../src/widgets/colorpicker.h"

#include "../src/common/util/colortoangleconverter.h"
#include "../src/common/util/cursorcolorizer.h"

#include <pumpkintest.h>
#include <assertions.h>

class ColorPickerUtilTest : public PumpkinTest::AutoRegisteredTest
{
public:
	ColorPickerUtilTest(): PumpkinTest::AutoRegisteredTest("Color Picker Test Utils")
	{
		test("darkColorShouldBeAtAngle0", []()
		{
			QTEST_ASSERT(0 == int(valueAndSaturationToAngle(QColor::fromHsv(0, 0, 0))));
		});

		test("lightColorShouldBeAtAngle180", []()
		{
			QTEST_ASSERT(180 == int(valueAndSaturationToAngle(QColor::fromHsv(255, 0, 255))));
		});

		test("middleColorShouldBeAt90", []()
		{
			QTEST_ASSERT(90 == int(valueAndSaturationToAngle(QColor::fromHsv(255, 255, 255))));
		});

		test("colorShouldBeAtRightAngle", []()
		{
			QTEST_ASSERT(45 == int(valueAndSaturationToAngle(QColor::fromHsv(128, 128, 128))));
		});

		test("shouldPickDarkColorWhenWhite", []()
		{
			CursorColorizer sut(0, 180);
			QTEST_ASSERT(sut(QColor(255, 255, 255)) == QColor(40, 40, 40));
		});

		test("shouldPickLightColorWhenBlack", []()
		{
			CursorColorizer sut(0, 180);
			QTEST_ASSERT(sut(QColor(0, 0, 0)) == QColor(240, 240, 240));
		});

		test("shouldPickColorWithSmoothTransition", []()
		{
			CursorColorizer sut(0, 180);
			QTEST_ASSERT(sut(QColor(0, 255, 128)).toRgb() == QColor(153, 153, 153));
		});
	}
};
REGISTER_TEST(ColorPickerUtilTest)
