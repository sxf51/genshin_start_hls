# 2026-09-06T11:06:12.977466687
import vitis

client = vitis.create_client()
client.set_workspace(path="genshin_start_hls")

vitis.dispose()

