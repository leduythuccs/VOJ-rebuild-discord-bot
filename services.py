class PolygonInteracter:
    def __init__(self, username, password):
        self.username = username
        self.password = password

    #login with self.username & self.password
    def login(self):
        print(self.username + " logged to polygon")
    
    def give_access(self, problem_name, username, permission = 'WRITE'):
        # give username permission to problem 
        # maybe we need mapping from problem_name to problem_id ?
        # please be careful because problem_name maybe not uploaded to polygon yet
        print("Gave permisstion {2} of problem {0} to user {1} successfully".format(problem_name, username, permission))
        # return true if give access successfully 
        return True
