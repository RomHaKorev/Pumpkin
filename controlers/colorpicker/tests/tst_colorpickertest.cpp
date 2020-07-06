#include <QtTest>

#include "../src/widgets/colorpicker.h"

class ColorPickerTest : public QObject
{
	Q_OBJECT

public:
	ColorPickerTest();
	~ColorPickerTest();

private slots:
	void test_case1();

};

ColorPickerTest::ColorPickerTest()
{

}

ColorPickerTest::~ColorPickerTest()
{

}

void ColorPickerTest::test_case1()
{
	Pumpkin::ColorPicker p;
}

QTEST_MAIN(ColorPickerTest)

#include "tst_colorpickertest.moc"
