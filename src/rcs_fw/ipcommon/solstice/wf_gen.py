from PyQt5.QtCore import Qt, QObject, QUrl, pyqtSignal, pyqtSlot, QThread
from PyQt5.QtWebEngineWidgets import QWebEngineView
from PyQt5.QtWidgets import QApplication
from PyQt5.QtGui import QCursor
from functools import partial
import plotly.express as px
from PyQt5 import QtWidgets
import matlab.engine
import pandas as pd
import os.path
import os 

# Generator Page Class
class GeneratorPage(QObject):

    def __init__(self, main_window):
        super().__init__()
        self.main_window = main_window
        self.eng = main_window.eng
        self.status = main_window.status
        self.initElements()

    # Finds and assigns objects of the UI file to attributes of the class
    def initElements(self):
        #views
        self.spectrum_plot = self.main_window.findChild(QWebEngineView, "gen_spectrumPlot_wv")
        self.time_plot = self.main_window.findChild(QWebEngineView, "gen_timePlot_wv")
        # push buttons
        self.genWF_pb = self.main_window.findChild(QtWidgets.QPushButton, "gen_genWF_pb")
        self.genWF_pb.clicked.connect(self.genWaveformButtonPress)
        # radio buttons
        self.NoC_button1 = self.main_window.findChild(QtWidgets.QRadioButton, "gen_NoC_1_rb")
        self.NoC_button2 = self.main_window.findChild(QtWidgets.QRadioButton, "gen_NoC_2_rb")
        self.NoC_button3 = self.main_window.findChild(QtWidgets.QRadioButton, "gen_NoC_3_rb")
        self.NoC_button4 = self.main_window.findChild(QtWidgets.QRadioButton, "gen_NoC_4_rb")
        self.NoC_button5 = self.main_window.findChild(QtWidgets.QRadioButton, "gen_NoC_5_rb")
        self.NoC_button6 = self.main_window.findChild(QtWidgets.QRadioButton, "gen_NoC_6_rb")
        self.NoC_button7 = self.main_window.findChild(QtWidgets.QRadioButton, "gen_NoC_7_rb")
        self.NoC_button8 = self.main_window.findChild(QtWidgets.QRadioButton, "gen_NoC_8_rb")
        # check box
        self.applyCFR_chb = self.main_window.findChild(QtWidgets.QCheckBox, "gen_applyCFR_chb")
        self.applyCFR_chb.stateChanged.connect(self.applyCFRChbStateChanged)
        self.levelScaledToAllocatedRBs_chb = self.main_window.findChild(QtWidgets.QCheckBox, "gen_levelScaled_chb")
        self.levelScaledToAllocatedRBs_chb.stateChanged.connect(self.levelScaledChbStateChanged)
        self.contiguous_chb = self.main_window.findChild(QtWidgets.QCheckBox, "gen_contiguous_chb")
        self.contiguous_chb.stateChanged.connect(self.contiguousChbStateChanged)
        self.windowing_chb = self.main_window.findChild(QtWidgets.QCheckBox, "gen_windowing_chb")
        self.windowing_chb.stateChanged.connect(self.windowingChbStateChanged)
        self.autoLength_chb = self.main_window.findChild(QtWidgets.QCheckBox, "gen_autoLength_chb")
        self.autoLength_chb.stateChanged.connect(self.autoLengthChbStateChanged)
        self.channelFilter_chb = self.main_window.findChild(QtWidgets.QCheckBox, "gen_channelFilter_chb")
        # label
        self.errorMsg_lb = self.main_window.findChild(QtWidgets.QLabel, "gen_errorMsg_lb")
        self.centerFreq_lb = self.main_window.findChild(QtWidgets.QLabel, "gen_centerFreq_lb")
        self.windowing_lb = self.main_window.findChild(QtWidgets.QLabel, "gen_windowing_lb")
        self.targetPAPR_lb = self.main_window.findChild(QtWidgets.QLabel, "gen_PAPR_lb")
        self.threshold_lb = self.main_window.findChild(QtWidgets.QLabel, "gen_threshold_lb")
        self.fullRBLevel_lb = self.main_window.findChild(QtWidgets.QLabel, "gen_fullRBLevel_lb")
        self.signalLevel_lb = self.main_window.findChild(QtWidgets.QLabel, "gen_signalLevel_lb")
        # frames/layouts
        self.NR_WF_frame = self.main_window.findChild(QtWidgets.QFrame, "gen_NRWf_frame")
        self.NoC_layout = self.main_window.findChild(QtWidgets.QHBoxLayout, "gen_NoC_layout")
        self.BW_frame = self.main_window.findChild(QtWidgets.QFrame, "gen_BW_frame")
        self.SCS_frame = self.main_window.findChild(QtWidgets.QFrame, "gen_SCS_frame")
        self.NoC_layout1 = self.main_window.findChild(QtWidgets.QVBoxLayout, "gen_NoC_layout1")
        self.NoC_layout2 = self.main_window.findChild(QtWidgets.QVBoxLayout, "gen_NoC_layout2")
        # line edits
        self.centerFreq_le = self.main_window.findChild(QtWidgets.QLineEdit, "gen_centerFreq_le")
        self.signalLevel_le = self.main_window.findChild(QtWidgets.QLineEdit, "gen_signalLevel_le")
        self.targetPAPR_le = self.main_window.findChild(QtWidgets.QLineEdit, "gen_PAPR_le")
        self.fullRBLevel_le = self.main_window.findChild(QtWidgets.QLineEdit, "gen_fullRBLevel_le")
        self.threshold_le = self.main_window.findChild(QtWidgets.QLineEdit, "gen_threshold_le")
        self.filename_le = self.main_window.findChild(QtWidgets.QLineEdit, "gen_wfFile_le")
        self.filename_le.textChanged.connect(self.validateWaveformFileInput)
        self.windowing_le = self.main_window.findChild(QtWidgets.QLineEdit, "gen_WaF_windowing_le")
        # combo box
        self.duplexMode_cmb = self.main_window.findChild(QtWidgets.QComboBox, "gen_duplexMode_cmb")
        self.specification_cmb = self.main_window.findChild(QtWidgets.QComboBox, "gen_specification_cmb")
        self.specification_cmb.currentTextChanged.connect(self.specificationCmbStateChanged)
        self.filterStyle_cmb = self.main_window.findChild(QtWidgets.QComboBox, "gen_filterStyle_cmb")
        # table widget
        self.parameterValue_tw = self.main_window.findChild(QtWidgets.QTableWidget, "gen_parameterValue_tw")
        self.parameterValue_tw.setHorizontalHeaderLabels(["Parameter", "Value"])

    # Ensures one of the radio button options on the WF Generation Page has been selected
    # Assigns the selected options/inputs to variables of the class
    def identifySelectedRadioButtons(self):
        self.NRWF_input = None
        self.NoC_input = None
        self.BW_input = None
        self.SCS_input = None
        for button in self.NR_WF_frame.findChildren(QtWidgets.QRadioButton):
            if(button.isChecked()):
                self.NRWF_input = button.objectName()
                break
        for button in [self.NoC_button1, self.NoC_button2, self.NoC_button3, self.NoC_button4, self.NoC_button5, self.NoC_button6, self.NoC_button7, self.NoC_button8]:
            if (button.isChecked()):
                self.NoC_input = button.objectName()
                break
        for button in self.BW_frame.findChildren(QtWidgets.QRadioButton):
            if(button.isChecked()):
                self.BW_input = button.objectName()
                break    
        for button in self.SCS_frame.findChildren(QtWidgets.QRadioButton):
            if(button.isChecked()):
                self.SCS_input = button.objectName()
                break 

    # Checks the validity of line edit inputs          
    # Returns False and turns line edit red if inputs are not appropriate
    def inputErrorChecking(self):
        successful_inputs = True
        for line_edit in [self.targetPAPR_le, self.signalLevel_le, self.centerFreq_le, self.fullRBLevel_le, self.threshold_le, self.filename_le, self.windowing_le]:
                # turn all pink line edits --> white
                line_edit.setStyleSheet("QLineEdit { background-color: white; }")
                # check for empty
                if (not line_edit.text().strip()):
                    line_edit.setStyleSheet("QLineEdit { background-color: pink; }")
                    successful_inputs = False
                if ((line_edit != self.filename_le) and (line_edit != self.centerFreq_le)):
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

    # Ensures the waveform file line edit always ends in ".bin"
    # Has an issue because if you delete the period it just adds .bin to the end but leaves the bin
    def validateWaveformFileInput(self, text):
        if not text.endswith(".bin"):
            self.filename_le.setText(text.split(".")[0] + ".bin")

    # Event handlers for checkbox selects/combobox changes
    # Disables/enables certain inputs depending on selected checkbox/combobox 
    def contiguousChbStateChanged(self):
        if self.contiguous_chb.isChecked():
            self.centerFreq_le.setEnabled(False)
            self.centerFreq_lb.setEnabled(False)
        else:
            self.centerFreq_le.setEnabled(True)
            self.centerFreq_lb.setEnabled(True)
    def windowingChbStateChanged(self):
        if self.windowing_chb.isChecked():
            self.autoLength_chb.setEnabled(True)
            self.autoLengthChbStateChanged()
        else:
            self.autoLength_chb.setEnabled(False)
            self.windowing_le.setEnabled(False)
            self.windowing_lb.setEnabled(False)
    def autoLengthChbStateChanged(self):
        if self.autoLength_chb.isChecked():
            self.windowing_le.setEnabled(False)
            self.windowing_lb.setEnabled(False)
        else:
            self.windowing_le.setEnabled(True)
            self.windowing_lb.setEnabled(True)
    def applyCFRChbStateChanged(self):
        if self.applyCFR_chb.isChecked():
            self.targetPAPR_le.setEnabled(True)
            self.targetPAPR_lb.setEnabled(True)
        else:
            self.targetPAPR_le.setEnabled(False)
            self.targetPAPR_lb.setEnabled(False)
    def specificationCmbStateChanged(self):
        if (self.specification_cmb.currentText() == "Relative"):
            self.threshold_lb.setEnabled(False)
            self.threshold_le.setEnabled(False)
            self.targetPAPR_lb.setEnabled(True)
            self.targetPAPR_le.setEnabled(True)
        else:
            self.threshold_lb.setEnabled(True)
            self.threshold_le.setEnabled(True)
            self.targetPAPR_lb.setEnabled(False)
            self.targetPAPR_le.setEnabled(False)
    def levelScaledChbStateChanged(self):
        if self.levelScaledToAllocatedRBs_chb.isChecked():
            self.fullRBLevel_lb.setEnabled(True)
            self.fullRBLevel_le.setEnabled(True)
            self.signalLevel_lb.setEnabled(False)
            self.signalLevel_le.setEnabled(False)
        else:
            self.fullRBLevel_lb.setEnabled(False)
            self.fullRBLevel_le.setEnabled(False)
            self.signalLevel_lb.setEnabled(True)
            self.signalLevel_le.setEnabled(True)

    # Sets the application status to 'Errored'
    # Sets the generator page's error message 
    @pyqtSlot(str)
    def genErrorStatus(self, error_msg):
        self.status.setStyleSheet("color: red")
        self.status.setText("Errored")
        self.errorMsg_lb.setStyleSheet("color: red")
        self.errorMsg_lb.setText(error_msg)
        QApplication.processEvents()

    # Sets the application status to 'Busy'
    # Sets the generator page's error message 
    def genBusyStatus(self, error_msg):
        self.status.setStyleSheet("color: blue")
        self.status.setText("Busy")
        self.errorMsg_lb.setStyleSheet("color: blue")
        self.errorMsg_lb.setText(error_msg)
        QApplication.processEvents()

    # Sets the application status to 'Busy'
    # Sets the generator page's error message 
    def genSuccessStatus(self, error_msg):
        self.status.setStyleSheet("color: green")
        self.status.setText("Ready")
        self.errorMsg_lb.setStyleSheet("color: green")
        self.errorMsg_lb.setText(error_msg)
        QApplication.processEvents()

    # Fills out the parameter/value table
    def populateTable(self, params):
        # table information
        param_table_titles = ["Waveform", "Duplex Mode", "Slots", "Duty Cycle", "BW (MHz)", "SCS (kHz)", "Carriers", "Rate (MHz)", "PAPR 99.9%", "PAPR 99.99%", "PAPR 100%", "Power (dBFS)"]
        param_table_info = [params['nrtm'], params['duplex'], str(int(params['numSlot'])), "Duty", str(int(params['bw']/1E6)), str(int(params['scs']/1E3)), str(int(params['numCar'])), "1966.08", str(round(params['papr999'], 4)), str(round(params['papr9999'], 4)), str(round(params['papr100'], 4)), str(round(params['level'], 0))]
        row = 0
        self.parameterValue_tw.setRowCount(12)
        for idx, value in enumerate(param_table_titles):
            self.parameterValue_tw.setItem(row, 0, QtWidgets.QTableWidgetItem(value))
            self.parameterValue_tw.setItem(row, 1, QtWidgets.QTableWidgetItem(param_table_info[idx]))
            row += 1
    
    # Generates and uploads the plots to the UI
    def generatePlots(self, params): 
        if not os.path.exists('figures'):
            os.mkdir('figures')
        # power spectrum plot
        spectrum_df = pd.DataFrame({'Frequency (MHz)': params['spectrum_x'][0], 'Power (dB)':params['spectrum_y'][0]})
        fig = px.line(spectrum_df, x='Frequency (MHz)', y='Power (dB)')
        fig.update_layout(margin = dict(l=10, r=10, t=10, b=10))
        fig.write_html('figures/spectrum_plot.html')

        # time domain plot
        time_df = pd.DataFrame({'Time (ms)': params['time_x'][0], 'y':params['time_y'][0]})
        fig = px.line(time_df, x='Time (ms)', y='y')
        fig.update_layout(margin = dict(l=10, r=10, t=10, b=10))
        fig.write_html('figures/time_plot.html')
        
        # upload to the GUI
        file_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "figures/spectrum_plot.html"))
        self.spectrum_plot.load(QUrl.fromLocalFile(file_path))
        file_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "figures/time_plot.html"))
        self.time_plot.load(QUrl.fromLocalFile(file_path))

    # Function called when the "Generate Waveform" push button is clicked    
    # Generates the waveform file 
    def genWaveformButtonPress(self):
        try:
            self.genBusyStatus("Generating waveform, please wait")   

            # error checking inputs   
            self.identifySelectedRadioButtons()
            if (not self.inputErrorChecking()):
                self.genErrorStatus("Input error: please fill out all inputs with an appropriate value")
                return

            # preparing matlab function input
            try:
                inputs_dict = {"NRWF": self.NRWF_input, 
                        "BW": self.BW_input, 
                        "SCS": self.SCS_input, 
                        "NoC":self.NoC_input,
                        "duplex_mode":self.duplexMode_cmb.currentText(), 
                        "specification":self.specification_cmb.currentText(),
                        "filter_style": self.filterStyle_cmb.currentText(),
                        "apply_CFR": self.applyCFR_chb.isChecked(), 
                        "level_scaled_to_allocated_RBs": self.levelScaledToAllocatedRBs_chb.isChecked(),
                        "contiguous": self.contiguous_chb.isChecked(),
                        "windowing": self.windowing_chb.isChecked(),
                        "auto_length": self.autoLength_chb.isChecked(),
                        "channel_filter": self.channelFilter_chb.isChecked(),
                        "signal_level": float(self.signalLevel_le.text()),
                        "target_PAPR": float(self.targetPAPR_le.text()),
                        "center_freq":self.centerFreq_le.text(),
                        "full_RB_level": float(self.fullRBLevel_le.text()),
                        "threshold_BFS":float(self.threshold_le.text()),
                        "filename":self.filename_le.text(),
                        "windowing_le": float(self.windowing_le.text())
                }
            except Exception as e:
                print("Error: ", e)
                self.genErrorStatus("Input error: please fill out all inputs with appropriate values")
                return 
            self.genWF_pb.setCursor(QCursor(Qt.WaitCursor))
            
            # generate thread to open and run matlab functions
            self.matlab_thread = GenWfThread(inputs_dict, self.eng)
            self.matlab_thread.success.connect(partial(self.matlabSuccess))
            self.matlab_thread.failure.connect(partial(self.genErrorStatus))
            self.matlab_thread.finished.connect(self.matlab_thread.deleteLater)
            self.matlab_thread.start()
        
        except Exception as e:
            print("Error: ", e)
            self.genErrorStatus("Error: Issue generating waveform")
            return
    
    @pyqtSlot(str)
    def matlabSuccess(self, params):
        self.genBusyStatus("Populating table and graphs, please wait")
        self.populateTable(params)
        self.generatePlots(params)
        QApplication.processEvents()
        self.genSuccessStatus("The waveform was generated successfully")
        self.genWF_pb.setCursor(QCursor(Qt.ArrowCursor))

# Thread which runs the matlab functionalities
# Emits either a success or failure signal
class GenWfThread(QThread):
    # signals
    failure = pyqtSignal(str) # signal to emit if matlab functionality fails
    success = pyqtSignal(dict) # signal to emit if matlab functionality succeeds

    def __init__(self, inputs_dict, eng):
        super().__init__()
        self.inputs_dict = inputs_dict
        self.eng = eng

    # automatically runs when thread is started
    def run(self):
        try:
            self.eng.addpath('matlab/generator')
            params = self.eng.genButton(self.eng.struct(self.inputs_dict))
            self.success.emit(params)
        except Exception as e:
            print("Error: ", e)
            self.failure.emit("MATLAB Error: Matlab was unable to open")
            return 