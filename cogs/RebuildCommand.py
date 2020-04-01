from discord.ext import commands
import discord
import asyncio
import os
from services import Polygon
import json
from datetime import datetime
from helper import paginator
from helper import helper
from helper import database
from helper import table
from helper import problem_set_helper
import requests
import time
_FIXLATEX_WEB_ = 'https://leduythuccs.github.io/fix.html'
_LOG_PATH_ = 'botlogs/'
_NOT_FOUND_ = 0
_INTERACTION_FAILED_ = 1
_ALREADY_GAVE_ = 2
_ALREADY_REVIEWED_ = 3
_TITLE_MAP_ = {
    _NOT_FOUND_: "List not found problem:",
    _INTERACTION_FAILED_: "List problem failed when interact with polygon:",
    _ALREADY_GAVE_: "List problem already gave:",
    _ALREADY_REVIEWED_: "List problem already review: "
}
_WHITE_LIST_USER_NAME_ = ['leduykhongngu', 'tuvietthao', 'MLGuy', 'codeforces']


class RebuildCommand(commands.Cog):
    def __init__(self, bot):
        self.bot = bot
        username = os.getenv('POLYGON_USERNAME')
        password = os.getenv('POLYGON_PASSWORD')
        api_key = os.getenv('POLYGON_API_KEY')
        api_secret = os.getenv('POLYGON_API_SECRET')

        self.log_channel = None
        self.commit_state = None
        self.interator = Polygon.PolygonInteractor(
            username, password, api_key, api_secret)

        self.problem_name_to_id = {}
        self.id_query = 0

        self.helper = problem_set_helper.problem_set_helper()
        self.db = database.DataUser()
        self.db_gave = database.ProblemGave()
        self.db_reviewed = database.ProblemGave(is_review=True)
        self.db_deleted = database.DeletedProblem()

    @commands.Cog.listener()
    async def on_ready(self):
        problem_json = self.interator.get_problem_list()
        self.problem_name_to_id = helper.get_problem_name_id(problem_json)

        log_channel_id = int(os.getenv('DISCORD_LOG_CHANNEL_ID'))
        self.log_channel = self.bot.get_channel(log_channel_id)

        # clear log
        logs = os.listdir(_LOG_PATH_)
        for log in logs:
            os.remove(_LOG_PATH_ + log)
        await self.log_channel.send(f'{self.bot.user.name} has connected to Discord!')

    def log(self, type_log, message):
        path = _LOG_PATH_ + "{0}_{1}.txt".format(self.id_query, type_log)
        if os.path.exists(path) == False:
            open(path, "w").close()
        if type_log == _ALREADY_GAVE_ or type_log == _ALREADY_REVIEWED_:
            open(path, "a").write(message.strip() + '\n')
        else:
            open(path, "a").write(message.strip() + ' ')

    @commands.command(brief="Re-login to polygon")
    @commands.is_owner()
    async def re_login(self, ctx):
        if self.interator.login():
            await ctx.send('VOJ-BOT logged to polygon')
        else:
            await ctx.send('Failed')

    @commands.command(brief="Change log channel.")
    @commands.is_owner()
    async def change_log(self, ctx):
        """Change bot's log channel to this channel"""
        self.log_channel = ctx.channel
        await ctx.send("Successfully set log channel to " + ctx.channel.name)

    @commands.command(brief="Get all problem sets are available.", usage="[optional: problemset_folder]")
    async def problemset(self, ctx, *args):
        """Get all problem sets are available, if problemset_folder is provide, the bot will get all problem sets of that folder instead"""
        path = "problem_set/"
        if (len(args)):
            x = args[0]
            while x[-1] == '/':
                x = x[:-1]
            path += self.helper.format_name(x) + '/'
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
        print(args)
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

    async def give_access(self, ctx, problem_set, usernames, force=False, is_review=False):
        non_white_list_username = usernames
        if not is_review:
            non_white_list_username = list(
                filter(lambda x: x not in _WHITE_LIST_USER_NAME_, usernames))
        print(force, is_review, non_white_list_username)
        type_log = _ALREADY_GAVE_
        data_base = self.db_gave
        if is_review:
            type_log = _ALREADY_REVIEWED_
            data_base = self.db_reviewed

        problems, categories = self.helper.get_give_list(problem_set)
        # erase duplicate problems
        problems = list(set(problems))
        self.id_query += 1

        count_failed_problem = 0
        total_problem = len(problems)
        message = "Doing " + str(total_problem) + " problems."
        if len(categories) >= 1:
            message = "Categories: " + categories + ". " + message
        await ctx.send(message)

        current_message = await ctx.send("0/" + str(total_problem))
        count_done = 0
        succeed_problems = []
        for p in problems:
            count_done += 1
            p = "VOJ-" + p.upper().replace('_', '-')
            if (p not in self.problem_name_to_id) or (force == False and self.db_deleted.is_deleted(p)):
                count_failed_problem += 1
                self.log(type_log=_NOT_FOUND_, message=p)
            else:
                # problem is already gave
                user = data_base.get(p)
                if (user is not None) and (not force) and (len(non_white_list_username) != 0):
                    count_failed_problem += 1
                    self.log(type_log=type_log,
                             message=p[4:] + ' ' + user + '\n')
                    continue
                # fail when interact with polygon, mostly because it was gave to that user.
                problem_id = self.problem_name_to_id[p]
                if self.interator.give_access(problem_id, usernames, True) == False:
                    count_failed_problem += 1
                    self.log(type_log=_INTERACTION_FAILED_, message=p[4:])
                    if is_review and (len(non_white_list_username) != 0):
                        data_base.set(p, str(non_white_list_username))
                else:
                    # success
                    succeed_problems.append(p[4:])
                    if len(non_white_list_username) != 0:
                        data_base.set(p, str(non_white_list_username))
            # update status to discord every 5 iterates
            if (count_done % 5 == 0):
                await current_message.edit(content=str(count_done) + "/" + str(total_problem) + "\nSuccess: " + str(count_done - count_failed_problem))

        message = ""
        if len(succeed_problems) != 0:
            message = "Successfully gave {0} problems ({2}) to `{1}`".format(
                len(succeed_problems), usernames, ' '.join(succeed_problems))

        if (count_failed_problem > 0):
            message += "\nFailed {0} problems. ".format(count_failed_problem)
            message += "Query id = {0}.".format(self.id_query)
        if is_review:
            message += "\nPlease be a careful reviewer."
        else:
            message += "\nPlease checkout " + _FIXLATEX_WEB_ + " to quick fix latex."
        await current_message.edit(content=message.strip())

    @commands.command(brief="Give permission access.", usage="[problems] [username1] [username2] [username3] ...")
    @commands.check_any(commands.is_owner(), commands.has_role('Admin'))
    async def give(self, ctx, problem_set, *args):
        """Give permission access of problem(s),
        Currently, "problems" can be: a single name or a problem set.

        """
        usernames = self.get_usernames(args)
        print(usernames)
        if len(usernames) == 0:
            await ctx.send("username not found")
            return
        await self.give_access(ctx, problem_set, usernames)

    @commands.command(brief="Force give permission access.", usage="[problems] [username1] [username2] [username3] ...")
    @commands.check_any(commands.is_owner(), commands.has_role('Admin'))
    async def _give(self, ctx, problem_set, *args):
        """Give permission access of problem(s),
        Currently, "problems" can be: a single name or a problem set.

        """
        usernames = self.get_usernames(args)
        print(usernames)
        if len(usernames) == 0:
            await ctx.send("username not found")
            return
        await self.give_access(ctx, problem_set, usernames, force=True)

    @commands.command(brief="Give permission access to reviewers.", usage="[problems] [username1] [username2] [username3] ...")
    @commands.check_any(commands.is_owner(), commands.has_role('Admin'))
    async def review(self, ctx, problem_set, *args):
        """Give permission access of problem(s) to reviewers,
        Currently, "problems" can be: a single name or a problem set.

        """
        usernames = self.get_usernames(args)
        print(usernames)
        if len(usernames) == 0:
            await ctx.send("username not found")
            return
        await self.give_access(ctx, problem_set, usernames, is_review=True)

    @commands.command(brief="Force give permission access to reviewers.", usage="[problems] [username1] [username2] [username3] ...")
    @commands.check_any(commands.is_owner(), commands.has_role('Admin'))
    async def _review(self, ctx, problem_set, *args):
        """Give permission access of problem(s) to reviewers,
        Currently, "problems" can be: a single name or a problem set.

        """
        usernames = self.get_usernames(args)
        print(usernames)
        if len(usernames) == 0:
            await ctx.send("username not found")
            return
        await self.give_access(ctx, problem_set, usernames, is_review=True, force=True)

    @commands.command(brief="Get log of give access query.", usage="[query id]")
    async def get_log(self, ctx, query_id):
        """Get failed problems from log file of given id"""
        found = False
        for type_log in range(0, 4):
            path = _LOG_PATH_ + "{0}_{1}.txt".format(query_id, type_log)
            if (os.path.exists(path) == False):
                continue

            with open(path, "r") as logfile:
                message = logfile.read()
            if (len(message) == 0):
                continue
            found = True
            title = _TITLE_MAP_[type_log]

            paginator.paginate(self.bot, self.log_channel, message, title)
        if not found:
            await ctx.send("Query not found")

    @commands.command(brief="Set polygon username to a user")
    @commands.check_any(commands.is_owner(), commands.has_role('Admin'))
    async def set(self, ctx, member: discord.Member, polygon_username: str):
        self.db.set(member.id, polygon_username)
        roles = ctx.channel.guild.roles
        s = ""
        for role in roles:
            if role.name == 'VOJ-staff':
                await member.add_roles(role)
                s = " & role `VOJ-staff`"
        await ctx.send("Polygon username " + polygon_username + s + " successfully set to " + member.display_name)

    @commands.command(brief="Get staff list")
    async def staff_list(self, ctx):
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

    def format_beautiful_string(self, user):
        if user is None:
            return "NULL"
        user = user.replace('\'', '').replace('[', '').replace(']', '')
        return user

    @commands.command(brief="Get problem's info")
    async def problem_info(self, ctx, problem_set):
        problems, categories = self.helper.get_give_list(problem_set)
        problems = list(set(problems))  # erase duplicate problems
        total_problem = len(problems)
        message = str(total_problem) + " problems."
        if len(categories) >= 1:
            message = "Categories: " + categories + ". " + message
        if total_problem > 26:
            message = "Too many problems to show. " + message
            await ctx.send(message)
            return
        style = table.Style('{:<}  {:<}  {:<}')
        t = table.Table(style)
        t += table.Header('Name', 'Fixer', 'Reviewer')
        t += table.Line()
        index = 0
        for p in problems:
            p = "VOJ-" + p.upper().replace('_', '-')
            if (p not in self.problem_name_to_id):
                continue
            fixer = self.db_gave.get(p)
            fixer = self.format_beautiful_string(fixer)
            reviewer = self.db_reviewed.get(p)
            reviewer = self.format_beautiful_string(reviewer)
            if self.db_deleted.is_deleted(p):
                fixer = 'DELETED'
                reviewer = 'DELETED'

            t += table.Data(p[4:], fixer, reviewer)

        msg = message + '```\n' + str(t) + '\n```'

        await ctx.send(msg)

    @commands.command(brief="Delete a problem.")
    @commands.is_owner()
    async def delete(self, ctx, problem_name, *args):
        reason = ' '.join(map(str, args))
        if reason == '':
            reason = 'Unknow'
        self.db_deleted.set(problem_name, reason)
        await ctx.send('Deleted ' + problem_name + '. Reason: ' + reason)

    @commands.command(brief="Restore a deleted problem.")
    @commands.is_owner()
    async def restore(self, ctx, problem_name):
        self.db_deleted.restore(problem_name)
        await ctx.send('Restored problem ' + problem_name)

    @commands.command(brief="Get list deleted problems.")
    async def deleted_list(self, ctx):
        cur = self.db_deleted.list()
        style = table.Style('{:<}  {:<}')
        t = table.Table(style)
        t += table.Header('Name', 'Reason')
        t += table.Line()
        index = 0
        for p in cur:
            t += table.Data(p, cur[p])

        msg = '```\n' + str(t) + '\n```'

        await ctx.send(msg)


def setup(bot):
    bot.add_cog(RebuildCommand(bot))
