#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QWidget>
#include "../renderers/colorpickerrenderer.h"
#include "../colorpickercommon.h"

namespace Pumpkin {
class ColorPicker : public QWidget
{
	Q_OBJECT
	COLORPICKER_INTERFACE
public:
	explicit ColorPicker(QWidget *parent = nullptr);
	virtual void paintEvent(QPaintEvent* event) override;

	virtual QSize sizeHint() const override { return QSize(120, 120); }

private:
	ColorPickerRenderer<Pumpkin::ColorPicker>* renderer;
};
}

#endif // COLORPICKER_H
