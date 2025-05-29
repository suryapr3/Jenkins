import os
import re
import shutil
import logging
import time
from template import *

# Get the current timestamp
timestamp = time.strftime("%Y_%m_%d_%H-%M")

#To create log of the process
log_directory = os.path.join(os.getcwd(), 'log')
if not os.path.exists(log_directory):
    os.makedirs(log_directory, exist_ok=True)

log_filename = f"logfile_.log_" + timestamp
log_file_path = os.path.join(log_directory, log_filename)

try:
    # Attempt to create and write to the log file
    with open(log_file_path, 'w') as logfile:
        logfile.write("Log file content.")
    print("Log file created successfully.")
except Exception as e:
    print("Error:", e)

logging.basicConfig(filename=log_file_path, level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

#Main Class
class Main():
    def __init__(self):
        self.offset = []
        self.default = []
        self.read_mask = []
        self.wr_mask = []
        self.base = []
        self.block = ""
        self.block1 = ""
    #function to read the header file and generate the list for base_address, offset_address, read_mask_address, wr_mask_address
    def read(self, file_path, h_filename):
        try:
            self.block1 = h_filename.strip('.h')
            self.block = h_filename.upper().strip('.H')
            with open(file_path, 'r', encoding='latin-1') as f:
                content = f.read().splitlines()
                for i in content:
                    if i.__contains__('0x'):
                        match = re.findall(r'.*_OFFSET\s*\(\s*0x.*\s*\)', i)
                        match1 = re.findall(r'.*_DEFAULT', i)
                        match2 = re.findall(r'.*_RD_MASK', i)
                        match3 = re.findall(r'.*_WR_MASK', i)
                        match4 = re.findall(r'.*_BASE\s*\(\s*0x.*\s*\)', i)
                        for i in match:
                            if i != '':
                                data = i.strip('#define').split('(')[0].strip()
                                self.offset.append(data)
                        for i in match1:
                            if i != '':
                                data = i.strip('#define').strip()
                                self.default.append(data)
                        for i in match2:
                            if i != '':
                                data = i.strip('#define').strip()
                                self.read_mask.append(data)
                        for i in match3:
                            if i != '':
                                data = i.strip('#define').strip()
                                self.wr_mask.append(data)
                        for i in match4:
                            if i != '':
                                data = i.strip('#define').split()[0].strip()
                                if data not in self.base:
                                    self.base.append(data)
            logging.info(f'Reading {h_filename}')
            print(f'============= Reading {h_filename} ==========================')
        except Exception as e:
            logging.error(f'error reading {h_filename}')


    def write_c_file(self, c_filename_path, mode):
        try:
            self.address_list = []
            # Helper function to filter out numerical characters and underscores from the address
            def remove_suffix(address):
                return address.replace('_OFFSET', '').replace('_DEFAULT', '').replace('_RD_MASK', '').replace('_WR_MASK', '')

            #function for partial match between offset and default,read,write mask addresses
            def partial_match(offset, address):
                # Function to split the string into segments of letters and numbers
                def split_alpha_num(s):
                    return re.findall(r'[A-Za-z]+|\d+', s)

                # Remove suffixes and split into segments
                offset_segments = split_alpha_num(remove_suffix(offset))
                address_segments = split_alpha_num(remove_suffix(address))

                # Check if the address segments are found in the offset segments in order
                offset_index = 0
                for segment in address_segments:
                    # Try to find the current segment in the remaining offset segments
                    found = False
                    while offset_index < len(offset_segments):
                        if segment.isdigit():
                            # If the segment is a number, match only if the whole segment matches
                            if offset_segments[offset_index] == segment:
                                found = True
                                break
                        else:
                            # If the segment is not a number, match if the offset segment starts with the address segment
                            if offset_segments[offset_index].startswith(segment):
                                found = True
                                break
                        offset_index += 1
                    if not found:
                        return False
                    offset_index += 1

                return True


            def remove_trailing_digits(word):
                return re.sub(r'(\D+)\d*$', r'\1', word)


            def remove_trailing_digits_from_words(text):
                words = remove_suffix(text).split('_')
                cleaned_words = [remove_trailing_digits(word) for word in words]
                return '_'.join(cleaned_words)


            def remove_pattern_from_offset(offset, regex_pattern):
                offset = remove_suffix(offset)
                new_offset = re.sub(regex_pattern, '', offset)
                return new_offset

            for offset_address in self.offset:
                pattern = r'.REG\d+'
                comp_offset_address = offset_address.replace('_OFFSET', '')
                comp_offset_address1 = remove_trailing_digits_from_words(offset_address)
                comp_offset_address2 = remove_pattern_from_offset(offset_address, pattern)
                matching_default = None
                matching_read_mask = None
                matching_wr_mask = None

                # Exact match without suffix
                for default_address in self.default:
                    comp_default_address = default_address.replace('_DEFAULT', '')
                    if comp_offset_address == comp_default_address:
                        matching_default = default_address
                        break
                    elif '_REG' in default_address:
                        comp_default_address = default_address.replace('_REG_DEFAULT', '')
                        if comp_offset_address == comp_default_address:
                            matching_default = default_address
                            break

                    elif '_REG_OFFSET' in default_address:
                        comp_default_address = default_address.replace('_REG_OFFSET_DEFAULT', '')
                        if comp_offset_address == comp_default_address:
                            matching_default = default_address
                            break

                    else:
                        if comp_offset_address1 == comp_default_address:
                            matching_default = default_address
                            break

                # Exact match without suffix for read_mask addresses
                for read_mask_address in self.read_mask:
                    comp_read_mask_address = read_mask_address.replace('_RD_MASK', '')
                    if comp_offset_address == comp_read_mask_address:
                        matching_read_mask = read_mask_address
                        break

                    elif '_REG' in read_mask_address:
                        comp_read_mask_address = read_mask_address.replace('_REG_RD_MASK', '')
                        if comp_offset_address == comp_read_mask_address:
                            matching_read_mask = read_mask_address
                            break
                    elif '_REG_OFFSET' in read_mask_address:
                        comp_read_mask_address = read_mask_address.replace('_REG_OFFSET_RD_MASK', '')
                        if comp_offset_address == comp_read_mask_address:
                            matching_read_mask = read_mask_address
                            break

                    else:
                        if comp_offset_address1 == comp_read_mask_address:
                            matching_read_mask = read_mask_address
                            break

                # Exact match without suffix for wr_mask addresses
                for wr_mask_address in self.wr_mask:
                    comp_wr_mask_address = wr_mask_address.replace('_WR_MASK', '')
                    if comp_offset_address == comp_wr_mask_address:
                        matching_wr_mask = wr_mask_address
                        break

                    elif '_REG' in wr_mask_address:
                        comp_wr_mask_address = wr_mask_address.replace('_REG_WR_MASK', '')
                        if comp_offset_address == comp_wr_mask_address:
                            matching_wr_mask = wr_mask_address
                            break
                    elif '_REG_OFFSET' in wr_mask_address:
                        comp_wr_mask_address = wr_mask_address.replace('_REG_OFFSET_WR_MASK', '')
                        if comp_offset_address == comp_wr_mask_address:
                            matching_wr_mask = wr_mask_address
                            break

                    else:
                        if comp_offset_address1 == comp_wr_mask_address:
                            matching_wr_mask = wr_mask_address
                            break


                if not matching_default:
                    for default_address in self.default:
                        comp_default_address = remove_suffix(default_address)
                        if comp_offset_address2 == comp_default_address:
                            matching_default = default_address
                            break

                if not matching_read_mask:
                    for read_mask_address in self.read_mask:
                        comp_read_mask_address = remove_suffix(read_mask_address)
                        if comp_offset_address2 == comp_read_mask_address:
                            matching_read_mask = read_mask_address
                            break

                if not matching_wr_mask:
                    for wr_mask_address in self.wr_mask:
                        comp_wr_mask_address = remove_suffix(wr_mask_address)
                        if comp_offset_address2 == comp_wr_mask_address:
                            matching_wr_mask = wr_mask_address
                            break

                #To check for minimum character match between offset, default, read, write
                if not matching_default:
                    for default_address in self.default:
                        if partial_match(offset_address, default_address):
                            matching_default = default_address
                            break

                if not matching_read_mask:
                    for read_mask_address in self.read_mask:
                        if partial_match(offset_address, read_mask_address):
                                    matching_read_mask = read_mask_address
                                    break

                if not matching_wr_mask:
                    for wr_mask_address in self.wr_mask:
                        if partial_match(offset_address, wr_mask_address):
                            matching_wr_mask = wr_mask_address
                            break

                #Adding match address to list of dictionary
                if matching_default and matching_read_mask and matching_wr_mask:
                    address_dict = {
                        'offset': offset_address,
                        'default': matching_default,
                        'read_mask': matching_read_mask,
                        'wr_mask': matching_wr_mask
                    }

                    self.address_list.append(address_dict)

            if mode == 'register_default':
                if(len(self.base)>1):
                    for_loop = '    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)\n    {' #Loop to access base_address elements
                    logging.info(f'updating the {self.block1} c file')
                    self.update_file(c_filename_path, License_template) #Intel License Template from template folder to add in c code
                    self.update_file(c_filename_path, Template) #Template from template folder to add in c code
                    self.update_file(c_filename_path, Template2) #Template from template folder to add in c code
                    self.update_file(c_filename_path, self.address_array(self.base))#adding base_address array in c code
                    self.update_file(c_filename_path, for_loop) # adding for loop in c code

                    for i in self.address_list:
                        self.update_file(c_filename_path, f'''        read_reg_expect_18a(base_address[i]+{i["offset"]}, \\
                                    {i["default"]}, \\
                                    {i["read_mask"]}, "{i["offset"]}");\n''')

                    self.update_file(c_filename_path, '    }\n')
                    self.update_file(c_filename_path, '}')
                else:
                    for_loop = '    for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)\n    {' #Loop to access base_address elements
                    logging.info(f'updating the {self.block1} c file')
                    self.update_file(c_filename_path, License_template) #Intel License Template from template folder to add in c code
                    self.update_file(c_filename_path, Template) #Template from template folder to add in c code
                    self.update_file(c_filename_path, Template2) #Template from template folder to add in c code
                    self.update_file(c_filename_path, self.address_array(self.base))#adding base_address array in c code
                    self.update_file(c_filename_path, for_loop) # adding for loop in c code

                    for i in self.address_list:
                        self.update_file(c_filename_path, f'''        read_reg_expect_18a(base_address[i]+{i["offset"]}, \\
                                    {i["default"]}, \\
                                    {i["read_mask"]}, "{i["offset"]}");\n''')

                    self.update_file(c_filename_path, '    }\n')
                    self.update_file(c_filename_path, '}')

            elif mode == 'write_read':
                if(len(self.base) > 1):
                    for_loop = '        for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)\n        {' #Loop to access base_address elements
                    logging.info(f'updating the {self.block1} c file')
                    self.update_file(c_filename_path, License_template) #Intel License Template from template folder to add in c code
                    self.update_file(c_filename_path, Template)#Template from template folder to add in c code
                    self.update_file(c_filename_path, TemplateForReadWriteOnly) #Template from template folder to add in c code
                    self.update_file(c_filename_path, Template3_write_read) #Template from template folder to add in c code
                    self.update_file(c_filename_path, self.address_array(self.base))#adding base_address array in c code
                    self.update_file(c_filename_path, Template_for_loop)#adding for loop of template in c code
                    self.update_file(c_filename_path, for_loop) # adding for loop in c code
                    for i in self.address_list:
                        self.update_file(c_filename_path, f'''            write_read_expect_18a(base_address[i]+{i["offset"]}, \\
                                    {i["default"]}, write_data, expected_data, \\
                                    {i["read_mask"]}, {i["wr_mask"]}, \\
                                    "{i["offset"]}");\n''')

                    self.update_file(c_filename_path, '        }\n')
                    self.update_file(c_filename_path, '    }\n')
                    self.update_file(c_filename_path, '}')
                else:
                    for_loop = '        for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)\n        {' #Loop to access base_address elements
                    logging.info(f'updating the {self.block1} c file')
                    self.update_file(c_filename_path, License_template) #Intel License Template from template folder to add in c code
                    self.update_file(c_filename_path, Template)#Template from template folder to add in c code
                    self.update_file(c_filename_path, TemplateForReadWriteOnly) #Template from template folder to add in c code
                    self.update_file(c_filename_path, Template3_write_read) #Template from template folder to add in c code
                    self.update_file(c_filename_path, self.address_array(self.base))#adding base_address array in c code
                    self.update_file(c_filename_path, Template_for_loop)#adding for loop of template in c code
                    self.update_file(c_filename_path, for_loop) # adding for loop in c code
                    for i in self.address_list:
                        self.update_file(c_filename_path, f'''            write_read_expect_18a(base_address[i]+{i["offset"]}, \\
                                    {i["default"]}, write_data, expected_data, \\
                                    {i["read_mask"]}, {i["wr_mask"]}, \\
                                    "{i["offset"]}");\n''')

                    self.update_file(c_filename_path, '        }\n')
                    self.update_file(c_filename_path, '    }\n')
                    self.update_file(c_filename_path, '}')
        except Exception as e:
            logging.error(f'Error handling {c_filename_path}: {e}')


    #function to update the c file with required content
    def update_file(self, filepath, content):
        with open(filepath, 'a') as f:
            f.write(content)
            f.write('\n')

    #function to create respective c file as per header file
    def create_cfile(self, c_filename_path):
        with open(c_filename_path, 'w') as f:
            pass

    #function to add base address array in C file
    def address_array(self, base_address_list):
        c_code =""
        c_code += "    uint32_t base_address[] = {\n    "
        for i, macro in enumerate(base_address_list):
            c_code += "" +macro
            if (i + 1) % 5 == 0 and i != len(base_address_list) - 1:
                c_code += ",\n    "
            elif i != len(base_address_list) - 1:
                c_code += ", "
            else:
                c_code += "\n"
        c_code += "    };\n"
        return c_code

def process_header_file(header_file):

    #Declaring the object for the Main class
    obj = Main()

    #Creating the path for header file
    h_filepath = os.path.join(path, header_file)

    #Executing the read function
    obj.read(h_filepath, header_file)

    #If offset addresses are present continue to read the header file and execute the rest process

    for key, values in Register_dict.items():

        #Getting the mode value i.e register_default_read and write_read
        mode_values = values.split(',')

    #Executing the process for the respective mode
    for mode in mode_values:
        mode = mode.strip()
        logging.info(f"The present mode is {mode} for header file {header_file}")
        print(f'=============== The present mode is {mode} for header file {header_file} ============================')
        c_filedir = os.path.join(c_file_path, mode)

        h_filename = obj.block1.strip('.h')
        c_file_dir = os.path.join(c_filedir, h_filename)

        #Removes the directory if already present
        if os.path.exists(c_file_dir):
               shutil.rmtree(c_file_dir)


        if len(obj.offset) != 0:
            #copy content of resource directory to respective c file directory
            shutil.copytree(resource_path, c_file_dir)

            #To create the c filename
            c_filename = h_filename + '.c'

            #To create the path of respective c file
            c_filename_path = os.path.join(c_file_dir, c_filename)

            #Execute the create_cfile function for the respective c file path
            obj.create_cfile(c_filename_path)

            #Execute the write function for the respective c file for the respective mode
            obj.write_c_file(c_filename_path, mode)

            for content in resource_list:
                if content.endswith('.py'):
                    old_py_filepath = os.path.join(c_file_dir, content)
                    py_file = content.split('.')[0]
                    new_py_file = content.replace(py_file, h_filename)
                    new_py_filepath = os.path.join(os.path.dirname(old_py_filepath), new_py_file)
                    os.rename(old_py_filepath, new_py_filepath)
                    logging.info(f'Renaming the py file of Resource file to required register py file for header file {header_file}')
                    print(f'=================== Renaming the py file of Resource file to required register py file for header file {header_file}======================')
        else:
            logging.info(f"skipping {header_file} as it doesn't have offset addresses")
            print(f"====================== skipping {header_file} as it doesn't have offset addresses =======================")





if __name__ == '__main__':

    #Dictionary for modes
    Register_dict = {"Register_type": "write_read,register_default"}
    #To set the environment for PROJECT_HOME
    PROJECT_HOME = os.environ['PROJECT_HOME']
    print("Home directory path: ", PROJECT_HOME)

    #Path of project header files
    path = PROJECT_HOME + "/src/hw_inc/"

    #Getting the list of h files from the src directory
    h_file_list = os.listdir(path)

    #Path where c files will be created
    c_file_path = PROJECT_HOME + "/tests/reg_access/"

    #resource path
    resource_path = PROJECT_HOME + "/scripts/Register_test_generation_scripts/resources/"

    #Getting the content of resource directory
    resource_list = os.listdir(resource_path)

    for header_file in h_file_list:
        process_header_file(header_file)
    logging.info('C files are created, and the whole process is complete')

    print('C files are created, and the whole process is complete')
