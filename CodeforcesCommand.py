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
seasons = {
    '2020-2021',
    '2019-2020',
    '2018-2019',
    '2017-2018',
    '2016-2017',
    '2015-2016',
    '2014-2015',
    '2013-2014',
    '2012-2013',
    '2011-2012',
    '2010-2011',
    '2009-2010',
    '2008-2009',
    '2007-2008',
    '2006-2007',
    '2005-2006',
    '2004-2005',
    '2003-2004',
    '2002-2003',
    '2001-2002',
    '2000-2001',
    '1999-2000',
    '1998-1999',
    '1997-1998',
    '1996-1997',
    '1995-1996',
    '1991-1992'
}
class CodeforcesCommand(commands.Cog):
    def __init__(self, bot):
        self.bot = bot
        username = os.getenv('CODEFORCES_USERNAME')
        password = os.getenv('CODEFORCES_PASSWORD')
        self.group_id = os.getenv('CODEFORCES_GROUP_ID')
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
        current_message = await ctx.send("Creating mashup " + contest_name)
        res, contest_id = self.interator.create_mashup(contest_name, problem_json, duration)
        if not res:
            await current_message.edit(content='Error when interact with CF. Please see local log file.')
            print(str(contest_id))
            return False
        message = 'Mashup name = ' + contest_name + '.\nMashup id = ' + str(contest_id) + '.\n'
        await current_message.edit(content = message)
        return contest_id
    
    @commands.command(brief="Add a mashup to VNOI CF group")
    @commands.is_owner()
    async def add_contest(self, ctx, mashup_id):
        if not mashup_id.isdigit():
            await ctx.send('Mashup id must be a number.')
            return False
        if self.group_id is None:
            await ctx.send('Codeforces group id not found.')
            return False
        url = self.interator.add_mashup_to_group(mashup_id, self.group_id)
        if url == None:
            message = "Cannot add {0} to VNOI CF group.".format(mashup_id)
        else:
            message = "Contest link: " + url
        await ctx.send(message)
        return True
    @commands.command(brief="Edit mashup info")
    @commands.is_owner()
    async def edit_info_mashup(self, ctx, mashup_id, contest_type, difficulty, *season):
        if not mashup_id.isdigit():
            await ctx.send('Mashup id must be a number.')
            return False
        if not difficulty.isdigit() or int(difficulty) < 0 or int(difficulty) > 5:
            await ctx.send('Difficulty must be a integer in [0, 5]')
            return False
        if len(season) == 0:
            season = ''
        else:
            if type(season[0]) is tuple:
                season = season[0]
            season = '-'.join(season)
            if season not in seasons:
                await ctx.send('Season {0} not found.'.format(season))
        if contest_type != 'IOI' and contest_type != 'ICPC':
            await ctx.send("Contest type must be `IOI` or `ICPC`.")
            return False
        prefix = 'Editing:\n'
        message = '- Contest id: {0}.\n- Contest type: {1}.\n - Difficulty: {2} stars.\n- Season: {3}.\n'.format(mashup_id, contest_type, difficulty, season)
        current_message = await ctx.send(prefix + message)
        self.interator.edit_mashup_info(str(mashup_id), contest_type, str(difficulty), season)
        suffix = 'Done. Please check the result, the bot cannot confirm it.'
        await current_message.edit(content= message + suffix)
        return True
    @commands.command(brief="Create mashup and add it to VNOI CF group")
    @commands.is_owner()
    async def full_create_mashup(self, ctx, problem_set, duration, contest_type, difficulty, *season):
        mashup_id = await self.create_mashup(ctx, problem_set, duration)
        if mashup_id == False:
            return False
        if len(season) == 0:
            season = ''
        result = await self.edit_info_mashup(ctx, str(mashup_id), contest_type, difficulty, season)
        if result == False:
            return False
        result = await self.add_contest(ctx, str(mashup_id))

        return result

    @commands.command(brief="Re-login to codeforces") 
    @commands.is_owner()
    async def re_login_cf(self, ctx):
        if self.interator.login():
            await ctx.send('VOJ-BOT logged to codeforces')
        else:
            await ctx.send('Failed')

def setup(bot):
    bot.add_cog(CodeforcesCommand(bot))
