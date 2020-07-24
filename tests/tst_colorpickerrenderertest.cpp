#include <QtTest>

#include "../controlers/colorpicker/widgets/colorpicker.h"
#include "../controlers/colorpicker/common/colorpickerrenderer.h"

#include <pumpkintest.h>
#include <assertions.h>


inline std::ostream& operator<<(std::ostream& os, QSizeF const& s)
{
	os << s.width() << "/" << s.height();
	return os;
}


class ColorPickerRendererTest;
class ColorPickerBaseStub: ColorPickerBase
{
public:
	ColorPickerBaseStub(): ColorPickerBase(new ColorPickerRenderer(this, new QObject()))
	{}

	virtual void updateColor() override
	{
		updateColorCalled = true;
	}
	virtual void updateArea(const QRect &/*are*/) override
	{
		updateAreaCalled = true;
	}
	virtual QSizeF size() const override
	{
		return QSize(100, 100);
	}

	bool updateColorCalled;
	bool updateAreaCalled;
	bool validateCalled;


private:
	virtual void validate() override
	{
		validateCalled = true;
	}
	friend ColorPickerRendererTest;
};


class ColorPickerRendererTest : public PumpkinTest::AutoRegisteredTest
{
public:
	ColorPickerRendererTest(): PumpkinTest::AutoRegisteredTest("Color Picker Test")
	{
		test("contentRect should be inside the widget", []()
		{
			ColorPickerBaseStub stub;
			ColorPickerRendererBase* renderer = stub.getRenderer();
			PumpkinTest::Assertions::assertEquals(renderer->boundingRect().size(), stub.size());
		});
	}
};
REGISTER_TEST(ColorPickerRendererTest)
