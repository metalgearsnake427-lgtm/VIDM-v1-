setup_gui_code = r"""
import tkinter as tk
from tkinter import messagebox, ttk
import subprocess
import threading
import os

class VidMInstaller:
    def __init__(self, root):
        self.root = root
        self.root.title("vidM Media Engine - Setup Wizard")
        self.root.geometry("500x350")
        
        self.label = tk.Label(root, text="Welcome to the vidM Installation", font=("Arial", 14, "bold"))
        self.label.pack(pady=20)

        self.info = tk.Label(root, text="This will install FFmpeg, SDL2, and the Media Engine.", wraplength=400)
        self.info.pack(pady=10)

        self.progress = ttk.Progressbar(root, orient="horizontal", length=300, mode="determinate")
        self.progress.pack(pady=20)

        self.install_btn = tk.Button(root, text="Install Now", command=self.start_installation, 
                                     bg="#1DB954", fg="white", width=15)
        self.install_btn.pack(pady=10)

        self.status_var = tk.StringVar(value="Ready to install.")
        self.status_label = tk.Label(root, textvariable=self.status_var, fg="gray")
        self.status_label.pack(side="bottom", pady=5)

    def start_installation(self):
        self.install_btn.config(state="disabled")
        threading.Thread(target=self.run_setup).start()

    def run_setup(self):
        try:
            self.status_var.set("Running vidM.ps1 installer...")
            self.progress['value'] = 30
            
            # Execute the PowerShell installer we created earlier
            process = subprocess.run(["powershell.exe", "-ExecutionPolicy", "Bypass", "-File", ".\\vidM.ps1"], 
                                     capture_output=True, text=True)
            
            if process.returncode == 0:
                self.progress['value'] = 100
                self.status_var.set("Installation Successful!")
                messagebox.showinfo("Success", "vidM Media Engine installed successfully!")
            else:
                self.status_var.set("Installation Failed.")
                messagebox.showerror("Error", f"Setup failed:\n{process.stderr}")
        except Exception as e:
            messagebox.showerror("Error", str(e))
        finally:
            self.install_btn.config(state="normal")

if __name__ == "__main__":
    root = tk.Tk()
    app = VidMInstaller(root)
    root.mainloop()
"""

with open('setup_gui.py', 'w') as f:
    f.write(setup_gui_code)

print("Setup GUI script 'setup_gui.py' created.")
