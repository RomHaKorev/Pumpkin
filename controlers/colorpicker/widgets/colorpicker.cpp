/*
Copyright Romha Korev and dimitry Ernot (2020-03-30)

romha [dot] korev [at] gmail [dot] com
ernd [dot] mail [at] gmail [dot] com

This software is a computer program whose purpose is to provide a Design System for Qt Applications.

This software is governed by the CeCILL-C license under French law and
abiding by the rules of distribution of free software.  You can  use,
modify and/ or redistribute the software under the terms of the CeCILL-C
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability.

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-C license and that you accept its terms.
*/

#include "colorpicker.h"

#include <QPaintEvent>

Pumpkin::ColorPicker::ColorPicker(QWidget *parent) : QWidget(parent), ColorPickerBase(new ColorPickerRenderer(this, this))
{
	resize(120, 120);
}


void Pumpkin::ColorPicker::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	paint(painter);
}

void Pumpkin::ColorPicker::updateColor()
{
	update();
}

void Pumpkin::ColorPicker::validate()
{
	colorChanged(color());
}

void Pumpkin::ColorPicker::mousePressEvent(QMouseEvent *event)
{
	handleMousePressEvent(event);
}

void Pumpkin::ColorPicker::mouseMoveEvent(QMouseEvent *event)
{
	handleMouseMoveEvent(event);
}

void Pumpkin::ColorPicker::mouseReleaseEvent(QMouseEvent *event)
{
	handleMouseReleaseEvent(event);
}

void Pumpkin::ColorPicker::updateArea(const QRect &area)
{
	this->update(area);
}

QSizeF Pumpkin::ColorPicker::size() const
{
	return QWidget::size();
}
