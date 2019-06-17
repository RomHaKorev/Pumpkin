import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Window 2.2

import QtQuick.Layouts 1.3

import pumpkin.gauges 1.0

//import "../boxes/qml"

Item {
    visible: true
    width: 640
    height: 480

    function updateGallery()
    {
        verticalGaugeWidget.setValue(foo.value)
        circularGaugeWidget.setValue(foo.value)
    }

    RowLayout {
        anchors.fill: parent
        VerticalGauge {
            minimum: 0
            maximum: 100
            value: foo.value
            style.rounded: true
        }
        CircularGauge {
            minimum: 0
            maximum: 100
            value: foo.value
            style.rounded: true
        }
        SpinBox {
            id: foo
            from: 0
            to: 100
            value: 50
            editable: true
            onValueChanged: updateGallery()
            Component.onCompleted: updateGallery()
        }
        /*CollapsibleGroupBox {
            title: qsTr("Synchronize")
            //Layout.alignment: Qt.AlignTop
            ColumnLayout {
                anchors.fill: parent
                CheckBox { text: qsTr("E-mail") }
                CheckBox { text: qsTr("Calendar") }
                CheckBox { text: qsTr("Contacts") }
            }
        }*/
    }


}
