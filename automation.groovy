def writeLogFile(String logFilePath, String buildUrl, String buildNumber, String cloneIp, String cloneUsername, String runIp, String runUsername, String execDir, String setupEnvCmd, String designLoadingHwCmd) {
    def logContent = """
    Build URL: ${buildUrl}
    Build Number: ${buildNumber}
    Clone IP: ${cloneIp}
    Clone Username: ${cloneUsername}
    Run IP: ${runIp}
    Run Username: ${runUsername}
    Execution Directory: ${execDir}
    Setup Environment Command: ${setupEnvCmd}
    Design Loading HW Command: ${designLoadingHwCmd}
    """

    // Use writeFile to create the log file
    writeFile file: logFilePath, text: logContent
    println "Log file created at: ${logFilePath}"
}

properties([
    parameters([
        string(name: 'CLONE_IP', defaultValue: '', description: 'Provide the IP for cloning the repository'),
        string(name: 'CLONE_USERNAME', defaultValue: '', description: 'Provide the username for cloning the repository'),
        password(name: 'CLONE_PASSWORD', defaultValue: '', description: 'Provide the password for cloning the repository'),
        string(name: 'RUN_IP', defaultValue: '', description: 'Provide the IP for running commands'),
        string(name: 'RUN_USERNAME', defaultValue: '', description: 'Provide the username for running commands'),
        password(name: 'RUN_PASSWORD', defaultValue: '', description: 'Provide the password for running commands'),
        string(name: 'EXECUTION_DIR', defaultValue: '', description: 'Provide the execution dir'),
        string(name: 'SETUP_ENV_CMD', defaultValue: '', description: 'Provide the source_env_frio_cmd'),
        string(name: 'DESIGN_LOADING_HW_CMD', defaultValue: '', description: 'Design_load_frio_hw_selection_cmd.')
    ])
])

node {
    stage('Git Operation') {
        try {
            println "Attempting Git Checkout..."
            if (fileExists('.git')) {
                println "Repository exists. Performing git pull without deleting the workspace..."
                checkout scm
            } else {
                println "Repository does not exist. Performing full checkout..."
                checkout scm
            }
            println "Git Checkout is Successful"
        } catch (Exception checkoutException) {
            println "Error during Git Checkout: ${checkoutException.message}"
            currentBuild.result = 'ABORTED'
            error("Stopping due to failure in Git operations.")
        }
    }

    stage('Regression') {
        try {
            def CLONE_IP = params.CLONE_IP
            def CLONE_USERNAME = params.CLONE_USERNAME
            def CLONE_PASSWORD = params.CLONE_PASSWORD
            def RUN_IP = params.RUN_IP
            def RUN_USERNAME = params.RUN_USERNAME
            def RUN_PASSWORD = params.RUN_PASSWORD
            def EXECUTION_DIR = params.EXECUTION_DIR
            def SETUP_ENV_CMD = params.SETUP_ENV_CMD
            def DESIGN_LOADING_HW_CMD = params.DESIGN_LOADING_HW_CMD

            def BUILD_URL = env.BUILD_URL ?: "Build URL not available"
            def BUILD_NUMBER = env.BUILD_NUMBER ?: "Build Number not available"
            def LOG_FILE_PATH = "execution_log.txt" // Ensure this path is valid

            script {
                println '-------------------------------------------------------'
                println "STARTING AUTOMATION, PLEASE WAIT"

                // Create log file and write details
                writeLogFile(LOG_FILE_PATH, BUILD_URL, BUILD_NUMBER, CLONE_IP, CLONE_USERNAME, RUN_IP, RUN_USERNAME, EXECUTION_DIR, SETUP_ENV_CMD, DESIGN_LOADING_HW_CMD)

                bat """
                python.exe -u jenkins_runner.py --clone_ip "${CLONE_IP}" --clone_username "${CLONE_USERNAME}" --clone_password "${CLONE_PASSWORD}" --run_ip "${RUN_IP}" --run_username "${RUN_USERNAME}" --run_password "${RUN_PASSWORD}" --dir "${EXECUTION_DIR}" --env "${SETUP_ENV_CMD}" --db_hw "${DESIGN_LOADING_HW_CMD}"
                """
            }
            println "[Stage-2] Test Execution - Successfully"
        } catch (Exception e) {
            println "Error during test execution: ${e.message}"
            currentBuild.result = 'ABORTED'
            error("Stopping due to an error in the build stage.")
        }
    }
}