#include "verticaltreelayout.h"

#include <QDebug>
#include <QQmlContext>
#include <QAbstractItemModel>
#include <QPainter>

#include <qmath.h>

VerticalTreeLayout::VerticalTreeLayout(): QQuickPaintedItem(), delegate(nullptr)
{
	/*connect(this, &QQuickItem::childrenChanged, this, &VerticalTreeLayout::performLayout);
	connect(this, &QQuickItem::childrenRectChanged, this, &VerticalTreeLayout::performLayout);
	connect(this, &QQuickItem::widthChanged, this, &VerticalTreeLayout::performLayout);
	connect(this, &QQuickItem::heightChanged, this, &VerticalTreeLayout::performLayout);
	connect(this, &QQuickItem::visibleChanged, this, &VerticalTreeLayout::performLayout);
	connect(this, &QQuickItem::implicitWidthChanged, this, &VerticalTreeLayout::performLayout);
	connect(this, &QQuickItem::implicitHeightChanged, this, &VerticalTreeLayout::performLayout);
	connect(this, &QQuickItem::xChanged, this, &VerticalTreeLayout::performLayout);
	connect(this, &QQuickItem::yChanged, this, &VerticalTreeLayout::performLayout);*/
}

QQmlComponent* VerticalTreeLayout::getDelegate() const
{
	return delegate;
}

void VerticalTreeLayout::setDelegate(QQmlComponent* delegate)
{
	this->delegate = delegate;
	//performLayout();
}


QAbstractItemModel* VerticalTreeLayout::getModel() const
{
	return model;
}

void VerticalTreeLayout::setModel(QAbstractItemModel *model)
{
	this->model = model;
	performTreeLayout();
}

double VerticalTreeLayout::getHorizontalSpacing() const
{
	return horizontalSpacing;
}

void VerticalTreeLayout::setHorizontalSpacing(double value)
{
	horizontalSpacing = value;
	emit horizontalSpacingChanged();
}

double VerticalTreeLayout::getVerticalSpacing() const
{
	return verticalSpacing;
}

void VerticalTreeLayout::setVerticalSpacing(double value)
{
	verticalSpacing = value;
	emit verticalSpacingChanged();
}

void VerticalTreeLayout::performTreeLayout()
{
	if (model == nullptr)
		return;

	if (delegate == nullptr)
		return;
	performLayout();
}

void VerticalTreeLayout::performLayout()
{
	for (QQuickItem* item: nodes)
	{
		item->deleteLater();
	}
	for (QQuickItem* item: connectors)
	{
		item->deleteLater();
	}
	nodePositions.clear();
	nodes.clear();
	connectors.clear();

	itemWidth = 0;
	itemHeight = 0;
	calculateTreePositions();

	for (QModelIndex const& key: nodePositions.keys())
	{
		auto item = createItem(key);
		auto position = nodePositions[key];
		item->setX(position.x() * (horizontalSpacing + item->width()));
		item->setY(position.y() * (verticalSpacing + item->height()));
		nodes.insert(key, item);
	}
}

void VerticalTreeLayout::calculateTreePositions()
{
	this->nodePositions.clear();
	this->defineNodePosition(model->index(0,0));
}

double VerticalTreeLayout::defineNodePosition(QModelIndex const& index, double siblingCount, double depth)
{
	int rows = model->rowCount(index);
	if ( !index.isValid() )
		return 0.0;

	if ( rows == 0 )
	{
		this->configureXCoordinateForNode(index, siblingCount);
		this->configureYCoordinateForNode(index, depth);
		return siblingCount + 1;
	}

	for (int r = 0; r < rows; ++r)
	{
		QModelIndex child = model->index(r, 0, index);
		siblingCount = defineNodePosition(child, siblingCount, depth + 1);
	}

	qreal left = nodePositions[model->index(0, index.column(), index)].x();
	qreal right = nodePositions[model->index(rows - 1, index.column(), index)].x();

	if (rows >= 2)
	{
		if (rows % 2 == 1)
		{
			qreal r = qFloor(rows / 2) + 1;
			qreal v = nodePositions[model->index(r - 1, index.column(), index)].x();
			configureXCoordinateForNode(index, v);
		}
		else
			configureXCoordinateForNode(index, (right + left) / 2);
	}
	else
		configureXCoordinateForNode(index, left);

	configureYCoordinateForNode(index, depth);
	return right + 1;
}

void VerticalTreeLayout::configureXCoordinateForNode(QModelIndex const& index, qreal x)
{
	if (!nodePositions.contains(index))
		nodePositions.insert(index, QPointF());

	nodePositions[index].setX(x);
}

void VerticalTreeLayout::configureYCoordinateForNode(QModelIndex const& index, qreal y)
{
	if (!nodePositions.contains(index))
		nodePositions.insert(index, QPointF());

	nodePositions[index].setY(y);
}


QQuickItem* VerticalTreeLayout::createItem(const QModelIndex &root)
{
	QQmlContext* context = new QQmlContext(delegate->creationContext());
	context->setContextProperty("name", root.data());
	auto obj = delegate->create(context);
	QQuickItem *item = qobject_cast<QQuickItem*>(obj);
	item->setParentItem(this);

	itemWidth = qMax(itemWidth, item->width());
	itemHeight = qMax(itemHeight, item->height());

	return item;
}


void VerticalTreeLayout::paint(QPainter *painter)
{
	for (QModelIndex const& index: nodes.keys())
	{
		if (!index.parent().isValid())
			continue;

		QQuickItem* parent = nodes.value(index.parent());
		QQuickItem* item = nodes.value(index);
		paintConnection(painter, parent, item);
	}
}


void VerticalTreeLayout::paintConnection(QPainter *painter, QQuickItem *left, QQuickItem *right)
{
	QPointF p1 = left->mapToItem(this, left->boundingRect().center());
	QPointF p2 = right->mapToItem(this, right->boundingRect().center());
	painter->drawLine(p1, p2);
}
