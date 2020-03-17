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
        
        self.helper = problem_set_helper.problem_set_helper()
        self.interator = Codeforces.CodeforcesInteracter(username, password)
        data = open(os.path.join('database', 'polygon_mapping_links.txt'), 'r', encoding='utf-8').read().strip().split('\n')
        for i, item in enumerate(data):
            data[i] = list(item.split(' '))
        self.polygon_links = {}
        self.db_deleted = database.DeletedProblem()
        for x in data:
            link, name = x
            self.polygon_links[name.upper().replace('-', '_')] = link
    # @commands.Cog.listener()
    # async def on_ready(self):
    #     problem_set_helper.mapping_file_name()
    def get_polygon_link(self, problem_names, err):
        problem_json = []
        for p in problem_names:
            p = p.upper().replace('-', '_')
            if p not in self.polygon_links:
                print(p + ' not found')
                err += p + ' not found.\n'
            problem_json.append({'url' : self.polygon_links[p]})
        if err != '':
            return None
        return problem_json
    def get_link_codeforces(self, problems, mashup_id):
        cur = self.db_deleted.list()
        style = table.Style('{:<}  {:<}')
        t = table.Table(style)
        t += table.Header('Name', 'Link')
        t += table.Line()
        pattern = 'https://codeforces.com/group/FLVn1Sc504/contest/{0}/problem/{1}'
        cur_char = 'A'
        res = ''
        for p in problems:
            p = p.upper()
            t += table.Data(p, pattern.format(mashup_id, cur_char))
            cur_char = chr(ord(cur_char) + 1)
        msg = '```\n' + str(t) + '\n```'
        return msg
    @commands.command(brief="Create a mashup by problemset", usage="[problem_set] [duration]")
    @commands.is_owner()
    async def create_mashup(self, ctx, problem_set, duration):
        problems, categories = self.helper.get_give_list(problem_set)
        # remove deleted problem
        problems = list(filter(lambda x: not self.db_deleted.is_deleted(x), problems))
        contest_name = categories.strip()
        err = ''
        problem_json = self.get_polygon_link(problems, err)
        if problem_json is None:
            await ctx.send('Error: ' + err)
            return
        print(contest_name)
        print(problem_json)
        await ctx.send('developing, pls return later')
        return
        res, contest_id = self.interator.create_mashup(contest_name, problem_json, duration)
        if not res:
            ctx.send('Error when interactive with CF: ' + str(contest_id))
            return
        message = 'Mashup name = ' + contest_name + '.\nMashup id = ' + contest_id + '.\n'
        message += 'Please add those links to admin sheet:' + self.get_link_codeforces() 
        await ctx.send(message)
    @commands.command(brief="Re-login to codeforces") 
    async def re_login_cf(self, ctx):
        if self.interator.login():
            await ctx.send('VOJ-BOT logged to codeforces')
        else:
            await ctx.send('Failed')

def setup(bot):
    bot.add_cog(CodeforcesCommand(bot))
