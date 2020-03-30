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


import QtQuick 2.11
import QtQuick.Controls 2.5
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.0
import QtQuick.Shapes 1.12

Item {
	id: groupbox
	property string title
	property bool expand: true

	default property alias __content: container.data

	readonly property alias contentItem: container

	implicitWidth: Math.max((!anchors.fill ? container.calcWidth() : 0) + 20,
							titleBar.implicitWidth + 24)
	implicitHeight: (!anchors.fill ? container.calcHeight() : 0) + titleBar.height + 20

	Layout.minimumWidth: implicitWidth
	Layout.minimumHeight: implicitHeight

	Accessible.role: Accessible.Grouping
	Accessible.name: title

	activeFocusOnTab: false

	data: [
		Item {
			anchors.top: parent.top
			anchors.left: parent.left
			anchors.right: parent.right
			height: titleText.height
		RowLayout {
			id: titleBar;
			visible: true;
			anchors.leftMargin: 10
			spacing: 6
			Canvas {
				id: indicator
				width: 12
				height: 8
				transform: Rotation { id: indicatorAngle; origin.x: 6; origin.y: 4; angle: 0}
				onPaint: {
					var ctx = getContext("2d");
					ctx.fillStyle = "grey";//Qt.rgba(1, 0, 0, 1);
					ctx.moveTo(6, 8);
					ctx.lineTo(12, 0);
					ctx.lineTo(0, 0);
					ctx.closePath();
					ctx.fill()
				}
			}
			Text {
				id: titleText
				text: groupbox.title
			}
		}
		MouseArea {
			id: titleArea
			anchors.fill: parent
			onClicked: { groupbox.expand = !groupbox.expand; }
		}
		},
		Rectangle {
			id: closedBar
			height: 2
			color: frame.background.border.color
			anchors.top: parent.top
			anchors.left: parent.horizontalCenter
			anchors.right: parent.horizontalCenter
			anchors.topMargin: titleBar.height + 4
		},
		Frame {
			anchors.top: parent.top
			anchors.left: parent.left
			anchors.right: parent.right
			anchors.bottom: parent.bottom
			anchors.topMargin: titleBar.height + 4
			//padding: 0
			id: frame
			Item {
				id: container
				objectName: "container"
				focus: true
				anchors.fill: parent
				property Item layoutItem: container.children.length === 1 ? container.children[0] : null
				function calcWidth () {
						return (layoutItem ? (layoutItem.implicitWidth || layoutItem.width) +
															 (layoutItem.anchors.fill ? layoutItem.anchors.leftMargin +
																						layoutItem.anchors.rightMargin : 0) : container.childrenRect.width);
				}
				function calcHeight () {
					return (layoutItem ? (layoutItem.implicitHeight || layoutItem.height) +
															  (layoutItem.anchors.fill ? layoutItem.anchors.topMargin +
																						 layoutItem.anchors.bottomMargin : 0) : container.childrenRect.height);
				}
			}
		}]

	states: [State {
				name: "collapseAnimation"
				AnchorChanges { target: frame; anchors.bottom: groupbox.top }
				AnchorChanges { target: closedBar; anchors.left: parent.left; anchors.right: parent.right }
				PropertyChanges { target: container; opacity: 0.0 }
				PropertyChanges {
					target: indicatorAngle
					angle: -90
				}
				when: !groupbox.expand
			},
			State {
				name: "expandAnimation"
				AnchorChanges { target: frame; anchors.bottom: groupbox.bottom }
				PropertyChanges { target: container; opacity: 1.0 }
				PropertyChanges {
					target: indicatorAngle
					angle: 0
				}
				when: groupbox.expand
			}]
	transitions: [Transition {
					 from: "expandAnimation"
					 to: "collapseAnimation"
					 NumberAnimation { property: "angle"; duration: 600}
					 SequentialAnimation {
						 NumberAnimation { property: "opacity"; duration: 400}
						 AnchorAnimation { duration: 400 }
					 }
				  },
				  Transition {
					 to: "expandAnimation"
					 from: "collapseAnimation"
					 NumberAnimation { property: "angle"; duration: 600}
					 SequentialAnimation {
						 AnchorAnimation { duration: 400 }
						 NumberAnimation { property: "opacity"; duration: 400}
					 }
				  }
	]

}
