const { roleMention } = require('discord.js');
const Discord = require('discord.js');

const client = new Discord.Client({intents: []});

client.once('ready', () => {
     console.log('Bot is online')
});


client.on('message', message => {
    if (message.guild.members.get(bot.user.id).hasPermission("MANAGE_NICKNAMES") && message.guild.members.get(bot.user.id).hasPermission("CHANGE_NICKNAME")) {
        message.guild.members.get(bot.user.id).setNickname("Nickname Here");
    } else {
        message.channel.sendMessage("I dont have the permissons to change my nickname in this server.");
    }
})















client.login('MTA4Mzc3MTE3Nzg0OTMzMTc2Mg.GcK-0v.KQq73Uz2SGRWx4zLvY9JHf0o6B4mM9WcMPlhMw');

