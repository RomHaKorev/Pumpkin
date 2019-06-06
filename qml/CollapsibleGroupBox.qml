/*import QtQuick 2.11

import QtQuick.Controls 2.0

import QtQuick.Layouts 1.3



import QtQuick.Window 2.11



import QtQuick 2.9

import QtQuick.Window 2.2

import QtGraphicalEffects 1.0



import QtQuick 2.12

import QtQuick.Window 2.12

import QtQuick.Controls 1.4

import Qt.labs.folderlistmodel 2.12

Item {
    property alias contentItem: content.contentItem;
    property string title: ""
    ColumnLayout {
        anchors.fill: parent
        Rectangle {
            id: titleBar
            color: "red"
            //Layout.maximumHeight: label.height + 10
            //Layout.maximumWidth: label.width + expand.width + 10
            RowLayout {
                anchors.fill: parent
                CheckBox {
                    Layout.alignment: Qt.AlignLeft
                    id: expand
                    checked: true;
                }
                Text {
                    Layout.alignment: Qt.AlignLeft
                    text: title
                    id: label
                }
            }
        }
        Rectangle {
            color: "green"
            Layout.minimumHeight: content.contentHeight
            Layout.minimumWidth: content.contentWidth
            Layout.fillWidth: true
            Pane {
                anchors.fill: parent
//                topPadding: 0
                visible: expand.checked
                id: content

                onContentItemChanged: contentItem.anchors.fill = content
                //onContentDataChanged:
            }
        }
    }
}*/


import QtQuick 2.11
import QtQuick.Controls 2.5
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.0

/*!
    \qmltype GroupBox
    \inqmlmodule QtQuick.Controls
    \since 5.1
    \ingroup controls
    \brief GroupBox provides a group box frame with a title.
    A group box provides a frame, a title on top and displays various other controls inside itself. Group boxes can also be checkable.
    Child controls in checkable group boxes are enabled or disabled depending on whether or not the group box is checked.
    You can minimize the space consumption of a group box by enabling the flat property.
    In most styles, enabling this property results in the removal of the left, right and bottom edges of the frame.
    To add content to a group box, you can reparent it to its contentItem property.
    The implicit size of the GroupBox is calculated based on the size of its content. If you want to anchor
    items inside the group box, you must specify an explicit width and height on the GroupBox itself.
    The following example shows how we use a GroupBox with a column:
    \qml
        GroupBox {
            title: qsTr("Package selection")
            Column {
                spacing: 2
                CheckBox {
                    text: qsTr("Update system")
                }
                CheckBox {
                    text: qsTr("Update applications")
                }
                CheckBox {
                    text: qsTr("Update documentation")
                }
            }
        }
    \endqml
    \sa CheckBox, RadioButton, Layout
*/

Item {
    id: groupbox
    property string title
    property bool ellapsed: true

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


    onEllapsedChanged: {
        return;
        if(!ellapsed)
            groupbox.state = "collapseAnimation"
        else
            groupbox.state = "ellapseAnimation"
    }

    data: [
        Item {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: titleText.height
        Row {
            id: titleBar;
            visible: true;
            anchors.leftMargin: 10
            spacing: 6
            Rectangle {
                anchors.verticalCenter: parent.verticalCenter
                width: 8
                height: 8
                color: "red"
            }
            Text {
                id: titleText
                text: groupbox.title
            }
        }
        MouseArea {
            id: titleArea
            anchors.fill: parent
            onClicked: { groupbox.ellapsed = !groupbox.ellapsed; }
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
                when: !groupbox.ellapsed
            },
            State {
                name: "ellapseAnimation"
                AnchorChanges { target: frame; anchors.bottom: groupbox.bottom }
                PropertyChanges { target: container; opacity: 1.0 }
                when: groupbox.ellapsed
            }]
    transitions: [Transition {
                     from: "ellapseAnimation"
                     to: "collapseAnimation"
                     SequentialAnimation {
                         NumberAnimation { property: "opacity"; duration: 200}
                         AnchorAnimation { duration: 400 }
                     }
                  },
                  Transition {
                     to: "ellapseAnimation"
                     from: "collapseAnimation"
                     SequentialAnimation {
                         AnchorAnimation { duration: 400 }
                         NumberAnimation { property: "opacity"; duration: 200}
                     }
                  }
    ]

}
