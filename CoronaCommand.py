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

    def get_data(self):
        r = requests.get(API_PATH).json()
        if not("success" in r and r["success"] == True):
            return None
        return r["data"]
 
    # @commands.Cog.listener()
    # async def on_ready(self):
    #     pass

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
        style = table.Style('{:<}  {:<}  {:<}')
        t = table.Table(style)
        t += table.Header(' ', 'Vietnam', 'Global')
        t += table.Line()
        t += table.Data('Cases', data['vietnam']['cases'], data['global']['cases'])
        t += table.Data('Recovered', data['vietnam']['recovered'], data['global']['recovered'])
        t += table.Data('deaths', data['vietnam']['deaths'], data['global']['deaths'])
        msg = "Some statistics about corona case: \n" '```\n' + str(t) + '\n```'

        await ctx.send(msg)
    
def setup(bot):
    bot.add_cog(CoronaCommand(bot))
