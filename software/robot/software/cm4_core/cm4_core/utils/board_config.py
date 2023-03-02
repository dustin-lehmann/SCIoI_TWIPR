import json
import uuid
from pathlib import Path
import os

uuid_file_path = os.path.expanduser('~/board_uuid.json')
config_file_path = os.path.expanduser('~/board_config.json')


# ======================================================================================================================
def getBoardConfig():
    # First check if the files exist

    config = {}
    with open(config_file_path) as config_file:
        config = {**config, **json.load(config_file)}
    with open(uuid_file_path) as uuid_file:
        config = {**config, **json.load(uuid_file)}

    return config


# ======================================================================================================================
def generate_uuid_file():
    uid = str(uuid.uuid4())
    print(uid)
    data = {
        'uid': uid
    }

    with open(uuid_file_path, "w") as uuid_file:
        json.dump(data, uuid_file)


# ======================================================================================================================
def generate_board_config():
    board_config = {
        'name': 'c4_02',
        'address': list(b'\x01\x01'),
    }

    with open(config_file_path, 'w') as config_file:
        json.dump(board_config, config_file)


if __name__ == '__main__':
    # generate_uuid_file()
    generate_board_config()
