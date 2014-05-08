UPDATE `creature_template` SET `scriptname`= 'boss_baron_silverlaine', `AIName`= '' WHERE `entry`= 3887;
UPDATE `creature_template` SET `flags_extra`= 130 WHERE `entry` IN (51047, 51080, 51085, 50934);

UPDATE `creature_template` SET `scriptname`= 'npc_wolf_master_nandos', `AIName`= '' WHERE `entry`= 50851;
UPDATE `creature_template` SET `scriptname`= 'npc_razorclaw_the_butcher', `AIName`= ''  WHERE `entry`= 50869;
UPDATE `creature_template` SET `scriptname`= 'npc_odo_the_blindwatcher', `AIName`= ''  WHERE `entry`= 50857;
UPDATE `creature_template` SET `scriptname`= 'npc_rethilgore', `AIName`= ''  WHERE `entry`= 50834;

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(93857, 'spell_sfk_summon_worgen_spirit');

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(3887, 0, 0, 'Leave this accursed place at once!', 14, 0, 100, 0, 0, 0, 'Baron Silverlaine - Aggro'),
(3887, 1, 0, 'This death is only a temporary respite from my curse.', 14, 0, 100, 0, 0, 0, 'Baron Silverlaine - Death'),
(3887, 2, 0, 'I hope your spirit finds solace.', 14, 0, 100, 0, 0, 0, 'Baron Silverlaine - Slay 1'),
(3887, 2, 1, 'May you rest in peace.', 14, 0, 100, 0, 0, 0, 'Baron Silverlaine - Slay 2');

REPLACE INTO `creature_onkill_reward` (`creature_id`, `RewOnKillRepFaction1`, `MaxStanding1`, `RewOnKillRepValue1`, `CurrencyId1`, `CurrencyCount1`) VALUES
(49709, 0, 0, 0, 395, 70); -- 5 Player Heroic
