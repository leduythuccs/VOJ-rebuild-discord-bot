import requests, random, hashlib, time
from urllib.parse import urlparse, parse_qs

BASE_URL = 'https://polygon.codeforces.com'

class PolygonInteracter:
    def __init__(self, username, password, api_key, api_secret):
        self.username = username
        self.password = password
        self.api_key = api_key
        self.api_secret = api_secret

        s = requests.session()
        s.allow_redirects = False

        self.s = s

        self.login()

    def extract_ccid(self, text):
        return text.split('name="ccid" content="')[1].split('"')[0]

    #login with self.username & self.password
    def login(self):
        r = self.s.get(BASE_URL + '/login')
        ccid = self.extract_ccid(r.text)
        self.ccid = ccid

        data = {
            'login': self.username,
            'password': self.password,
            'submit': 'Login',
            'submitted': 'true'
        }

        params = {
            'ccid': ccid
        }

        r1 = self.s.post(BASE_URL + '/login', data=data, params=params, allow_redirects=False)

        print(r1.status_code)

        if r1.status_code != 302:
            return False

        print(self.username + " logged to polygon")
        return True

    def get_session_id(self, problem_id):
        data = {'problemId': problem_id}
        params = {'ccid': self.ccid}

        continue_edit_request = self.s.post(BASE_URL + '/edit-start', data=data, params=params, allow_redirects=False)

        session = parse_qs(urlparse(continue_edit_request.headers['location']).query)['session'][0]

        return session

    def request_unofficial(self, method_name, data={}, params={}, method='GET'):
        data['ccid'] = self.ccid

        if not ('session' in data and data['session']):
            data['session'] = self.get_session_id(data['problemId'])

        return self.s.request(method, BASE_URL + '/' + method_name, files=data, params=params)

    def request_official(self, method_name, data={}, params={}, method='POST'):
        params["apiKey"] = self.api_key
        params["time"] = int(time.time())

        signature_random = ''.join([chr(random.SystemRandom().randint(0, 25) + ord('a')) for _ in range(6)])
        signature_random = signature_random.encode('utf-8')

        for i in params:
            params[i] = str(params[i]).encode('utf-8')
        param_list = [(key.encode('utf-8'), params[key]) for key in params]
        param_list.sort()

        signature_string = signature_random + b'/' + method_name.encode('utf-8')
        signature_string += b'?' + b'&'.join([i[0] + b'=' + i[1] for i in param_list])
        signature_string += b'#' + self.api_secret.encode('utf-8')
        params["apiSig"] = signature_random + hashlib.sha512(signature_string).hexdigest().encode('utf-8')
        url = BASE_URL + '/api/' + method_name

        return self.s.request(method, url, files=params)

    def get_problem_list(self):
        return self.request_official('problems.list').json()['result']

    def give_access(self, problem_id, usernames, permission='WRITE', session=None):
        # give username permission to problem 

        data = {
            'problemId': problem_id,
            'submitted': 'true',
            'users_added': ','.join(usernames),
            'type': permission,
            'session': session
        }

        r = self.request_unofficial('access', data=data, params={'action': 'add'}, method='POST')

        return 'location' in r.headers and 'access' in r.headers['location']