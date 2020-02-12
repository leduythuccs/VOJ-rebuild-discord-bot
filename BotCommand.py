from discord.ext import commands
import os
import services
import json 

class BotCommand(commands.Cog):
    def __init__(self, bot):
        self.bot = bot
        username = os.getenv('POLYGON_USERNAME')
        password = os.getenv('POLYGON_PASSWORD')
        api_key = os.getenv('POLYGON_API_KEY')
        api_secret = os.getenv('POLYGON_API_SECRET')
        self.interator = services.PolygonInteracter(username, password, api_key, api_secret)
        self.un_complete = []
        self.problem_name_to_id = json.load(open("list_problems.json", "r"))
    

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

        self.un_complete = []
        await ctx.send("Doing " + str(len(problems)) + " problems, it might takes a couple of minutes")
        for p in problems:
            p = p.upper()
            if (p not in self.problem_name_to_id):
                self.un_complete.append(p)
            else:
                problem_id = self.problem_name_to_id[p]
                print("problem id = {0}, problem name = {1}".format(problem_id, p))
                self.interator.give_access(problem_id, username)

        message = "Successfully gave {0} problem(s) to user(s) `{1}`".format(len(problems) - len(self.un_complete), username)
        if (len(self.un_complete) > 0):
            message += "\nFailed {0} problem(s) \n".format(len(self.un_complete))
            message += "Using `failed` command to see failed list."
        await ctx.send(message)


    @commands.command(brief="Get failed problem(s) when give access")
    async def failed(self, ctx):
        message = "List failed = `"
        for p in self.un_complete:
            message += p + " "
        if (len(message) > 500):
            message = message[:500]
            message = "Because the failed list is too long, this is its first 500 charaters:\n" + message
        message += "`"
        if (len(self.un_complete) == 0):
            message = "Don't have any failed problem."
        await ctx.send(message)
    

def setup(bot):
    bot.add_cog(BotCommand(bot))