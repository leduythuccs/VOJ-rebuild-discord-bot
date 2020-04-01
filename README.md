# VOJ-rebuild-bot
 A discord bot which helps speed up migration VOJ problems to Codeforces by using polygon, codeforces APIs.

## Features
### Polygon
- Give permission access of a (list of) problem(s)  to other users.

### Codeforces
- Create new mashup using polygon links
- Edit mashup information
- Run package solutions
- Add mashup contest to a codeforces group

### Other
- Manage:
    - Staff list
    - Problems list: see doing problems, deleted problems, reviewed problems ...
- Some git commands to update the bot.
- Some commands about nCoVi virus.

## Installation
Clone this repository 
- `python pip install -r requirements`
- Base on file `.env-example`, create file `.env` and fill all the data: bot token, account polygon (for polygon commands), account codeforces (for codeforces commands), ...

## How to use
- Create a discord bot, add it to your discord server.
- Then use `python main.py` to run the bot. Remember to edit data in `.env`.
- Use `;rebuild help` to see list command

## Notes
- There is some commands required `Admin` role. If you a not bot's owner, you will need `Admin` role to use those commands.
- You can update the bot (get new commit from this repository) by using `;rebuild git_pull` command. Then you can use `;rebuild restart` to restart the bot (you don't need to run it again, it's very useful since I'm running the bot in a VPS).

## About the APIs
Since the bot doesn't need many APIs, I didn't add all the API I have into [services](/services) but I'll upload it soon (in an other repository). 

Currently, for polygon APIs, you can see [this repository](https://github.com/t-rekttt/polygon-api/tree/master/built) (written in nodejs). 
