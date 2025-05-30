import argparse
import time
import paramiko
import os
from datetime import datetime
from outlook_mail import Send_Mail, HTML_Header

os.environ["PYTHONUNBUFFERED"] = "1"

class JenkinsRunner:

    def __init__(self):
        print("STARTING...")
        parser = argparse.ArgumentParser()
        parser.add_argument('--clone_ip', type=str, required=True, help="IP address for cloning the repository")
        parser.add_argument('--clone_username', type=str, required=True, help="Username for cloning the repository")
        parser.add_argument('--clone_password', type=str, required=True, help="Password for cloning the repository")
        parser.add_argument('--run_ip', type=str, required=True, help="IP address for running commands")
        parser.add_argument('--run_username', type=str, required=True, help="Username for running commands")
        parser.add_argument('--run_password', type=str, required=True, help="Password for running commands")
        parser.add_argument('--dir', type=str, required=True, help="Directory to execute commands")
        parser.add_argument('--env', type=str, required=True, help="Environment setup command")
        parser.add_argument('--db_hw', type=str, required=True, help="Hardware setup command")

        self.args = parser.parse_args()

        self.clone_ip = self.args.clone_ip
        self.clone_username = self.args.clone_username
        self.clone_password = self.args.clone_password

        self.run_ip = self.args.run_ip
        self.run_username = self.args.run_username
        self.run_password = self.args.run_password
        
        self.clone_dir = "/project/hwc/workspace/hw/users/suryapr3"
        self.test_script_dir = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/suryap/sudharsan_dir"
        self.exec_dir = self.args.dir
        self.env = self.args.env
        self.db_hw = self.args.db_hw

        self.directory_name = None

    def run_remote_clone(self, hostname, username, password, repo_url, base_path):
        port = 22
        ssh = paramiko.SSHClient()
        ssh.load_system_host_keys()
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())

        try:
            ssh.connect(hostname, port=port, username=username, password=password)
            today_date = datetime.now().strftime('%Y-%m-%d_%H-%M-%S-%f')
            self.directory_name = f"repo_clone_{today_date}"
            full_path = f"{base_path}/{self.directory_name}"

            # Create the directory
            create_dir_command = f'mkdir -p {full_path}'
            print(f"Creating directory: {create_dir_command}")
            stdin, stdout, stderr = ssh.exec_command(create_dir_command)
            print(stdout.read().decode())
            print(stderr.read().decode())

            # Verify directory creation
            verify_dir_command = f'ls -ld {full_path}'
            stdin, stdout, stderr = ssh.exec_command(verify_dir_command)
            print("Directory verification output:")
            print(stdout.read().decode())
            print(stderr.read().decode())

            # Clone the repository
            clone_command = f'cd {full_path} && git clone {repo_url} .'
            print(f"Cloning repository: {clone_command}")
            stdin, stdout, stderr = ssh.exec_command(clone_command)
            print(stdout.read().decode())
            print(stderr.read().decode())

            # Change the mode of the script to executable
            script_path = f"{full_path}/tests/reg_access/reg_access_execution_18a.sh"
            chmod_command = f'chmod +x {script_path}'
            print(f"Changing script mode to executable: {chmod_command}")
            stdin, stdout, stderr = ssh.exec_command(chmod_command)
            print(stdout.read().decode())
            print(stderr.read().decode())

            print(f"Executed script in {full_path}:")
            print("Output:")
            print(output)
            print("Error:")
            print(error)

        except Exception as e:
            print(f"An error occurred: {e}")

        finally:
            ssh.close()
            
    def run_remote_commands(self, hostname, username, password, commands, directory):
        port = 22
        ssh = paramiko.SSHClient()
        ssh.load_system_host_keys()
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())

        try:
            ssh.connect(hostname, port=port, username=username, password=password)

            # Define the shell script content
            script_content = """#!/bin/bash

# Get the directory name from the first argument
directory_name=$1

# Define the path and file name
file_path="/nfs/site/disks/zsc14.xne_abc_fe_001/users/suryap/sudharsan_dir"
file_name="test_script"

# Ensure the directory exists
mkdir -p "$file_path"

# Full path to the file
full_file_path="$file_path/$file_name"

# Create and write the content to the file using a heredoc
cat <<EOF > "$full_file_path"
#!/bin/bash
echo "Hello test script"

# Check whether FRIO RTE and ABC RTE are loaded. If not, load them
pwd
cd /project/hwc/workspace/hw/users/suryapr3/$directory_name || { echo "Directory not found"; exit 1; }
source FPGA.env || { echo "FPGA.env not found"; exit 1; }
pwd
echo "Executing memory access tests"
echo "Executing register access tests"
./\$PROJCT_HOME/tests/reg_access/reg_access_execution_18a.sh
echo "Executing vha tests"
echo "Executing v2d tests"
echo "Executing rcs tests"
echo "Executing vex tests"
python ./\$PROJCT_HOME/scripts/report.py
EOF

# Print success message
echo "File '$file_name' created successfully at '$file_path'."
"""

            # Use SFTP to upload the script content
            sftp = ssh.open_sftp()
            shell_script_path = f"{self.test_script_dir}/write_bash_script.sh"
            with sftp.file(shell_script_path, 'w') as script_file:
                script_file.write(script_content)
            sftp.close()

            # Verify script creation
            verify_script_command = f'ls -l {shell_script_path}'
            stdin, stdout, stderr = ssh.exec_command(verify_script_command)
            print("Script verification output:")
            print(stdout.read().decode())
            print(stderr.read().decode())

            # Execute the shell script on the remote server with the directory name as an argument
            full_command = f'bash {shell_script_path} {self.directory_name} && cd {directory} && ' + ' && '.join(commands)
            print(f"\n\nfull_command : {full_command}")

            stdin, stdout, stderr = ssh.exec_command(full_command)
            output = stdout.read().decode()
            error = stderr.read().decode()

            print(f"Executed commands in {directory}:")
            print("Output:")
            print(output)
            print("Error:")
            print(error)

            for line in iter(stdout.readline, ""):
                print(line, end='', flush=True)

            print("---> Error:", flush=True)
            for line in iter(stderr.readline, ""):
                print(line, end='', flush=True)

        except Exception as e:
            print(f"An error occurred: {e}")

        finally:
            ssh.close()

    def trigger_job(self):
        try:
            print("\n\n ---------------------- Please wait trigger the job ---------------------")
            print(f"Clone IP            : {self.clone_ip}")
            print(f"Clone USERNAME      : {self.clone_username}")
            print(f"Run IP              : {self.run_ip}")
            print(f"Run USERNAME        : {self.run_username}")
            print(f"Execution Directory : {self.exec_dir}")
            print(f"Source Env Command  : {self.env}")
            print(f"FRIO HW Command     : {self.db_hw}")

            with open("jenkins_metadata.txt", "w") as f:
                f.write(f"Dir:{self.exec_dir}")
                f.write("\n")
                f.write(f"SourceEnv:{self.env}")
                f.write("\n")
                f.write(f"db_hw:{self.db_hw}")
                f.write("\n")

            repo_url = "https://github.com/intel-innersource/applications.validation.wireless.radio.functional.abc-emul-val.git"
            self.run_remote_clone(self.clone_ip, self.clone_username, self.clone_password, repo_url, self.clone_dir)

            commands = [f"{self.env}", f"{self.db_hw}"]
            print(f"Command List        : {commands}")
            self.run_remote_commands(self.run_ip, self.run_username, self.run_password, commands, self.exec_dir)

            time.sleep(2)
            print("Sending Mail...")
            contents = HTML_Header()
            Send_Mail(from_address="suryaprakash.mishra@intel.com",
                      to_address=["sneha.singh@intel.com","suryaprakash.mishra@intel.com"],
                      Subject="ABC Jenkin Automation Regression Report",
                      contents=contents,
                      attachments=[])
            print("Mail Sent")

        except Exception as err:
            print(err)

if __name__ == '__main__':
    jenkinsRunner = JenkinsRunner()
    jenkinsRunner.trigger_job()
    print("Execution Completed.")