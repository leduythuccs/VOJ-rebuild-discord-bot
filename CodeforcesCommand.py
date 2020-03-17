from discord.ext import commands
import discord
import asyncio
import os
from services import Codeforces
import json 
from datetime import datetime
from helper import paginator
from helper import helper
from helper import database
from helper import table
from helper import problem_set_helper
import requests
import time
class CodeforcesCommand(commands.Cog):
    def __init__(self, bot):
        self.bot = bot
        username = os.getenv('CODEFORCES_USERNAME')
        password = os.getenv('CODEFORCES_PASSWORD')
        self.interator = Codeforces.CodeforcesInteracter(username, password, api_key, api_secret)
    @commands.Cog.listener()
    async def on_ready(self):
        problem_set_helper.mapping_file_name()

    @commands.command(brief="Create a mashup by problemset", usage="[Contest name] [problem_set] [duration]")
    @commands.is_owner()
    async def create_mashup(self, ctx, contest_name, problem_set, duration):
        problems, categories = problem_set_helper.get_give_list(problem_set)
        await ctx.send('This commnand is developping, pls comeback later')
        pass

    @commands.command(brief="Re-login to codeforces") 
    async def re_login_cf(self, ctx):
        if self.interator.login():
            await ctx.send('VOJ-BOT logged to codeforces')
        else:
            await ctx.send('Failed')

def setup(bot):
    bot.add_cog(CodeforcesCommand(bot))
