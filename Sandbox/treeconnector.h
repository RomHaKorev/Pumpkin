#ifndef TREECONNECTOR_H
#define TREECONNECTOR_H

#include <QQuickPaintedItem>

class TreeConnector : public QQuickPaintedItem
{
public:
	TreeConnector(QQuickItem* left, QQuickItem* right, QQuickItem* parent);
private:
	QQuickItem* left;
	QQuickItem* right;

	void updateDrawing();
	void listenItemChanges(QQuickItem*);

public:
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter* painter) override;
};

#endif // TREECONNECTOR_H
