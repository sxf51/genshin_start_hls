# 2026-08-31T10:50:28.250120777
import vitis

client = vitis.create_client()
client.set_workspace(path="genshin_start_hls")

vitis.dispose()

