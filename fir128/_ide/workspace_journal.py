# 2026-09-05T22:30:38.159416820
import vitis

client = vitis.create_client()
client.set_workspace(path="fir128")

comp = client.get_component(name="baseline")
comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

vitis.dispose()

