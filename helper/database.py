import json 

class DataUser:
    def __init__(self):
        self.file_path = 'database/user_database.json'

    def load(self):
        with open(self.file_path, "r") as json_file: 
            return json.load(json_file)
    
    def save(self, cur):
        with open(self.file_path, "w") as json_file: 
            json.dump(cur, json_file)

    def set(self, id_discord, username_polygon):
        id_discord = str(id_discord)
        cur = self.load()
        if id_discord in cur:
            cur.pop(id_discord)
        cur[id_discord] = username_polygon
        self.save(cur)
    def get(self, id_discord):
        id_discord = str(id_discord)
        cur = self.load()
        if id_discord in cur:
            return cur[id_discord]
        return None
    def list(self):
        return self.load()

    