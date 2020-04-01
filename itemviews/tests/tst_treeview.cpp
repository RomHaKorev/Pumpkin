#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class TreeViewUnitTests : public QObject
{
	Q_OBJECT

public:
	TreeViewUnitTests();
	~TreeViewUnitTests();

private slots:
	void test_case1();

};

TreeViewUnitTests::TreeViewUnitTests()
{

}

TreeViewUnitTests::~TreeViewUnitTests()
{

}

void TreeViewUnitTests::test_case1()
{

}
// QTEST_MAIN(TreeView)

#include "tst_treeview.moc"
