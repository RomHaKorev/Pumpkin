import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Window 2.2

import QtQuick.Layouts 1.3

import pumpkin.gauges 1.0
import pumpkin.controlers 1.0
import pumpkin.indicators 1.0

Item {
    visible: true
    width: 640
    height: 480

    function updateGallery()
    {
        verticalGaugeWidget.setValue(foo.value)
        circularGaugeWidget.setValue(foo.value)
    }

    Column {
        RowLayout {
            //anchors.fill: parent
            Column {
                TextInput {
                    id: color
                    //text: picker.color
                    onAccepted: picker.color = text
                }
                ColorPicker {
                    id: picker
                    width: 200
                    height: 200
                    onColorChanged: color.text = picker.color
                }
            }

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
        }
        RowLayout {
            Repeater {
                id: segments
                property int offset: 0
                model: 10
                SevenSegments {
                    value: (index + segments.offset) % 10
                    width: 70
                    height: 120
                }
            }
        }

        Timer {
                interval: 1200;
                running: true;
                repeat: true
                onTriggered: segments.offset = (segments.offset + 1) % 10;
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
