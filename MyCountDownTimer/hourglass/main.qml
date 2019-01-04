import QtQuick 2.2

Rectangle {
  width: 48
  height: 48
  color: "#9c27b0"

  MouseArea {
    anchors.fill: parent
    //onClicked: menuBackIcon.state = menuBackIcon.state === "menu" ? "back" : "menu"
    onClicked: testQml.state = testQml.state === "menu" ? "back" : "menu"

  }

  testQml {
    id: menuBackIcon
    anchors.centerIn: parent
  }
}
