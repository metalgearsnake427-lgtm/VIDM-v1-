import subprocess

# Execute the unified Linux installer
# Note: This requires sudo for package installation. In a real environment, you would be prompted for a password.
try:
    print("--- Starting Full Installation on Linux ---")
    # Using 'bash' to run the generated installer script
    process = subprocess.Popen(['bash', './vidM_linux_unified.sh'], 
                               stdout=subprocess.PIPE, 
                               stderr=subprocess.STDOUT, 
                               text=True)

    # Stream output to the console
    for line in process.stdout:
        print(line, end='')

    process.wait()
    if process.returncode == 0:
        print("\n[SUCCESS] vidM installation and build complete!")
    else:
        print(f"\n[ERROR] Installation failed with exit code {process.returncode}")

except Exception as e:
    print(f"Failed to run installer: {e}")
