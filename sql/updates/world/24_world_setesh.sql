
UPDATE `creature_template` SET `speed_walk`= 2.8 WHERE `entry` IN (48776, 39732);
UPDATE `creature_template` SET `flags_extra`= 130, `minlevel`= 85, `maxlevel`= 85, `faction_A`= 14, `faction_H`= 14, `unit_flags`= 33587264, `unit_flags2`= 34816, `modelid1`=1126, `modelid2`= 16925,  `scriptname`= 'npc_hoo_reign_of_chaos' WHERE `entry`= 41168;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 14, `faction_H`= 14, `unit_flags`= 33587264, `unit_flags2`= 32768, `exp`= 3 WHERE `entry` IN (48769, 41055);
UPDATE `creature_template` SET `scriptname`= 'npc_hoo_chaos_portal' WHERE `entry`= 41055;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 14, `faction_H`= 14, `exp`= 3 WHERE `entry` IN (41208, 48888);
UPDATE `creature_template` SET `flags_extra`= 130, `minlevel`= 85, `maxlevel`= 85, `faction_A`= 14, `faction_H`= 14, `unit_flags`= 33587264, `unit_flags2`= 34816, `modelid1`=1126, `modelid2`= 16925,  `scriptname`= 'npc_hoo_chaos_blast' WHERE `entry`= 41041;
UPDATE `creature_template` SET `flags_extra`= 130, `minlevel`= 85, `maxlevel`= 85, `faction_A`= 14, `faction_H`= 14, `unit_flags`= 33587264, `unit_flags2`= 2048, `modelid1`=1126, `modelid2`= 16925, `InhabitType`= 4,  `scriptname`= 'npc_hoo_chaos_seed' WHERE `entry`= 41126;

DELETE FROM `creature_text` WHERE `entry`= 39732;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(39732, 0, 0, 'You fear that which you cannot control. But can you control your fear?', 14, 0, 100, 0, 0, 18553, 'Setesh - Aggro'),
(39732, 1, 0, 'Embrace the end.', 14, 0, 100, 0, 0, 18555, 'Setesh - Aggro'),
(39732, 1, 1, 'Do you understand now?', 14, 0, 100, 0, 0, 18553, 'Setesh - Aggro'),
(39732, 2, 0, 'Yes! Harness... your... hatred.', 14, 0, 100, 0, 0, 18552, 'Setesh - Death');

DELETE FROM `creature` WHERE `id`= 41055;
DELETE FROM conditions WHERE SourceEntry IN (77030, 89872, 76784, 77607, 76676, 77128);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 1, 77030, 0, 0, 31, 0, 3, 39732, 0, 0, 0, '', 'Reign of Chaos - Target Setesh'),
(13, 1, 89872, 0, 0, 31, 0, 3, 39732, 0, 0, 0, '', 'Reign of Chaos - Target Setesh'),
(13, 1, 77607, 0, 0, 31, 0, 3, 41208, 0, 0, 0, '', 'Chaos Portal Summon Visual - Target Void Sentinel'),
(13, 1, 76676, 0, 0, 31, 0, 3, 41041, 0, 0, 0, '', 'Chaos Blast - Target Chaos Blast Dummy'),
(13, 1, 77128, 0, 0, 31, 0, 3, 41055, 0, 0, 0, '', 'Chaos Burn - Target Chaos Portal'),
(13, 1, 76784, 0, 0, 31, 0, 3, 41055, 0, 0, 0, '', 'Chaos Portal Channel - Target Chaos Portal');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES

(76674, 'spell_hoo_chaos_blast');

REPLACE INTO `creature_onkill_reward` (`creature_id`, `RewOnKillRepFaction1`, `MaxStanding1`, `RewOnKillRepValue1`, `CurrencyId1`, `CurrencyCount1`) VALUES
(48776, 0, 0, 0, 395, 70); -- 5 players heroic
