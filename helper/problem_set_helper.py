import os
class problem_set_helper:
    def __init__(self):
        self.dir_map = {}
        self.mapping_file_name()

    def mapping_file_name(self):
        self.dir_map = {}
        path = 'problem_set/'
        for x in os.listdir(path):
            if x.find('.') != -1:
                x = x[:x.find('.')]
                self.dir_map[x.lower()] = x
            else:
                self.dir_map[x.lower()] = x
                for y in os.listdir(path + x + '/'):
                    y = y[:y.find('.')]
                    self.dir_map[y.lower()] = y

    def format_name(self, x):
        tmp = x.lower()
        if tmp not in self.dir_map:
            return "NULL"
        return self.dir_map[tmp]

    def format_path(self, x):
        tmp = str(x.lower())
        tmp.replace("//", "/")
        tmp = '/'.join(map(lambda x: self.format_name(x), tmp.split('/')))
        return tmp

    def get_give_list(self, sets):
        
        problem_set = self.format_path(sets)

        path = "problem_set/"
        problems = []
        folders = []
        print(";" + problem_set + ";")
        if len(sets) >= 3 and sets[-3:].upper() == "ALL" != -1:
            if problem_set == "ALL":
                folders = [path + format_name("ALL") + ".txt"]
            else:
                path += problem_set[:problem_set.rfind('/') + 1]
                folders = [path + self.format_name(x[:x.find('.')]) + '.txt' for x in os.listdir(path)]
        else:
            folders = [path + problem_set + ".txt"]
        print(folders)
        files = []
        for folder in folders:
            if folder.find('.') != -1:
                files.append(folder)
            else:
                files += os.listdir(folder)
        print(files)
        categories = ""
        for f in files:
            if (os.path.exists(f)):
                data = list(map(lambda x: x.strip('\n'), open(f, "r", encoding='utf-8').readlines()))
                categories += data[0] + ", "
                problems += data[1:]
            else:
                problems += [sets]
        if len(categories) >= 2:
            categories = categories[0:-2]

        # problems = list(set(problems)) # erase duplicate problems
        print(problems)
        return problems, categories