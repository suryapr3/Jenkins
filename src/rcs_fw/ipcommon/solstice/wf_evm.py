from PyQt5.QtCore import QObject
from PyQt5 import QtWidgets
from PyQt5.QtWebEngineWidgets import QWebEngineView
from PyQt5.QtWidgets import QApplication, QHeaderView
from functools import partial
from PyQt5.QtCore import Qt, QObject, QUrl, pyqtSignal, pyqtSlot, QThread
import matlab.engine
from PyQt5.QtGui import QCursor
from pprint import pprint
import plotly.express as px
import pandas as pd
import plotly.graph_objs as go
import os

# EVM Page Class
class EvmPage(QObject):

    def __init__(self, main_window):
        super().__init__()
        self.main_window = main_window
        self.eng = main_window.eng
        self.status = main_window.status
        self.initElements()
    
    # Finds and assigns objects of the UI file to attributes of the class
    def initElements(self):
        # combo box
        self.source_cmb = self.main_window.findChild(QtWidgets.QComboBox, "evm_source_cmb")
        self.source_cmb.currentTextChanged.connect(self.sourceCmbStateChanged)
        self.units_cmb = self.main_window.findChild(QtWidgets.QComboBox, "evm_units_cmb")
        # check box
        self.correction_chb = self.main_window.findChild(QtWidgets.QCheckBox, "evm_correction_chb")
        self.constellation_chb = self.main_window.findChild(QtWidgets.QCheckBox, "evm_constellation_chb")
        # label
        self.errorMsg_lb = self.main_window.findChild(QtWidgets.QLabel, "evm_status_lb")
        self.attentuation_lb = self.main_window.findChild(QtWidgets.QLabel, "evm_attentuation_lb")
        self.filename_lb = self.main_window.findChild(QtWidgets.QLabel, "evm_filename_lb")
        # line edit
        self.attenuation_le = self.main_window.findChild(QtWidgets.QLineEdit, "evm_attenuation_le")
        self.filename_le = self.main_window.findChild(QtWidgets.QLineEdit, "evm_filename_le")
        self.filename_le.textChanged.connect(self.validateFileInput)
        # push button
        self.analyze_pb = self.main_window.findChild(QtWidgets.QPushButton, "evm_analyze_pb")
        self.analyze_pb.clicked.connect(self.analyzeButtonPress)
        # views
        self.symbol_plot = self.main_window.findChild(QWebEngineView, "evm_symbolPlot_wv")
        self.resource_plot = self.main_window.findChild(QWebEngineView, "evm_resourcePlot_wv")
        # widgets 
        self.table_tw = self.main_window.findChild(QtWidgets.QTableWidget, "evm_table_tw")
        # gen page
        self.duplexMode_cmb = self.main_window.findChild(QtWidgets.QComboBox, "gen_duplexMode_cmb") # why do this?

    # Event handlers for checkbox selects/combobox changes
    # Disables/enables certain inputs depending on selected checkbox/combobox 
    def sourceCmbStateChanged(self):
        if (self.source_cmb.currentText() == "Waveform File"):
            self.attentuation_lb.setEnabled(False)
            self.attenuation_le.setEnabled(False)
            self.correction_chb.setEnabled(False)
            self.filename_le.setEnabled(True)
            self.filename_lb.setEnabled(True)
        else:
            self.attentuation_lb.setEnabled(True)
            self.attenuation_le.setEnabled(True)
            self.correction_chb.setEnabled(True)
            self.filename_le.setEnabled(False)
            self.filename_lb.setEnabled(False)
    
    # Sets the application status to 'Busy'
    # Sets the generator page's error message 
    def genBusyStatus(self, error_msg):
        self.status.setStyleSheet("color: blue")
        self.status.setText("Busy")
        self.errorMsg_lb.setStyleSheet("color: blue")
        self.errorMsg_lb.setText(error_msg)
        QApplication.processEvents()

    # Sets the application status to 'Errored'
    # Sets the generator page's error message 
    @pyqtSlot(str)
    def genErrorStatus(self, error_msg):
        self.status.setStyleSheet("color: red")
        self.status.setText("Errored")
        self.errorMsg_lb.setStyleSheet("color: red")
        self.errorMsg_lb.setText(error_msg)
        self.analyze_pb.setCursor(QCursor(Qt.ArrowCursor))
        QApplication.processEvents()

    # Sets the application status to 'Ready'
    # Sets the generator page's error message 
    @pyqtSlot(str)
    def genSuccessStatus(self, error_msg):
        self.status.setStyleSheet("color: green")
        self.status.setText("Ready")
        self.errorMsg_lb.setStyleSheet("color: green")
        self.errorMsg_lb.setText(error_msg)
        QApplication.processEvents()
    
    # Ensures the waveform file line edit always ends in ".bin"
    # Has an issue because if you delete the period it just adds .bin to the end but leaves the bin
    def validateFileInput(self, text):
        if not text.endswith(".bin"):
            self.filename_le.setText(text.split(".")[0] + ".bin")

    # Checks the validity of line edit inputs          
    # Returns False and turns line edit red if inputs are not appropriate
    def selectedOptionsErrorChecking(self):
        successful_inputs = True
        for line_edit in [self.attenuation_le, self.filename_le]:
                # turn all pink line edits --> white
                line_edit.setStyleSheet("QLineEdit { background-color: white; }")
                # check for empty
                if (not line_edit.text().strip()):
                    line_edit.setStyleSheet("QLineEdit { background-color: pink; }")
                    successful_inputs = False
                if ((line_edit == self.attenuation_le)):
                    try: 
                        float(line_edit.text())
                    except Exception as e:
                        print("Error: ", e)
                        line_edit.setStyleSheet("QLineEdit { background-color: pink; }")
                        successful_inputs = False
        # filename needs to be longer than ".bin"
        if(len(self.filename_le.text()) < 5):
            self.filename_le.setStyleSheet("QLineEdit { background-color: pink; }")
            successful_inputs = False
        QApplication.processEvents()
        return successful_inputs    
    
    # Function called when the "Analyze" push button is clicked    
    # Analyzes the waveform file
    def analyzeButtonPress(self):
        try:
            self.genBusyStatus("Analyzing, please wait")         
            #self.checkSelectedOptions()

            if (not self.selectedOptionsErrorChecking()):
                self.genErrorStatus("Input error: please fill out all inputs with an appropriate value")
                return
            try:
                inputs_dict = {"source": self.source_cmb.currentText(), 
                        "filename": self.filename_le.text(),
                        "duplex": self.duplexMode_cmb.currentText(),
                        "units": self.units_cmb.currentText(),
                        "constellation": self.constellation_chb.isChecked(),
                        "correction": self.correction_chb.isChecked()
                }
            except Exception as e:
                print("Error: ", e)
                self.genErrorStatus("Input error: please fill out all inputs with appropriate values")
                return 
            self.analyze_pb.setCursor(QCursor(Qt.WaitCursor))
            
            # generate thread to open and run matlab functions
            self.matlab_thread = EvmThread(inputs_dict, self.eng)
            self.matlab_thread.success.connect(partial(self.matlabSuccess))
            self.matlab_thread.failure.connect(partial(self.genErrorStatus))
            self.matlab_thread.finished.connect(self.matlab_thread.deleteLater)
            self.matlab_thread.start()
        
        except Exception as e:
            print("Error: ", e)
            self.genErrorStatus("Error: Issue analyzing waveform")
            self.analyze_pb.setCursor(QCursor(Qt.ArrowCursor))
            return
    
    # Generates both EVM plots
    # Saves their HTML files and displays to GUI
    def generatePlots(self, params):
        if not os.path.exists('figures'):
            os.mkdir('figures')
        # resource block plot
        if (params['rb_x'] == 0):
            rb_df = pd.DataFrame({'RMS':params['rb_y_b'][0], 'Peak':params['rb_y_r'][0], '3GPP Limit': ([params['line_y'][0][0]] * len(params['rb_y_r'][0]))})
            fig = px.line(rb_df, y= ['RMS', 'Peak', '3GPP Limit'])
        else:
            #scatter = go.Scatter(x = params['rb_x'][0], y = [params['rb_y_b'][0],params['rb_y_r'][0]], mode = 'markers', name = 'scatter plot')
            rb_df = pd.DataFrame({'RMS':params['rb_y_b'][0], 'Peak':params['rb_y_r'][0], '3GPP Limit': ([params['line_y'][0][0]] * len(params['rb_y_r'][0])), 'x': params['rb_x'][0]})
            fig = px.line(rb_df, x = 'x', y= ['RMS', 'Peak', '3GPP Limit'])
        fig.update_layout(margin = dict(l=10, r=10, t=10, b=10))
        fig.update_layout(xaxis_title = "Resource Block Index", yaxis_title = "EVM (%)")
        fig.write_html('figures/rb_plot.html')

        test = pd.DataFrame({'RMS':params['rb_y_b'][0], 'Peak':params['rb_y_r'][0], '3GPP Limit': ([params['line_y'][0][0]] * len(params['rb_y_r'][0])), 'line': [params['line_y'][0][0]] * len(params['rb_y_r'][0])})
        #print("RMS LENGTH: ", len(test['RMS']))
        #print("PEAK LENGTH: ", len(test['Peak']))
        #print((test['Peak']))
        scatter = go.Scatter(y = test['RMS'], mode = 'lines+markers', name = 'RMS')
        scatter2 = go.Scatter(y = test['Peak'], mode = 'lines+markers', name = 'Peak')
        line = go.Scatter(y = test['line'], mode = 'lines', name = '3GPP Limit')
        fig = go.Figure()
        fig.add_trace(scatter)
        fig.add_trace(line)
        fig.add_trace(scatter2)
        fig.write_html('figures/combo_test_plot.html')

        # symbol plot
        #print("\n\n\n", params['symbol'][0], "\n\n\n")
        rms_df = pd.DataFrame({'CC2': params['symbol'][0], '3GPP Limit': ([params['symbol_y'][0][0]] * len(params['symbol'][0]))})
        fig = px.line(rms_df, y= ['CC2', '3GPP Limit'])
        fig.update_layout(margin = dict(l=10, r=10, t=10, b=10))
        fig.update_layout(xaxis_title = "Symbol Index", yaxis_title = "EVM (%)")
        fig.write_html('figures/rms_plot.html')

        # upload to the GUI
        file_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "figures/rb_plot.html"))
        self.resource_plot.load(QUrl.fromLocalFile(file_path))
        file_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "figures/rms_plot.html"))
        self.symbol_plot.load(QUrl.fromLocalFile(file_path))

    # Populates and resizes the table
    def populateTable(self, params):
        # table information
        self.table_tw.setRowCount(5)
        row = 0
        for row_title in ["Overall RMS (%)", "Overall Peak (%)", "Worst RB RMS (%)", "Worst Symbol RMS (%)", "Equalizer Fitness (dB)"]:
            self.table_tw.setItem(row, 0, QtWidgets.QTableWidgetItem(row_title))
            row += 1
        col = 0
        for key in params:
            if key.startswith('CC'):
                col += 1
                row = 0
                param_table_info = params[key]
                for value in param_table_info:
                    self.table_tw.setItem(row, col, QtWidgets.QTableWidgetItem(value))
                    row += 1
        # remove extra columns and resize table
        for column in range(8, 2, -1):
            self.table_tw.removeColumn(column) 
        self.table_tw.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        
    @pyqtSlot(str)
    def matlabSuccess(self, params):
        self.genBusyStatus("Populating table and graphs, please wait")
        self.populateTable(params)
        self.generatePlots(params)
        QApplication.processEvents()
        self.genSuccessStatus("The waveform was analyzed successfully")
        self.analyze_pb.setCursor(QCursor(Qt.ArrowCursor))
        
# Thread which runs the matlab functionalities
# Emits either a success or failure signal       
class EvmThread(QThread):
    failure = pyqtSignal(str)
    success = pyqtSignal(dict)

    def __init__(self, inputs_dict, eng):
        super().__init__()
        self.inputs_dict = inputs_dict
        self.eng = eng

    # automatically runs when thread is started
    def run(self):
        try:
            self.eng.addpath('matlab/evm')
            params = self.eng.AnalyzeButtonPushed(self.eng.struct(self.inputs_dict))
            self.success.emit(params)
        except Exception as e:
            print("Error: ", e)
            self.failure.emit("MATLAB Error: Matlab was unable to open")
            return 