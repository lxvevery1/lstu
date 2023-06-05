import datetime
import discord
from discord.ext import commands

intents = discord.Intents.default()
intents.members = True
intents.guilds = True
bot = commands.Bot(command_prefix='!', intents=intents)
adminRole = "@Преподаватель"

async def assign_role_by_name(member):
    name = member.display_name.split(',')[0]
    if name != adminRole:
        role = discord.utils.get(member.guild.roles, name=name)
        if role:
            await member.add_roles(role)
            print(f"Role '{role.name}' added to '{member.display_name}'")

async def remove_role_by_name(member):
    name = member.display_name.split(',')[0]
    if name != adminRole:
        role = discord.utils.get(member.guild.roles, name=name)
        if role:
            await member.remove_roles(role)
            print(f"Role '{role.name}' removed from '{member.display_name}'")

@bot.event
async def on_member_join(member):
    await assign_role_by_name(member)
    print(f"'{member.display_name}' joined the server and got their role assigned!")

@bot.event
async def on_member_update(before, after):
    if before.display_name != after.display_name:
        print(f"User '{before.display_name}' updated their display name to '{after.display_name}'")
        await assign_role_by_name(after)
        await remove_role_by_name(before)

#@bot.event
#async def on_member_update(member):
#    current_month = datetime.datetime.now().month
#    current_year = datetime.datetime.now().year
#    if current_month in [1, 2, 3, 4, 5, 6]:  # Если текущий месяц с первой половины года (второй семестр)
#        semester = "В"
#    else:
#        semester = "О"  # Иначе (вторая половина года, т.е. первый семестр)
#    group = member.display_name.split('-')[0]
#    teleginGroups = ["АС", "ЭМТ", "АТТ", "иАС", "ОЗ", "СДП"]
#    haritonenkoGroups = ["ЭП", "САУ", "МА"]
#    if (group == teleginGroups)
#        role = current_year +


bot.run('MTA4Mzc3MTE3Nzg0OTMzMTc2Mg.GnkTSm.dLFQVow0kVyJx4xqu0fvKYCRoLtgG1nXn6azws')