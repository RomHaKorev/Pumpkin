#include <../controlers/colorpicker/widgets/colorpicker.h>

#include "../controlers/colorpicker/common/util/colortoangleconverter.h"
#include "../controlers/colorpicker/common/util/cursorcolorizer.h"

#include <pumpkintest.h>
#include <assertions.h>

inline std::ostream& operator<<(std::ostream& os, QColor const& s)
{
	os << "QColor(" << s.red() << ", " << s.green() << ", " << s.blue() << ")";
	return os;
}

class ColorPickerUtilTest : public PumpkinTest::AutoRegisteredTest
{
public:
	ColorPickerUtilTest(): PumpkinTest::AutoRegisteredTest("Color Picker Test Utils")
	{
		test("Dark color should be at angle 0", []()
		{
			PumpkinTest::Assertions::assertEquals(0, int(valueAndSaturationToAngle(QColor::fromHsv(0, 0, 0))));
		});

		test("Light color should be at angle 180", []()
		{
			PumpkinTest::Assertions::assertEquals(180, int(valueAndSaturationToAngle(QColor::fromHsv(255, 0, 255))));
		});

		test("Middle color should be At 90", []()
		{
			PumpkinTest::Assertions::assertEquals(90, int(valueAndSaturationToAngle(QColor::fromHsv(255, 255, 255))));
		});

		test("Color should be at right angle", []()
		{
			PumpkinTest::Assertions::assertEquals(45, int(valueAndSaturationToAngle(QColor::fromHsv(128, 128, 128))));
		});

		test("Should pick a dark color when white", []()
		{
			CursorColorizer sut(0, 180);
			PumpkinTest::Assertions::assertEquals(sut(QColor(255, 255, 255)), QColor(40, 40, 40));
		});

		test("Should pick a light color when black", []()
		{
			CursorColorizer sut(0, 180);
			PumpkinTest::Assertions::assertEquals(sut(QColor(0, 0, 0)), QColor(240, 240, 240));
		});

		test("Should pick a color with smooth transition", []()
		{
			CursorColorizer sut(0, 180);
			PumpkinTest::Assertions::assertEquals(sut(QColor(0, 255, 128)).toRgb(), QColor(153, 153, 153));
		});
	}
};
REGISTER_TEST(ColorPickerUtilTest)
