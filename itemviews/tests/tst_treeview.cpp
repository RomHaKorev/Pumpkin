#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class TreeView : public QObject
{
	Q_OBJECT

public:
	TreeView();
	~TreeView();

private slots:
	void test_case1();

};

TreeView::TreeView()
{

}

TreeView::~TreeView()
{

}

void TreeView::test_case1()
{

}

QTEST_MAIN(TreeView)

#include "tst_treeview.moc"
