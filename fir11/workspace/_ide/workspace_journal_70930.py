# 2026-08-31T10:54:41.137655214
import vitis

client = vitis.create_client()
client.set_workspace(path="workspace")

comp = client.create_hls_component(name = "baseline",cfg_file = ["hls_config.cfg"],template = "empty_hls_component")

cfg = client.get_config_file(path="/home/lipuze/genshin_start_hls/fir11/workspace/baseline/hls_config.cfg")

cfg.set_value(key="part", value="xck26-sfvc784-2LV-c")

cfg.set_value(section="hls", key="clock", value="10")

cfg.set_value(section="hls", key="syn.top", value="fir")

cfg.set_values(key="syn.file", values=["../../fir.cpp", "../../fir.h"])

cfg.set_values(key="tb.file", values=["../../fir_test.cpp", "../../input.dat", "../../out.gold.dat"])

cfg.set_value(section="hls", key="package.output.format", value="ip_catalog")

vitis.dispose()

