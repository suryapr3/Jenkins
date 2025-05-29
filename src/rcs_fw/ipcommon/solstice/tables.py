import os
import json
import argparse
import csv

# Tables Class
class Tables():
    def __init__(self):
        self.table_dict = {}
        self.info_dict = {}

#Searches recursively for a CSV file by name within a given directory path and returns the full path if found.
    def findCsvFile(self, name, path):
        for root, dirs, files in os.walk(path):
            if name in files:
                return os.path.join(root, name)

#Retrieves all CSV files in a directory (and its subdirectories) that do not start with "address_size", returning a list of their paths.
    def getAllCsvFiles(self, path):
        csv_files = []
        for root, dirs, files in os.walk(path):
            for file in files:
                if file.endswith(".csv") and not file.split("\\")[-1].startswith("address_size"):
                    csv_files.append(os.path.join(root, file))
        return csv_files

    def parseCsvFile(self, csv_file):
        with open(csv_file, mode='r') as file:
            csv_reader = csv.reader(file)
            parsed_data = {}
            bit_field_entries = []
            count = 0
            data_rows = []
            for row in csv_reader:
                # Remove empty strings from row
                row = [item for item in row if item != ""]
                if row:
                    title = row[0]
                    # Directly store single-entry values
                    if title in ["Table Name", "Category", "Subcategory"]:
                        parsed_data[title] = row[1] if len(row) > 1 else None
                    elif title == "Bit Field Name":
                        bit_field_entries.extend(row[1:])  # Ignore the title and store the rest
                        parsed_data["Bit Field Name"] = bit_field_entries
            return parsed_data

#creates data_array for tables with only one bit field name
    def processCsvRow(self, row, parse_dict, data_rows, all_data, subDim, count, index, all_indexes_flat, csv_file):
        if not self.found:
            if row and row[0] == "subtable dimension and name":
                subDim = self.subDim(parse_dict, row)
                self.found = True
        else:       
            asterisk_found = False
            for i, cell in enumerate(row):
                if '*' in cell:
                    filtered_data = {}
                    count += 1
                    index = 0
                    key = subDim
                    filtered_data[key] = data_rows 
                    table_dict = {**parse_dict, **filtered_data}
                    all_data[subDim] = table_dict
                    data_rows = []
                    parse_dict = self.parseCsvFile(csv_file)
                    asterisk_found = True
                    subDim = self.subDim(parse_dict, row)
                    break
            if not asterisk_found:
                filtered_row = [row[idx] for idx in all_indexes_flat if idx < len(row) and row[idx]]
                data_tuple = (index, filtered_row)
                data_rows.append(data_tuple)
                index += 1
        return parse_dict, data_rows, all_data, subDim, count, index

#Creates the data structure
    def createFile(self):
        csv_files = self.getAllCsvFiles("fw/tables/csv") 
        all_data = {}
        for csv_file in csv_files:
            filename = os.path.basename(csv_file)  
            file_base_name = filename.split('.')[0]  
            parse_dict = self.parseCsvFile(csv_file)          
            data_rows = []; all_indexes = []; subtable_counter = 0; current_subtable_key = None; self.found = False; index = 0; count = 0; subDim = None; bitFieldNamecount = 0
            with open(csv_file, mode='r') as file:
                csv_reader = csv.reader(file)               
                for row in csv_reader:
                    if row and row[0] == "Bit Field Name":
                        indexes = [index for index, value in enumerate(row) if value and index > 0]
                        all_indexes.append(indexes)
                        bitFieldNamecount += 1
            if bitFieldNamecount == 1:
                all_indexes_flat = [idx for sublist in all_indexes for idx in sublist]  # Flatten the list if needed
                with open(csv_file, mode='r') as file:
                    csv_reader = csv.reader(file)
                    for row in csv_reader:
                        parse_dict, data_rows, all_data, subDim, count, index = self.processCsvRow(
                            row, parse_dict, data_rows, all_data, subDim, count, index, all_indexes_flat, csv_file)
                filtered_data = {}
                filtered_data[subDim] = data_rows
                table_dict = {**parse_dict, **filtered_data}
                if count > 0:
                    all_data[subDim] = table_dict
                elif count == 0:
                    all_data[file_base_name] = table_dict
            else:
                all_data = self.multipleBitFieldNames(csv_file, all_data, file_base_name)
        # After all files have been processed, write all_data to a JSON file
        with open('fw/tables/csv/structured/all_data_structured.json', 'w') as f: #('../../tempdir/structured/all_data_structured.json', 'w')
            json.dump(all_data, f, indent=4)  # Pretty print the JSON

