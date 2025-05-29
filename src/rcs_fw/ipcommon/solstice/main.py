import sys
from PyQt5 import uic, QtWidgets, QtGui
from PyQt5.QtCore import QThread, pyqtSignal, QTimer
from PyQt5.QtWidgets import QMainWindow, QApplication, QWidget
from PyQt5.QtWebEngineWidgets import QWebEngineView
# from tables import Tables
# from tables_page import TablesPage
from wf_gen import GeneratorPage
from wf_evm import EvmPage
import matlab.engine

# The GUI's main window
class MainWindow(QMainWindow):
    def __init__(self, eng):
        super(MainWindow, self).__init__()
        uic.loadUi('main_window.ui', self)
        self.setWindowTitle("HWC GUI")

        # matlab engine
        self.eng = eng

        # gui status
        self.status = self.findChild(QtWidgets.QLabel, "status_lb")
        self.status.setStyleSheet("color: green")
        self.status.setText("Ready")
        
        # page creation
        self.genPage = GeneratorPage(self)
        self.evmPage = EvmPage(self)
        #self.tablesPage = TablesPage(self)

    # Close event function for the GUI's main window 
    # Closes the matlab engine
    def closeEvent(self, *args, **kwargs):
        super(QMainWindow, self).closeEvent(*args, **kwargs)
        eng.quit()

# The loading screen with the progress bar
# Shown before the application's main window appears
# Screen closes once the matlab engine has opened
class LoadingScreen(QWidget):
    def __init__(self):
        super().__init__()
        uic.loadUi('loading_screen.ui', self)

        # progress bar and timer
        self.progress_bar =  self.findChild(QtWidgets.QProgressBar, "progressBar")
        self.timer = QTimer()
        self.timer.timeout.connect(lambda: self.update_progress(6))
        self.time_elapsed = 0
        self.timer.start(1000)

    # Updates the progress bar 
    # Progress bar is updated every 'sec' seconds
    def update_progress(self, sec):
        self.time_elapsed += 1000
        progress_percentage = (self.time_elapsed/(1000 * sec)) * 100
        if progress_percentage >= 99:
            progress_percentage = 99
            self.timer.stop()
        self.progress_bar.setValue(int(progress_percentage))

# Thread for opening the matlab engine
# Started once the loading screen has opened
class OpeningMatlabThread(QThread):
    # signals
    matlab_opened = pyqtSignal(object)  # signal to emit once matlab has successfully been opened 

    # automatically runs when thread is started
    def run(self):
        global eng 
        eng = matlab.engine.start_matlab()
        self.matlab_opened.emit(eng)

# Called when the application has finished loading (opening matlab engine)
# Closes the loading screen and opens the application's main window
def on_loading_complete(data, loading_screen):
    # set the eng to the matlab engine which was opened 
    global eng
    eng = data

    # close the loading screen
    loading_screen.close()

    # open the main window
    global main_window # this HAS to be global
    main_window = MainWindow(eng)
    main_window.show()

# Opens the loading screen
# Starts the thread to open the matlab engine
def main():
    # create the application and loading screen
    app = QApplication(sys.argv)
    loading_screen = LoadingScreen()
    loading_screen.show()

    # thread to open matlab engine
    open_matlab_thread = OpeningMatlabThread()
    open_matlab_thread.matlab_opened.connect(lambda data: (on_loading_complete(data, loading_screen)))
    open_matlab_thread.start()

    sys.exit(app.exec_())

if __name__ == "__main__":
    main()   