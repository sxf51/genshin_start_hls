# Create and configure the FIR HLS component.
#
# IMPORTANT: run this from the project folder itself (i.e. whichever folder contains fir.cpp)
#
#     vitis -s script.py
#
# Afterwards, this console must be closed, otherwise vitis will complain
# that the workspace is already open in another process.

import os
import shutil
import vitis
import sys
import locale
sys.stdout.reconfigure(encoding='utf-8')

# Start from a clean workspace each run.
if os.path.exists("./workspace"):
    print("Deleting the existing 'workspace' folder ...")
    shutil.rmtree("./workspace")

client = vitis.create_client()

# Define workspace for component
client.set_workspace(path="./workspace")

# Create component called baseline
print("Creating HLS component 'baseline' ...")
comp = client.create_hls_component(
    name="baseline",
    cfg_file=["hls_config.cfg"],
    template="empty_hls_component",
)

# Set configuration parameters for new component
cfg = client.get_config_file(path="./workspace/baseline/hls_config.cfg")
src = "../../"

# Kria SOM as target part
cfg.set_value(key="part", value="xck26-sfvc784-2LV-c")

# Set target clock speed to 10ns
cfg.set_value(section="hls", key="clock", value="10")

# Set top-value function
cfg.set_value(section="hls", key="syn.top", value="fir")

# Include source files
cfg.set_values(section="hls", key="syn.file",
               values=[src + "fir.cpp", src + "fir.h"])

# Testbench files and data files
cfg.set_values(section="hls", key="tb.file",
               values=[src + "fir_test.cpp",
                       src + "input.dat",
                       src + "out.gold.dat"])

# packaging format for the exported IP
cfg.set_value(section="hls", key="package.output.format", value="ip_catalog")

print("Done. Please exit the current console, then set the workspace in Vitis ('Set Workspace' -> the new 'workspace' folder).")

# The flow steps can be scripted too - uncomment to run them here
# instead of clicking them in the GUI:

# comp = client.get_component(name="baseline")
# comp.run(operation="C_SIMULATION")
# comp.run(operation="SYNTHESIS")
# comp.run(operation="CO_SIMULATION")
# comp.run(operation="PACKAGE")

vitis.dispose()