#Accounts for 2D csv files
    def multipleBitFieldNames(self, csv_file, all_data, file_base_name):
        indexes = []; all_indexes = []; data_row=[]; found_subdim = False; row_counter = 0; numberOfSubDims= 0; subDim = ""; flag = True
        with open(csv_file, mode='r') as file:
            csv_reader = csv.reader(file)
            for row in csv_reader:
                if row and row[0] == "single entry bitwidth":
                    bitwidth_string = row[1]  # Adjust the index if necessary
                    rowsPerIndex = bitwidth_string.split('*')[1] 
            # If Bit Field Name only comes up once
                if row and row[0] == "Bit Field Name":
                    indexes = [index for index, value in enumerate(row) if value and index > 0]
                    all_indexes.append(indexes)
        with open(csv_file, mode='r') as file:
            csv_reader = csv.reader(file)
            for row in csv_reader:
                if not found_subdim:
                    # Check if the current row starts with "subDim"
                    if row and row[0] == "subtable dimension and name":
                        parse_dict = self.parseCsvFile(csv_file)
                        subDim = self.subDim(parse_dict, row)
                        found_subdim = True
                else:
                    flag = True
                    for i, cell in enumerate(row):
                        if '*' in cell:
                            numberOfSubDims+=1
                            parse_dict = self.parseCsvFile(csv_file)                              
                            filtered_data = self.print_data_values(all_indexes, data_row, rowsPerIndex, parse_dict, subDim)
                            table_dict = {**parse_dict, **filtered_data}
                            all_data[subDim] = table_dict
                            subDim = self.subDim(parse_dict, row)
                            data_row = []
                            flag = False
                    if flag == True:
                        data_row.append(row)              
        parse_dict = self.parseCsvFile(csv_file) #Get all info except data
        filtered_data = self.print_data_values(all_indexes, data_row, rowsPerIndex, parse_dict, subDim) #Get dictionary with key sub dim and value array
        table_dict = {**parse_dict, **filtered_data}
        if numberOfSubDims == 0:
            all_data[file_base_name] = table_dict
        if numberOfSubDims > 0:
            all_data[subDim] = table_dict

        return all_data

#Formats the data array when multiple bit field names are used
    def print_data_values(self, bitFieldNamearray, data_row, rowsPerIndex, parse_dict, subDim):
        filtered_data = []
        new_data = []
        index_array_length = len(bitFieldNamearray)
        data_index = 0
        index = 0
        count = 0
        rowsPerIndex = int(rowsPerIndex)
        new_dict = {}
        for i, data in enumerate(data_row):
            indices = bitFieldNamearray[i % index_array_length]
            filtered_subarray = [data[j] for j in indices]
            filtered_data.append(filtered_subarray)

        for index, ind in enumerate(range(0, len(filtered_data), rowsPerIndex)):
            # Combine the mini arrays in the current group
            combined_array = [item for sublist in filtered_data[ind:ind + rowsPerIndex] for item in sublist]
            new_data.append((index, combined_array))
        new_dict[subDim] = new_data
        return new_dict

#Finds the subDim in the row
    def subDim(self, parse_dict, row):
        self.table_dict = parse_dict
        asterisk_index=str(row[0]).find('*')
        target_index = asterisk_index + 4
        if asterisk_index + 4 < len(row):
            subDim = row[target_index]
        return subDim

#Combines parsing, dictionary restructuring, and cleaning operations to prepare a CSV file's data for use or output, updating the class's dictionaries accordingly.
    def createTableDicts(self, csv_file):
        self.table_dict = self.parseCsvFile(csv_file)

#Formats and writes the processed data from `table_dict` to a text file, structuring each bit field as a separate line with its corresponding values.
    def writeTableTxtFiles(self, file_path):
        with open(file_path, 'w') as file:
            table_name = self.info_dict["Table Name"]
            for bf_index, bf in enumerate(self.table_dict["Bit Field Name"]):
                bf_data = [self.table_dict[row][bf_index] for row in self.table_dict if row != "Bit Field Name"]
                file.write(f"{table_name}.{bf} = {{{','.join(bf_data)}}}\n")

 
tables1 = Tables()
tables1.createFile()