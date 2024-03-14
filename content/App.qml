// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.6
import QtQuick.Controls
import StudentManagement
import TableStudentController
import QtQuick.Dialogs
import Student
Window {
    id: mainWindow
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: "StudentManagement"
    TableStudentController{
        id: tableStudentController
    }

    Screen01 {
        id: mainScreen

        MessageDialog {
            id: mdNotifyError
            text: "Input is invalid"
            buttons: MessageDialog.Ok
            onAccepted: {
                mdNotifyError.close()
                mdNotifyError.informativeText = ""
            }
        }

        tableStudent.model: tableStudentController
        tableStudent.selectionMode: TableView.SingleSelection
        tableStudent.selectionBehavior: TableView.SelectRows

        tableStudent.selectionModel: ItemSelectionModel{
            onCurrentChanged: {
                if(currentIndex.row === -1){
                    return
                }
                var rowidx = currentIndex.row
                mainScreen.tfFullName.text = tableStudentController.data(tableStudentController.index(rowidx, 0), Qt.DisplayRole)
                mainScreen.tfStudentCode.text = tableStudentController.data(tableStudentController.index(rowidx, 1), Qt.DisplayRole)
                mainScreen.tfClassCode.text = tableStudentController.data(tableStudentController.index(rowidx, 2), Qt.DisplayRole)
                mainScreen.tfBirthday.text = tableStudentController.data(tableStudentController.index(rowidx, 3), Qt.DisplayRole)
            }
        }

        tableStudent.delegate: Rectangle {
            implicitWidth: 160
            implicitHeight: 60
            color: current ? "blue" : "lightgray"
            required property bool current
            Text { text: display
                anchors.centerIn: parent
                font.pixelSize: 16

            }

        }

        rbInsertItem.onClicked: {
            tableStudentController.appendStudent(tfFullName.text, tfStudentCode.text, tfClassCode.text, tfBirthday.text)
        }

        rbUpdateItem.onClicked: {
           var isSuccess = tableStudent.model.updateStudent(tableStudent.selectionModel.currentIndex.row, tfFullName.text, tfStudentCode.text, tfClassCode.text, tfBirthday.text)
            if(isSuccess){
                tableStudent.selectionModel.clear()
                rbReset.clicked()
            }
        }

        rbReset.onClicked: {
            tfFullName.text = ""
            tfStudentCode.text = ""
            tfClassCode.text = ""
            tfBirthday.text = ""
            tableStudent.selectionModel.clear()
        }

        rbDeleteItem.onClicked : {
            tableStudent.model.deleteStudent(tableStudent.selectionModel.currentIndex.row)
            tableStudent.selectionModel.clear()
        }

        rbSortItem.onClicked: {
            tableStudentController.sortTable(3,0)
        }

        Connections{
            target: tableStudentController
            onHasError: function (messageError){
                mdNotifyError.informativeText = qsTr(messageError)
                mdNotifyError.open()
            }
        }


    }
}





