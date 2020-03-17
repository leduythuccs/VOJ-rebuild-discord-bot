import os

dir_map = {}
def mapping_file_name():
    dir_map = {}
    path = 'problem_set/'
    for x in os.listdir(path):
        if x.find('.') != -1:
            x = x[:x.find('.')]
            dir_map[x.lower()] = x
        else:
            dir_map[x.lower()] = x
            for y in os.listdir(path + x + '/'):
                y = y[:y.find('.')]
                dir_map[y.lower()] = y

def format_name(x):
    tmp = x.lower()
    print('name ' + tmp)
    if tmp not in dir_map:
        return "NULL"
    return dir_map[tmp]

def format_path(x):
    tmp = str(x.lower())
    print(tmp)
    tmp.replace("//", "/")
    tmp = '/'.join(map(lambda x: format_name(x), tmp.split('/')))
    return tmp

def get_give_list(sets):
    
    problem_set = format_path(sets)

    path = "problem_set/"
    problems = []
    folders = []
    print(";" + problem_set + ";")
    if len(sets) >= 3 and sets[-3:].upper() == "ALL" != -1:
        if problem_set == "ALL":
            folders = [path + format_name("ALL") + ".txt"]
        else:
            path += problem_set[:problem_set.rfind('/') + 1]
            folders = [path + format_name(x[:x.find('.')]) + '.txt' for x in os.listdir(path)]
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