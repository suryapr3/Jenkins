import re
import smtplib
from datetime import datetime
from email.mime.image import MIMEImage
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.utils import formataddr
from pathlib import Path


def get_build_info_from_jenkins():
    log_file_path = 'execution_log.txt'
    result_dict = {}

    # Initialize variables
    build_url = ''
    build_number = ''
    vnc_ip = ''
    vnc_username = ''
    execution_dir = ''
    setup_env_cmd = ''
    design_loading_hw_cmd = ''

    # Read the log file
    with open(log_file_path, 'r') as file:
        log_content = file.read()

    # Use regular expressions to extract information
    build_url_match = re.search(r'Build URL:\s*(.*)', log_content)
    build_number_match = re.search(r'Build Number:\s*(.*)', log_content)
    vnc_ip_match = re.search(r'VNC IP:\s*(.*)', log_content)
    vnc_username_match = re.search(r'VNC Username:\s*(.*)', log_content)
    execution_dir_match = re.search(r'Execution Directory:\s*(.*)', log_content)
    setup_env_cmd_match = re.search(r'Setup Environment Command:\s*(.*)', log_content)
    design_loading_hw_cmd_match = re.search(r'Design Loading HW Command:\s*(.*)', log_content)

    # Check if matches were found and assign to variables
    if build_url_match:
        build_url = build_url_match.group(1).strip()
        result_dict["build_url"] = build_url
    if build_number_match:
        build_number = build_number_match.group(1).strip()
        result_dict["build_number"] = build_number
    if vnc_ip_match:
        vnc_ip = vnc_ip_match.group(1).strip()
        result_dict["vnc_ip"] = vnc_ip
    if vnc_username_match:
        vnc_username = vnc_username_match.group(1).strip()
        result_dict["vnc_username"] = vnc_username
    if execution_dir_match:
        execution_dir = execution_dir_match.group(1).strip()
        result_dict["execution_dir"] = execution_dir
    if setup_env_cmd_match:
        setup_env_cmd = setup_env_cmd_match.group(1).strip()
        result_dict["setup_env_cmd"] = setup_env_cmd
    if design_loading_hw_cmd_match:
        design_loading_hw_cmd = design_loading_hw_cmd_match.group(1).strip()
        result_dict["design_loading_hw_cmd"] = design_loading_hw_cmd

    # Print extracted values
    print(f'Build URL: {build_url}')
    print(f'Build Number: {build_number}')
    print(f'VNC IP: {vnc_ip}')
    print(f'VNC Username: {vnc_username}')
    print(f'Execution Directory: {execution_dir}')
    print(f'Setup Environment Command: {setup_env_cmd}')
    print(f'Design Loading HW Command: {design_loading_hw_cmd}')
    return result_dict


def HTML_Header(build_version="16"):
    result_dict = get_build_info_from_jenkins()
    backGroundColor = "#CCCCCC"
    content = f"""
        <!DOCTYPE html>
        <html>
        <head>
            <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
            <title> ABC regression test report</title>
            <meta name="viewport" content="width=device-width, initial-scale=1">
            <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
        </head>

        <body style="font-family: Open Sans, Helvetica, Arial, sans-serif;">
            <h1 style="color: green;">ABC Regression Automation Test Report</h1>
        <br />

        <p>Hi All, <br />
                   Please find the below ABC Regression Test Report executed on <b>{datetime.today().date()}</b> at <b>{datetime.now().strftime('%H:%M:%S')}</b>
        </p>

        <table align="center" style="font-family: Open Sans, Helvetica, 
        Arial, sans-serif; width:100%; padding: 30px 10px; border-collapse: collapse; border-spacing: 0; text-align: center;">


        <tr style="background-color:{backGroundColor};">
            <td style="border:none">
        <table style="padding:0px 0px; width:800px; font-family: Open Sans, Helvetica, Arial, sans-serif;">

        <tr>
        <td style="height: 25px; text-align: center; background-color: #FFFFFF; border: none; padding: 30px 10px;" height="25" bgcolor="#FFFFFF" align="center">
            <h2>Jenkins Build No: {result_dict["build_number"]}</h2>
        <table style="font-family: Open Sans, Helvetica, Arial, sans-serif; margin-left:auto; margin-right:auto; border-collapse: collapse; border-spacing: 0; width: 80%;" width="80%">

        <tr>
            <td style="border: 1px solid black; height: 25px; text-align: center; font-weight: bold; color: #fff; background: #01a982; width: 35%;" width="35%" height="25" align="center">Jenkins Job Link</td>
            <td style="border: 1px solid black; height: 25px; text-align: center;" height="25" align="center">{result_dict["build_url"]}</td>
        </tr>

        <tr>
            <td style="border: 1px solid black; height: 25px; text-align: center; font-weight: bold; color: #fff; background: #01a982; width: 35%;" width="35%" height="25" align="center">EXECUTION_DIR</td>
            <td style="border: 1px solid black; height: 25px; text-align: center;" height="25" align="center">{result_dict["execution_dir"]}</td>
        </tr>

        <tr>
            <td style="border: 1px solid black; height: 25px; text-align: center; font-weight: bold; color: #fff; background: #01a982; width: 35%;" width="35%" height="25" align="center">SETUP_ENV_CMD</td>
            <td style="border: 1px solid black; height: 25px; text-align: center;" height="25" align="center">{result_dict["setup_env_cmd"]}</td>
        </tr>

        <tr>
            <td style="border: 1px solid black; height: 25px; text-align: center; font-weight: bold; color: #fff; background: #01a982; width="35%" height="25" align="center">DESIGN_LOADING_HW_CMD</td>
            <td style="border: 1px solid black; height: 25px; text-align: center;" height="25" align="center">{result_dict["design_loading_hw_cmd"]}</td>
        </tr>


        </table>
        </td>
        </tr>
        </table>
        </td>
        </tr>
        <br /><br /><br /><br />        
        </td></tr>
        <tr>
        <td style="text-align: center; font-family: Open Sans, Helvetica, Arial, sans-serif; background-color: #425563; height: 65px; font-size: 13px; color: #fff;">
                   Mail generated by ABC Test report regression jenkins automation  <br />
                   Intel Technology India Pvt Ltd <br />
                   Any issues test failure  please contact Lovekesh gupta <br />
                           </td>
        </tr>
        </table></td></tr>
        </table>
        </body>
        </html>
   """
    return content


def Send_Mail(from_address, to_address, Subject, contents, attachments):
    print("Sending Mail...")
    print(f"from_address:{from_address}\nto_address{to_address}\nSubject:{Subject}")
    smtpHost = "smtp.intel.com"
    smtpPort = 25
    mail = MIMEMultipart()
    mail['From'] = formataddr(("ABC automation", from_address))
    mail['To'] = ', '.join(to_address)
    mail['Subject'] = Subject
    mail.attach(MIMEText(contents, "html", "utf-8"))
    if attachments:
        for file in attachments:
            mail.attach(MIMEImage(Path(file).read_bytes()))
    try:
        smtpObj = smtplib.SMTP()
        smtpObj.connect(smtpHost, smtpPort)
        smtpObj.sendmail(from_address, to_address, mail.as_string())
        print("Mail Sent Successfully.")
        return True
    except Exception as err:
        print(err)


contents = HTML_Header()

with open("report.html", "w") as f:
    f.write(contents)

# Send_Mail(from_address="sudharsan.kandukuri@intel.com",
#           to_address=["lovekesh.gupta@intel.com","sudharsan.kandukuri@intel.com"],
#           Subject="Jenkin Automation Report",
#           contents=contents,
#           attachments=[])
