from discord.ext import commands
import os
import services

class BotCommand(commands.Cog):
    def __init__(self, bot):
        self.bot = bot
        self.interator = services.PolygonInteracter(None, None)
        self.un_complete = []
    @commands.Cog.listener()
    async def on_ready(self):
        username = os.getenv('POLYGON_USERNAME')
        password = os.getenv('POLYGON_PASSWORD')
        print(username, password)
        self.interator = services.PolygonInteracter(username, password)
    

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


    @commands.command(brief="Give permission access", usage="[problems] [username]")
    async def give(self, ctx, problem_set, username):
        """Give permission access of problem(s),
        Currently, "problems" can be: a single name or a problem set
        """
        path = "problem_set/" + problem_set + ".txt"
        problems = []
        if (os.path.exists(path)):
            problems = list(map(lambda x: x.strip('\n'), open(path, "r").readlines()))
        else:
            problems = [problem_set]
        self.un_complete = []
        await ctx.send("Doing " + str(len(problems)) + " problems, it might takes a couple of minutes")
        for p in problems:
            if self.interator.give_access(p, username) == False:
                self.un_complete.append(p)

        message = "Successfully gave {0} problem(s) to user `{1}` \n".format(len(problems) - len(self.un_complete), username)
        message += "Failed {0} problem(s) \n".format(len(self.un_complete))
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