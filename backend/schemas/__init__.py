import json
from pathlib import Path


_base_dir = Path(__file__).resolve().parent

with (_base_dir / "taskschema.json").open("r") as fp:
    task_schema = json.load(fp)

with (_base_dir / "timerschema.json").open("r") as fp:
    timer_schema = json.load(fp)
