
UPDATE `creature_template` SET `minlevel`= 86, `maxlevel`= 86, `scriptname`= 'boss_lockmaw' WHERE `entry`= 43614;
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction_A`= 16, `faction_H`= 16, `exp`= 3 WHERE `entry`= 49043;
UPDATE `creature_template` SET `scriptname`= 'npc_lct_frenzied_crocolisk' WHERE `entry`= 43658;
UPDATE `creature_template` SET `scriptname`= 'npc_lct_dust_flail_facing', `flags_extra`= 130 WHERE `entry`= 43655;
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction_A`= 16, `faction_H`= 16, `scriptname`= 'npc_lct_dust_flail_target', `flags_extra`= 130 WHERE `entry`= 43650;
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction_A`= 16, `faction_H`= 16, `exp`= 3, `scriptname`= 'npc_lct_augh_battle' WHERE `entry` IN (45379, 45378, 49045);

UPDATE `creature_template` SET `scriptname`= 'npc_lct_augh'  WHERE `entry`= 45377;
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(45377, 0, 0, 'Bwaaaah! You no take da treasure!!!', '12', '0', '0', '0', '0', '0', 'Augh - Intro'),
(45377, 1, 0, 'Bwagauugh!!! Augh feed you to da crocs!', 12, 0, 100, 0, 0, 0, 'Augh'),
(45379, 0, 0, 'Bwagauugh!!! Augh feed you to da crocs!', 12, 0, 100, 53, 0, 0, 'Augh to Add Stalker'),
(45379, 1, 0, 'Gwaaaaaaaaaaaahhh!!!', 12, 0, 100, 0, 0, 0, 'Augh to Add Stalker'),
(49045, 0, 0, '%s appears from the distance!', '41', '0', '0', '0', '0', '0', 'Augh - Outro 1'),
(49045, 1, 0, 'GAAAH! How you kill crocs?!', '12', '0', '0', '0', '0', '0', 'Augh - Outro 2'),
(49045, 2, 0, 'Augh smart! Augh already steal treasure while you no looking!', '12', '0', '0', '0', '0', '0', 'Augh - Outro 3');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(107018, 'spell_lct_paralytic_blow_dart');

REPLACE INTO `creature_onkill_reward` (`creature_id`, `RewOnKillRepFaction1`, `MaxStanding1`, `RewOnKillRepValue1`, `CurrencyId1`, `CurrencyCount1`) VALUES
(43614, 0, 0, 0, 395, 30), -- 5 Player Normal
(49045, 0, 0, 0, 395, 70); -- 5 Player Heroic
