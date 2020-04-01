#ifndef VERTICALTREELAYOUT_H
#define VERTICALTREELAYOUT_H

#include <QQuickPaintedItem>
#include <QMap>
#include <QModelIndex>

class QAbstractItemModel;

class VerticalTreeLayout : public QQuickPaintedItem
{
	Q_OBJECT
public:

	Q_PROPERTY(QQmlComponent* delegate READ getDelegate WRITE setDelegate NOTIFY delegateChanged)
	Q_PROPERTY(QAbstractItemModel* model READ getModel WRITE setModel NOTIFY modelChanged)

	Q_PROPERTY(double horizontalSpacing READ getHorizontalSpacing WRITE setHorizontalSpacing NOTIFY horizontalSpacingChanged)
	Q_PROPERTY(double verticalSpacing READ getVerticalSpacing WRITE setVerticalSpacing NOTIFY verticalSpacingChanged)

	VerticalTreeLayout();

	Q_INVOKABLE QQmlComponent* getDelegate() const;
	Q_INVOKABLE void setDelegate(QQmlComponent* );

	Q_INVOKABLE QAbstractItemModel* getModel() const;
	Q_INVOKABLE void setModel(QAbstractItemModel* model);

	Q_INVOKABLE double getHorizontalSpacing() const;
	Q_INVOKABLE void setHorizontalSpacing(double value);

	Q_INVOKABLE double getVerticalSpacing() const;
	Q_INVOKABLE void setVerticalSpacing(double value);

signals:
	void delegateChanged();
	void modelChanged();
	void horizontalSpacingChanged();
	void verticalSpacingChanged();

private:
	QQmlComponent* delegate;
	QAbstractItemModel* model;

	double itemWidth;
	double itemHeight;

	double horizontalSpacing;
	double verticalSpacing;

	void performLayout();

	QQuickItem* createItem(QModelIndex const& root);

	QMap<QModelIndex, QPointF> nodePositions;
	QMap<QModelIndex, QQuickItem*> nodes;
	QList<QQuickItem*> connectors;

	void performTreeLayout();
	void calculateTreePositions();
	double defineNodePosition(const QModelIndex& index, double siblingCount=0, double depth=0);
	void configureXCoordinateForNode(QModelIndex const& index, qreal x);
	void configureYCoordinateForNode(QModelIndex const& index, qreal y);

	// QQuickPaintedItem interface
public:
	void paint(QPainter* painter);

private:
	void paintConnection(QPainter* painter, QQuickItem* left, QQuickItem* right);
};

#endif // VERTICALTREELAYOUT_H
