import json
__PREFIX__ = 'voj-'
def get_commit_state(problems):
    res = {}
    for problem in problems:
        if __PREFIX__ and problem.find(__PREFIX__) == -1:
            continue
        name = problem['name'].upper()
        number_commit = int(problem['revision'])
        res[name] = number_commit
    return res

def get_problem_name_id(problems):
    res = {}
    for problem in problems:
        name = problem['name'].upper()
        if __PREFIX__ and name.find(__PREFIX__) == -1:
            continue
        id = int(problem['id'])
        if name in res:
            if problem['owner'] == 'tuvietthao':
                continue
            
        res[name] = id
    return res

def time_format(seconds):
    seconds = int(seconds)
    days, seconds = divmod(seconds, 86400)
    hours, seconds = divmod(seconds, 3600)
    minutes, seconds = divmod(seconds, 60)
    return days, hours, minutes, seconds

def pretty_time_format(seconds):
    days, hours, minutes, seconds = time_format(seconds)
    timespec = [
        (days, 'day', 'days'),
        (hours, 'hour', 'hours'),
        (minutes, 'minute', 'minutes'),
        (seconds, 'second', 'seconds')
    ]
    timeprint = [(cnt, singular, plural) for cnt, singular, plural in timespec if cnt]
    def format_(triple):
        cnt, singular, plural = triple
        return f'{cnt} {singular if cnt == 1 else plural}'

    return ' '.join(map(format_, timeprint))