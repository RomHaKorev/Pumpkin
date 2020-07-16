#include <QtTest>

#include "../src/widgets/colorpicker.h"

#include "../src/common/colorpickerrenderer.h"

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


class ColorPickerRendererTest : public QObject
{
	Q_OBJECT
private slots:
	void contentRectShouldBeInsideTheWidget()
	{
		ColorPickerBaseStub stub;
		ColorPickerRendererBase* renderer = stub.getRenderer();
		QTEST_ASSERT(renderer->boundingRect().size() == stub.size());
	}

};
