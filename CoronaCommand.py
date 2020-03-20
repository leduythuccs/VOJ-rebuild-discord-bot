from discord.ext import commands, tasks
import discord
import asyncio
import os
import requests
from helper import table

API_PATH = 'https://code.junookyo.xyz/api/ncov-moh/data.json'
class CoronaCommand(commands.Cog):
    def __init__(self, bot):
        self.bot = bot
        self.log_channel = None
        self.cur = None
        self.looper.start()

    def get_data(self):
        r = requests.get(API_PATH).json()
        if not("success" in r and r["success"] == True):
            return None
        return r["data"]
 
    # @commands.Cog.listener()
    # async def on_ready(self):
    #     log_channel_id = int(os.getenv('DICORD_LOG_CHANNEL_ID'))
    #     self.log_channel = self.bot.get_channel(log_channel_id)

    @tasks.loop(minutes=10.0)
    async def looper(self):
        print("looping")
        nxt = self.get_data()
        if nxt is None:
            return
        pre_cases = int(self.cur['vietnam']['cases'])
        nxt_cases = int(nxt['vietnam']['cases'])
        pre_recovered = int(self.cur['vietnam']['recovered'])
        nxt_recovered = int(nxt['vietnam']['recovered'])
        pre_deaths = int(self.cur['vietnam']['deaths'])
        nxt_deaths = int(nxt['vietnam']['deaths'])

        msg = ""
        if (pre_cases != nxt_cases):
            msg += '{0} more new cases (from {1} to {2})'.format(nxt_cases - pre_cases, pre_cases, nxt_cases)
        if (pre_recovered != nxt_recovered):
            msg += '{0} more new recovered (from {1} to {2})'.format(nxt_recovered - pre_recovered, pre_recovered, nxt_recovered)
        if (pre_deaths != nxt_deaths):
            msg += '{0} more new deaths (from {1} to {2})'.format(nxt_deaths - pre_deaths, pre_deaths, nxt_deaths)
        if len(msg) == 0:
            return
        self.cur = nxt
        msg = "Vietnam just has:\n" + msg
        await self.log_channel.send(msg)

    @looper.before_loop
    async def before_looper(self):
        await self.bot.wait_until_ready()
        log_channel_id = int(os.getenv('DICORD_LOG_CHANNEL_ID'))
        self.log_channel = self.bot.get_channel(log_channel_id)
        self.cur = self.get_data()

    @commands.command(brief='Get cases in Vietnam or Global', usage="case [optional: global]")
    async def cases(self, ctx, *args):
        """ Get total cases had corona virus in Vietnam or global, default = Vietnam"""

        typ = 'vietnam'
        if len(args) > 0:
            x = str(args[0]).lower()
            if x == 'global':
                typ = x
        
        data = self.get_data()
        if data is None:
            await ctx.send('API Failed')
            return
        await ctx.send(data[typ]['cases'] + ' cases.')
    @commands.command(brief="Get full statistics")
    async def stats(self, ctx):
        
        data = self.get_data()
        if data is None:
            await ctx.send('API Failed')
            return    
        style = table.Style('{:<}  {:<}  {:<}   {:<}')
        t = table.Table(style)
        t += table.Header('Corona :(', 'Cases', 'Recovered', 'Deaths')
        t += table.Line()
        for country in data:
            name = country[0].upper() + country[1:]
            t += table.Data(name, data[country]['cases'], data[country]['recovered'], data[country]['deaths'])
        msg = "Some statistics about total corona virus cases: \n" '```\n' + str(t) + '\n```'

        await ctx.send(msg)
    
def setup(bot):
    bot.add_cog(CoronaCommand(bot))
