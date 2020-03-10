from discord.ext import commands
import discord
import asyncio
import os
import services
import json 
from datetime import datetime
from helper import paginator
from helper import helper
from helper import database
from helper import table
import requests
import time

_WAIT_TIME_ = 1 #minute
_LOG_PATH_ = 'botlogs/'
_NOT_FOUND_ = 0
_INTERACTION_FAILED_ = 1
class Database:
    def __init__(self):
        self.file_path = 'database/user_database.json'
        with open(self.file_path, "r") as json_file: self.cur = json.load(json_file)

    def load(self):
        with open(self.file_path, "r") as json_file: self.cur = json.load(json_file)

    def set(self, id_discord, username_polygon):
        self.load()
        if id_discord in self.cur:
            self.cur.pop(id_discord)
    
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

        self.problem_name_to_id = {}
        self.id_query = 0
        self.start_time = 0
        self.dir_map = {}
        self.in_loop = False
        
        self.db = database.DataUser()

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
        print(self.dir_map)

    @commands.Cog.listener()
    async def on_ready(self):
        self.start_time = time.time()
        problem_json = self.interator.get_problem_list()
        self.commit_state = helper.get_commit_state(problem_json)
        self.problem_name_to_id = helper.get_problem_name_id(problem_json)
        log_channel_id = int(os.getenv('DICORD_LOG_CHANNEL_ID'))
        self.log_channel = self.bot.get_channel(log_channel_id)
        self.mapping_file_name()

    def log(self, type_log, message):
        path = _LOG_PATH_ + "{0}_{1}.txt".format(self.id_query, type_log) 
        if os.path.exists(path) == False:
            open(path, "w").close()
        open(path, "a").write(message.strip() + ' ')
    
    def get_new_commit(self):
        current_commit_state = helper.get_commit_state(self.interator.get_problem_list())
        message = ""
        for name in self.commit_state:
            if (current_commit_state[name] != self.commit_state[name]):
                message += name + " "
                self.commit_state[name] = current_commit_state[name]
        return message

    @commands.command(brief="Update problemset.")
    async def update(self, ctx):
        self.mapping_file_name()

    @commands.command(brief="Re-login to polygon") 
    async def re_login(self, ctx):
        if self.interator.login():
            await ctx.send('VOJ-BOT logged to polygon')
        else:
            await ctx.send('Failed')

    @commands.command(brief="Change log channel. [owner's command]")
    @commands.is_owner()
    async def change_log(self, ctx):
        """Change bot's log channel to this channel""" 
        self.log_channel = ctx.channel
        await ctx.send("Successfully set log channel to " + ctx.channel.name)
        
    @commands.command(brief="Get new commit each minute. [owner's command]")
    @commands.is_owner()
    async def loop(self, ctx):
        if (self.log_channel is None):
            await ctx.send("Log channel not found.")
            return 
        if (self.in_loop):
            await ctx.send("Already loop")
            return
        await self.log_channel.send("Starting to get new commit every minute.")
        self.in_loop = True
        while True:
            message = self.get_new_commit()
            now = datetime.now()
            current_time = now.strftime("%Hh:%Mm:%Ss")
            if (len(message) > 0):
                title = current_time + ": In past " + str(_WAIT_TIME_)  \
                        + "minute(s), these problem(s) has new commit: "
                if len(message) < 1000:
                    message = title + "`" + message + "`"
                    await self.log_channel.send(message)
                else:
                    paginator.paginate(self.bot, self.log_channel, message, title)
            await asyncio.sleep(_WAIT_TIME_ * 60)

    @commands.command(brief="Check if bot is still alive. Also prints bot uptime")
    async def ping(self, ctx):
        await ctx.send("I have been running for " + 
                        helper.pretty_time_format(time.time() - self.start_time))

    @commands.command(brief="Kill bot. [owner's command]")
    @commands.is_owner()
    async def kill(self, ctx):
        """Kill bot"""
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

    def get_give_list(self, sets):
        
        problem_set = self.format_path(sets)

        path = "problem_set/"
        problems = []
        folders = []
        print(";" + problem_set + ";")
        if len(sets) >= 3 and sets[-3:].upper() == "ALL" != -1:
            if problem_set == "ALL":
                folders = [path + self.format_name("ALL") + ".txt"]
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
    
        problems = list(set(problems)) # erase duplicate problems
        print(problems)
        return problems, categories

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
    def get_usernames(self, args):
        usernames = []
        for arg in args:
            name = ""
            if len(arg) > 3 and arg[0] == '<':
                arg = arg[3:-1]
                arg = self.db.get(arg)
                if arg == "":
                    continue
            usernames.append(arg)
        return usernames

    @commands.command(brief="Give permission access. [owner's command]", usage="[problems] [username1] [username2] [username3] ...")
    @commands.check_any(commands.is_owner(),commands.has_role('Admin'))
    async def give(self, ctx, problem_set, *args):
        """Give permission access of problem(s),
        Currently, "problems" can be: a single name or a problem set.
        [owner's command]
        """
        problems, categories = self.get_give_list(problem_set)

        username = self.get_usernames(args)
        print(username)
        if len(username) == 0:
            await ctx.send("username not found")
            return

        self.id_query += 1

        count_failed_problem = 0
        total_problem = len(problems)
        message = "Doing " + str(total_problem) + " problems, it might takes a couple of minutes"
        if len(categories) >= 1:
            message = "Problem categories: " + categories + ". " + message
        await ctx.send(message)
        current_message = await ctx.send("0/" + str(total_problem))
        count_done = 0
        succeed_problems = []
        for p in problems:
            p = "VOJ-" + p.upper()
            if (p not in self.problem_name_to_id):
                count_failed_problem += 1
                self.log(type_log = _NOT_FOUND_, message = p)
            else:
                problem_id = self.problem_name_to_id[p]
                if self.interator.give_access(problem_id, username, True) == False:
                    count_failed_problem += 1
                    self.log(type_log = _INTERACTION_FAILED_, message = p[4:])
                else:
                    succeed_problems.append(p[4:])
            count_done += 1
            if (count_done % 5 == 0):
                await current_message.edit(content=str(count_done) + "/" + str(total_problem) + "\nSuccess: " + str(count_done - count_failed_problem))

        message = "Successfully gave {0} problem(s) ({2}) to `{1}`".format(len(succeed_problems), username, ' '.join(succeed_problems))
        
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

    @commands.command(brief="Set polygon username of a user")
    async def set(self, ctx, member: discord.Member, polygon_username: str):
        self.db.set(member.id, polygon_username)
        roles = ctx.channel.guild.roles
        s = ""
        for role in roles:
            if role.name == 'VOJ-staff':
                await member.add_roles(role)
                s = " & role `VOJ-staff`"
        await ctx.send("Polygon username " + polygon_username + s + " successfully set to "  + member.display_name)

    @commands.command(brief="Get staff list")
    async def list(self, ctx):
        cur = self.db.list()
        style = table.Style('{:>}  {:<}  {:<}')
        t = table.Table(style)
        t += table.Header('#', 'Name', 'Polygon')
        t += table.Line()
        index = 0
        for user_id in cur:
            member = ctx.guild.get_member(int(user_id))
            if member is None:
                continue
            index += 1
            name = member.display_name
            t += table.Data(index, name, cur[user_id])
            
        msg = '```\n' + str(t) + '\n```'

        await ctx.send(msg)

def setup(bot):
    bot.add_cog(BotCommand(bot))
