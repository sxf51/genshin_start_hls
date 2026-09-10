# 2026-09-07T04:49:34.764832100
import vitis

client = vitis.create_client()
client.set_workspace(path="workspace")

comp = client.get_component(name="baseline")
comp.run(operation="C_SIMULATION")

comp.run(operation="SYNTHESIS")

comp.run(operation="C_SIMULATION")

comp.run(operation="SYNTHESIS")

comp.run(operation="C_SIMULATION")

comp.run(operation="SYNTHESIS")

comp.run(operation="PACKAGE")

