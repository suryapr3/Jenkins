from PyQt5 import QtWidgets, uic
from PyQt5.QtWidgets import QMainWindow, QLabel, QTableWidget, QPushButton, QLineEdit, QListWidget, QTableWidgetItem, QListWidgetItem, QCompleter, QTabWidget, QWidget
from tables import Tables

# Tables Page Class
class TablesPage(QMainWindow):
    def __init__(self, main_window):
        super().__init__()
        self.main_window = main_window
        self.tables = Tables()
        self.createDataStructure()
        self.initList()
        self.initTable()
        

# - Sets up the main table widget including:
#   - Finding and initializing a label for the table's name.
#   - Connecting the save button to save the current state of the table.
#   - Calling methods to set the columns' headers, load data, and format the table.
    def initTable(self):
        self.table_title = self.main_window.findChild(QtWidgets.QLabel, "tableNameLabel")
        self.table = self.main_window.findChild(QtWidgets.QTableWidget, "tableWidget")
        self.save_button = self.main_window.findChild(QtWidgets.QPushButton, "saveButton")
        self.save_button.clicked.connect(self.saveButtonLambdaFunction)
        self.add_new_tab(self.main_window.outerTab, "My New Tab")
        self.setColumnNames()
        self.loadTableData()
        self.formatTable()
        

# - Initializes the list widget that displays the names of available CSV files:
#   - Loads names using `Tables` class.
#   - Adds a completer to the line edit for auto-suggesting file names.
#   - Preloads data from the first CSV file to the table.
    def initList(self):
        self.line_edit = self.main_window.findChild(QtWidgets.QLineEdit, "lineEdit")
        self.listWidget = self.main_window.findChild(QtWidgets.QListWidget, "listWidget")
        self.loadListData()
        self.listWidget.currentRowChanged.connect(self.slotOrLambdaFunction)

    def add_new_tab(self, outerTab, title):
        self.main_window.new_tab = QWidget()
        self.main_window.outerTab.addTab(self.main_window.new_tab, title)

# - Fetches and lists CSV file names from a specified directory.
# - Adds these names to the list widget and sets up a completer for the line edit to suggest names dynamically.
    def loadListData(self):
        csv_files = self.tables.getAllCsvFiles("../../tempdir/csv")
        new_csv_files = [file.split("\\")[-1].split(".")[0] for file in csv_files]
        # print(new_csv_files)
        for csv_file in new_csv_files:
            #print(csv_file)
            self.listWidget.addItem(QtWidgets.QListWidgetItem(csv_file))
        completer = QtWidgets.QCompleter(new_csv_files, self)
        self.line_edit.setCompleter(completer)
        self.tables.createTableDicts(csv_files[0] if csv_files else "default.csv")

#- Triggers saving of the currently displayed table data into a text file using the `Tables` class, with the file named after the table.
    def saveButtonLambdaFunction(self):
        self.tables.writeTableTxtFiles(self.tables.info_dict["Table Name"] + ".txt")

# - Handles list item selection changes:
#   - Finds and loads data from the selected CSV file into the table widget.
    def slotOrLambdaFunction(self, idx):
        this_csv_file = self.listWidget.currentItem().text()
        csv_file_path = self.tables.findCsvFile(this_csv_file + ".csv", "../../tempdir/csv")
        if csv_file_path:
            self.tables.createTableDicts(csv_file_path)
            self.initTable()

# - Adjusts visual settings of the table widget:
#   - Hides vertical headers and resizes columns and rows for better visibility and fit.
    def formatTable(self):
        #self.table_title.setText(self.tables.info_dict["Table Name"])
        self.table.verticalHeader().setVisible(False)
        self.table.resizeColumnsToContents()
        self.table.resizeRowsToContents()

#- Configures column headers in the table widget based on data keys from the `table_dict` managed by the `Tables` class.
    def setColumnNames(self):
        self.table.setColumnCount(len(self.tables.table_dict["Bit Field Name"]) + 1)
        for index, name in enumerate(self.tables.table_dict["Bit Field Name"]):
            self.table.setHorizontalHeaderItem(index + 1, QtWidgets.QTableWidgetItem(name))
            self.table.resizeColumnsToContents()

# - Fills the table widget with data:
#   - Iterates over the data dictionary, setting table cells to display data from the CSV.
    def loadTableData(self):
        self.table.setRowCount(len(self.tables.table_dict) - 1)
        row = 0
        col = 0
        for row_title, row_info in self.tables.table_dict.items():
            if row_title != "Bit Field Name":
                self.table.setItem(row, col, QtWidgets.QTableWidgetItem(row_title))
                col += 1
                for cell in row_info:
                    self.table.setItem(row, col, QtWidgets.QTableWidgetItem(cell))
                    col += 1
                row += 1
                col = 0

    def createDataStructure(self):
        self.tables.createFile()