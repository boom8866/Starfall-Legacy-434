UPDATE `creature_template` SET `scriptname`= 'boss_commander_springvale', `AIName`= ''  WHERE `entry`= 4278;
UPDATE `creature_template` SET `flags_extra`= 130, `unit_flags`= unit_flags | 256 | 512 WHERE `entry`= 50547;
UPDATE `creature_template` SET `faction_A`= 14, `faction_H`= 14, `minlevel`= 87, `maxlevel`= 87, `flags_extra`= 130, `unit_flags`= unit_flags | 256 | 512 WHERE `entry` IN (50503, 51258);

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(4278, 0, 0, 'Intruders in the keep! To arms!', 14, 0, 100, 0, 0, 0, 'Commander Springvale - Aggro'),
(4278, 1, 0, 'Repel the intruders!', 14, 0, 100, 0, 0, 0, 'Commander Springvale - Summon Adds'),
(4278, 2, 0, 'The attackers weaken!', 14, 0, 100, 0, 0, 0, 'Commander Springvale - Slay 1'),
(4278, 2, 1, 'One step closer to victory!', 14, 0, 100, 0, 0, 0, 'Commander Springvale - Slay 2'),
(4278, 3, 0, 'Our vigilance is eternal...', 14, 0, 100, 0, 0, 0, 'Kommandant Grüntal');

DELETE FROM `creature` WHERE `guid` IN (6956, 6954);
DELETE FROM `creature_addon` WHERE `guid` IN (6956, 6954);

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(7054, 'spell_sfk_forsaken_ability');

REPLACE INTO `creature_onkill_reward` (`creature_id`, `RewOnKillRepFaction1`, `MaxStanding1`, `RewOnKillRepValue1`, `CurrencyId1`, `CurrencyCount1`) VALUES
(49710, 0, 0, 0, 395, 70); -- 5 Player Heroic
