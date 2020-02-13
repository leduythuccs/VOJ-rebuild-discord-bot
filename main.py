import os
from dotenv import load_dotenv
from discord.ext import commands

current_path = os.path.dirname(os.path.abspath(__file__))
os.chdir(current_path)
load_dotenv()
if (os.path.exists("botlogs") == False):
    os.mkdir("botlogs")
token = os.getenv('DISCORD_TOKEN')

# bot 
bot = commands.Bot(command_prefix=';rebuild ')
print(bot.command_prefix)
bot.load_extension("BotCommand")
@bot.event
async def on_ready():
    print(f'{bot.user.name} has connected to Discord!')

    
@bot.event
async def on_command_error(ctx, error):
    print(error)
    await ctx.send('Error: ' + str(error))
    
bot.run(token)