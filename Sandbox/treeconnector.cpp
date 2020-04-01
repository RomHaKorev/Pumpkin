#include "treeconnector.h"

#include <QDebug>
#include <QPainter>

TreeConnector::TreeConnector(QQuickItem* left, QQuickItem* right, QQuickItem* parent): QQuickPaintedItem(parent),
	left(left), right(right)
{
	listenItemChanges(left);
	listenItemChanges(right);

	setParentItem(parent);

	setWidth(boundingRect().width());
	setHeight(boundingRect().height());
	setX(boundingRect().x());
	setY(boundingRect().y());
}

void TreeConnector::listenItemChanges(QQuickItem* item)
{
	if (!item)
		return;
	connect(item, &QQuickItem::xChanged, this, &QQuickItem::update);
	connect(item, &QQuickItem::yChanged, this, &QQuickItem::update);
	connect(item, &QQuickItem::widthChanged, this, &QQuickItem::update);
	connect(item, &QQuickItem::heightChanged, this, &QQuickItem::update);
	connect(item, &QQuickItem::implicitWidthChanged, this, &QQuickItem::update);
	connect(item, &QQuickItem::implicitHeightChanged, this, &QQuickItem::update);
}

QRectF TreeConnector::boundingRect() const
{
	if (!left || !right)
		return QRectF();

	QPointF p1 = left->mapToItem(this, left->boundingRect().center());
	QPointF p2 = right->mapToItem(this, right->boundingRect().center());
	return QRectF(p1, p2).normalized();
}

void TreeConnector::paint(QPainter* painter)
{
	QPointF p4 = left->boundingRect().translated(left->position()).center();
	QPointF p5 = right->boundingRect().translated(right->position()).center();

	QPointF p1 = left->mapToItem(this, left->boundingRect().center());
	QPointF p2 = right->mapToItem(this, right->boundingRect().center());
	qDebug() << mapToGlobal(p1) << mapToGlobal(p2) << left->mapToGlobal(p4) << right->mapToGlobal(p5);
	painter->drawLine(p1, p2);
}

