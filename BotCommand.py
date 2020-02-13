from discord.ext import commands
import os
import services
import json 
from helper import paginator

class BotCommand(commands.Cog):
    def __init__(self, bot):
        self.bot = bot
        username = os.getenv('POLYGON_USERNAME')
        password = os.getenv('POLYGON_PASSWORD')
        api_key = os.getenv('POLYGON_API_KEY')
        api_secret = os.getenv('POLYGON_API_SECRET')
        self.interator = services.PolygonInteracter(username, password, api_key, api_secret)
        self.problem_name_to_id = json.load(open("list_problems.json", "r"))
        self.id_query = 0
        open("botlogs/failed_0.log", "w")
    

    def log(self, message):
        open("botlogs/failed_" + str(self.id_query) + ".log", "a").write(message.strip() + '\n')
    
    @commands.command(brief="Check if bot is still alive")
    async def ping(self, ctx):
        await ctx.send("I'm still alive")
    

    @commands.command(brief="Kill bot")
    @commands.is_owner()
    async def kill(self, ctx):
        """Kill bot, only bot's owner can call this command"""
        await ctx.send("Dying")
        exit(0)


    @commands.command(brief="Get all problem sets are available")
    async def problemset(self, ctx):
        path = "problem_set/"
        file_list = os.listdir(path)
        message = "`"
        for p in file_list:
            message += p[:p.find('.')] + " "
        message += "`"
        await ctx.send(message)


    @commands.command(brief="Give permission access", usage="[problems] [username1] [username2] [username3] ...")
    @commands.is_owner()
    async def give(self, ctx, problem_set, *args):
        """Give permission access of problem(s),
        Currently, "problems" can be: a single name or a problem set
        """
        path = "problem_set/" + problem_set + ".txt"
        username = args
        problems = []
        if (os.path.exists(path)):
            problems = list(map(lambda x: x.strip('\n'), open(path, "r").readlines()))
        else:
            problems = [problem_set]

        count_failed_problem = 0
        total_problem = len(problems)

        await ctx.send("Doing " + str(total_problem) + " problems, it might takes a couple of minutes")
        current_message = await ctx.send("0/" + str(total_problem))
        count_done = 0

        for p in problems:
            p = p.upper()
            if (p not in self.problem_name_to_id):
                count_failed_problem += 1
                self.log(p + ": don't have it on polygon")
            else:
                problem_id = self.problem_name_to_id[p]
                if self.interator.give_access(problem_id, username, True) == False:
                    count_failed_problem += 1
                    self.log(p + ": failed when interact with polygon")
            count_done += 1
            if (count_done % 10 == 0):
                current_message.edit(content=str(count_done) + "/" + str(total_problem) + "\nSuccess: " + str(count_done - count_failed_problem))

        message = "Successfully gave {0} problem(s) to user(s) `{1}`".format(total_problem - count_failed_problem, username)
        if (count_failed_problem > 0):
            message += "\nFailed {0} problem(s). ".format(count_failed_problem)
            message += "Using `failed` command with query id = {0} to see failed list.".format(self.id_query)
            self.id_query += 1
            open("botlogs/failed_" + str(self.id_query) + ".log", "w")
        
        await current_message.edit(content=message)


    @commands.command(brief="Get log of give access query", usage="[queryid]")
    async def getlog(self, ctx, query_id):
        """Get failed problems from log file of given id"""
        
        if (os.path.exists("botlogs/failed_" + str(query_id) + ".log") == False):
            await ctx.send("Query " + str(query_id) +" not found")
            return

        with open("botlogs/failed_" + str(query_id) + ".log", "r") as logfile: message = logfile.read()
        paginator.paginate(self.bot, ctx, message, "Query " + str(query_id) + "'s failed list:")
    

def setup(bot):
    bot.add_cog(BotCommand(bot))