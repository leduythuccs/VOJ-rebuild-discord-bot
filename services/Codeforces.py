import re
import requests
import os

class CodeforcesInteracter:
    def __init__(self, username, password):
        self.username = username
        self.password = password
        self.session = requests.session()
        self.headers = {
            'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.130 Safari/537.36',
            'accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9',
            'accept-encoding': 'gzip, deflate, br',
            'accept-language': 'zh-TW,zh;q=0.9,en-US;q=0.8,en;q=0.7,zh-CN;q=0.6',
        }
        self.login()

    def login(self):
        url = 'https://codeforces.com/enter'
        result = self.session.get(url, headers=self.headers)
        csrf_token_pattern = r'name=["\']csrf_token["\'] value=["\'](.*?)["\']'
        ftaa_pattern = r'window._ftaa = ["\'](.*?)["\']'
        bfaa_pattern = r'window._bfaa = ["\'](.*?)["\']'
        data = {
            'csrf_token': re.findall(csrf_token_pattern, result.text)[0],
            'action': 'enter',
            'ftaa': re.findall(ftaa_pattern, result.text)[0],
            'bfaa': re.findall(bfaa_pattern, result.text)[0],
            'handleOrEmail': self.username,
            'password': self.password,
            '_tta': 487,
        }
        login_result = self.session.post(url, data=data, headers=self.headers)
        return self.check_login()

    def check_login(self):
        url = 'https://codeforces.com/settings/general'
        result = self.session.get(url, headers=self.headers, allow_redirects = False)
        if not result.is_redirect:
            print(self.username + " logged to codeforces.")
            return True
        
        print('Login failed!')
        return False
    def get_last_contest(self):
        url = 'https://codeforces.com/mashups'
        text = self.session.get(url, headers=self.headers).text
        pattern = r'\/gym\/(\d+)'
        ids = set(re.findall(pattern, text))
        ids = list(map(int, ids))
        return max(ids)
    def create_mashup(self, contest_name, problem_json, duration = 10):
        url = 'https://codeforces.com/mashup/new'
        result = self.session.get(url, headers=self.headers)
        csrf_token_pattern = r'name=["\']csrf_token["\'] value=["\'](.*?)["\']'
        ftaa_pattern = r'window._ftaa = ["\'](.*?)["\']'
        bfaa_pattern = r'window._bfaa = ["\'](.*?)["\']'
        data = {
            'csrf_token': re.findall(csrf_token_pattern, result.text)[0],
            'ftaa': re.findall(ftaa_pattern, result.text)[0],
            'bfaa': re.findall(bfaa_pattern, result.text)[0],
            '_tta': 377,
            #stuff
            'action': 'saveMashup',
            'isCloneContest' : 'false',
            'parentContestId' : '',
            'parentContestIdAndName' : '',
            'contestName' : contest_name,
            'contestDuration' : duration,
            'problemsJson' : str(problem_json),
        }
        url = 'https://codeforces.com/data/mashup'
        r = self.session.post(url, params=data, headers = self.headers).json()
        if "success" in r:
            return True, self.get_last_contest()
        open('err_mashup.txt', 'a', encoding='utf-8').write(str(r) + '\n')
        return False, str(r)