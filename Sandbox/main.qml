import QtQuick 2.12
import QtQuick.Window 2.12

import pumpkin.tree 1.0

Window {
	visible: true
	width: 640
	height: 480

	/*Rectangle {
		id: root
		width: 200
		height: 50
		color: "blue"
		anchors.bottom: children.top
		anchors.horizontalCenter: children.horizontalCenter
	}

	Item {
		id: children
		anchors.left: parent.left
		anchors.bottom: parent.bottom

		height: 40
		width: item1.width + item2.width

		Rectangle {
			id: item1
			color: "red"
			width: 150
			height: 40
			MouseArea {
				anchors.fill: parent
				onClicked: item1.width = item1.width * 1.5
			}
		}

		Rectangle {
			id: item2
			color: "green"
			width: 150
			height: 40
			anchors.top: item1.top
			anchors.left: item1.right
		}
	}*/

	TreeView {
		anchors.fill: parent
		model: myModel
		verticalSpacing:  50
		horizontalSpacing: 20
		delegate: Rectangle {
			border.color: "gray"
			width: 60
			height: 30
			Text {
				anchors.centerIn: parent
				text: name
			}
		}
	}
}
