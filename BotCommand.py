from discord.ext import commands
import discord
import asyncio
import os
import services
import json 
from datetime import datetime
from helper import paginator
from helper import helper
import requests
import time

_OWNER_ = 'tuvietthao'
_WAIT_TIME_ = 1 #minute
_LOG_PATH_ = 'botlogs/'
_NOT_FOUND_ = 0
_INTERACTION_FAILED_ = 1
class BotCommand(commands.Cog):
    def __init__(self, bot):
        self.bot = bot
        username = os.getenv('POLYGON_USERNAME')
        password = os.getenv('POLYGON_PASSWORD')
        api_key = os.getenv('POLYGON_API_KEY')
        api_secret = os.getenv('POLYGON_API_SECRET')

        self.log_channel = None
        self.commit_state = None
        self.interator = services.PolygonInteracter(username, password, api_key, api_secret)

        self.problem_name_to_id = json.load(open("list_problems.json", "r"))
        self.id_query = 0
        self.start_time = 0
        self.dir_map = {}
    
    @commands.command(brief="diff")
    async def diff(self, ctx):
        link = 'https://raw.githubusercontent.com/t-rekttt/VOJ/master/haveTests.txt'
        path_old = 'old_all.txt'
        cur = requests.get(link).text
        f1 = list(map(lambda x: x.strip('\n'), cur.split('\n')))
        f2 = list(map(lambda x: x.strip('\n'), open(path_old, "r", encoding="utf-8").readlines()))
        message = ""
        for x in f1:
            if x not in f2:
                message += x + "\n"
        f = open("diff.txt", "w")
        f.write(message)
        f.close()
        await ctx.send(file=discord.File("diff.txt"))

    @commands.Cog.listener()
    async def on_ready(self):
        self.start_time = time.time()
        self.commit_state = helper.problem_json_to_dic(self.interator.get_problem_list())
        log_channel_id = int(os.getenv('DICORD_LOG_CHANNEL_ID'))
        self.log_channel = self.bot.get_channel(log_channel_id)
        #map
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

    
    def log(self, type_log, message):
        path = _LOG_PATH_ + "{0}_{1}.txt".format(self.id_query, type_log) 
        if os.path.exists(path) == False:
            open(path, "w").close()
        open(path, "a").write(message.strip() + ' ')
    
    def get_new_commit(self):
        current_commit_state = helper.problem_json_to_dic(self.interator.get_problem_list())
        message = ""
        for name in self.commit_state:
            if (current_commit_state[name] != self.commit_state[name]):
                message += name + " "
                self.commit_state[name] = current_commit_state[name]
        return message

    @commands.command(brief="Change log channel. [owner's command]")
    @commands.is_owner()
    async def change_log(self, ctx):
        """Change bot's log channel to this channel""" 
        self.log_channel = ctx.channel
        await ctx.send("Successfully set log channel to " + ctx.channel.name)
        
    @commands.command(brief="Get new commit each minute. [owner's command]")
    @commands.is_owner()
    async def loop(self, ctx):
        channel = self.log_channel
        if (channel is None):
            await ctx.send("Log channel not found.")
            return 
        cnt_loop = 0
        await channel.send("Starting to get new commit every minute.")
        while True:
            print(cnt_loop)
            message = self.get_new_commit()
            now = datetime.now()
            current_time = now.strftime("%Hh:%Mm:%Ss")
            if (len(message) > 0):
                message = current_time + ": In past " + str(_WAIT_TIME_) + " minute(s), these problem(s) has new commit: `" + message + "`"
                await channel.send(message)
            await asyncio.sleep(_WAIT_TIME_ * 60)

    @commands.command(brief="Check if bot is still alive. Also prints bot uptime")
    async def ping(self, ctx):
        await ctx.send("I have been running for " + 
                        helper.pretty_time_format(time.time() - self.start_time))

    @commands.command(brief="Kill bot. [owner's command]")
    @commands.is_owner()
    async def kill(self, ctx):
        """Kill bot, only bot's owner can call this command"""
        await ctx.send("Dying")
        exit(0)

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

    @commands.command(brief="Get all problem sets are available.", usage="[optional: problemset_folder]")
    async def problemset(self, ctx, *args):
        """Get all problem sets are available, if problemset_folder is provide, the bot will get all problem sets of that folder instead"""
        path = "problem_set/"
        if (len(args)):
            x = args[0]
            while x[-1] == '/':
                x = x[:-1]
            path += self.format_name(x) + '/'
        print(path)
        if os.path.exists(path) == False:
            await ctx.send("Path not found")
            return
        file_list = os.listdir(path)
        message = "`"
        for p in file_list:
            if p.find('.') != -1:
                message += p[:p.find('.')] + " "
            else:
                message += p + "/ "
        message += "`"
        await ctx.send(message)

    @commands.command(brief="Give permission access. [owner's command]", usage="[problems] [username1] [username2] [username3] ...")
    @commands.is_owner()
    async def give(self, ctx, problem_set, *args):
        """Give permission access of problem(s),
        Currently, "problems" can be: a single name or a problem set.
        [owner's command]
        """
        problem_set = self.format_path(problem_set)
        path = "problem_set/"
        username = args
        problems = []
        folders = []
        print(";" + problem_set + ";")
        if len(problem_set) >= 3 and problem_set[-3:] == "ALL" != -1:
            if problem_set == "ALL":
                folders = [path + self.format_name("ALL.txt")]
            else:
                path += problem_set[:-3]
                folders = [path + self.format_name(x) for x in os.listdir(path)]
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
                problems += [problem_set]
        if len(categories) >= 2:
            categories = categories[0:-2]
        #erase duplicate problems
        problems = list(set(problems))
        count_failed_problem = 0
        total_problem = len(problems)
        message = "Doing " + str(total_problem) + " problems, it might takes a couple of minutes"
        if len(categories) >= 1:
            message = "Problem categories: " + categories + ". " + message
        await ctx.send(message)
        current_message = await ctx.send("0/" + str(total_problem))
        count_done = 0

        for p in problems:
            p = p.upper()
            if (p not in self.problem_name_to_id):
                count_failed_problem += 1
                self.log(type_log = _NOT_FOUND_, message = p)
            else:
                problem_id = self.problem_name_to_id[p]
                if self.interator.give_access(problem_id, username, True) == False:
                    count_failed_problem += 1
                    self.log(type_log = _INTERACTION_FAILED_, message = p)
            count_done += 1
            if (count_done % 10 == 0):
                await current_message.edit(content=str(count_done) + "/" + str(total_problem) + "\nSuccess: " + str(count_done - count_failed_problem))

        message = "Successfully gave {0} problem(s) to user(s) `{1}`".format(total_problem - count_failed_problem, username)
        if (count_failed_problem > 0):
            message += "\nFailed {0} problem(s). ".format(count_failed_problem)
            message += "Using `getlog` command with query id = {0} to see failed list.".format(self.id_query)
        
        await current_message.edit(content=message)

    @commands.command(brief="Get log of give access query.", usage="[queryid]")
    async def getlog(self, ctx, query_id):
        """Get failed problems from log file of given id"""
        found = False
        for type_log in range(0, 2):
            path = _LOG_PATH_ + "{0}_{1}.txt".format(query_id, type_log) 
            if (os.path.exists(path) == False):
                continue

            with open(path, "r") as logfile: message = logfile.read()
            if (len(message) == 0):
                continue
            found = True
            title = "List not found problem(s):" 
            if type_log == _INTERACTION_FAILED_:
                title = "List problem(s) failed when interact with polygon:"
            paginator.paginate(self.bot, self.log_channel, message, title)
        if not found:
            await ctx.send("Query not found")

def setup(bot):
    bot.add_cog(BotCommand(bot))