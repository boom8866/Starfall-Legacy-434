UPDATE `creature_template` SET `minlevel`= 86, `maxlevel`= 86, `scriptname`= 'boss_siamat' WHERE `entry`= 44819;
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction_A`= 16, `faction_H`= 16, `exp`= 3 WHERE `entry`= 51088;
UPDATE `creature_template` SET `AIName`= '', `InhabitType`= 4, `scriptname`= 'npc_lct_slipstream' WHERE `entry` IN (48092, 48097);
UPDATE `creature_template` SET `flags_extra`= 130 WHERE `entry`= 48097;
UPDATE `creature_template` SET `minlevel`= 84, `maxlevel`= 84, `faction_A`= 16, `faction_H`= 16, `exp`= 3, `scriptname`= 'npc_lct_servant_of_siamat' WHERE `entry` IN (45259, 45268, 45269);
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 16, `faction_H`= 16, `exp`= 3 WHERE `entry`In (49256, 49257, 49258);
UPDATE `creature_template` SET `minlevel`= 84, `maxlevel`= 84, `faction_A`= 16, `faction_H`= 16, `exp`= 3, `scriptname`= 'npc_lct_minion_of_siamat' WHERE `entry`= 44704;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 16, `faction_H`= 16, `exp`= 3 WHERE `entry`= 49260;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 16, `faction_H`= 16, `flags_extra`= 130, `scriptname`= 'npc_lct_cloud_burst' WHERE `entry`= 44541;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`= 48092;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(48092, 93970, 1, 0);

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(44819, 0, 0, 'I. AM. UNLEASHED!', 14, 0, 100, 0, 0, 20231, 'Siamat - Intro'),
(44819, 1, 0, 'Winds of the south, rise and come to your master\'s aid!', 14, 0, 100, 0, 0, 20227, 'Siamat - Aggro 1'),
(44819, 1, 1, 'Your city will be buried. Your lives forfeit to the elements!', 14, 0, 100, 0, 0, 20230, 'Siamat - Aggro 2'),
(44819, 2, 0, 'Cower before the tempest storm!', 14, 0, 100, 0, 0, 20228, 'Siamat - Wailing Winds 1'),
(44819, 2, 1, 'Suffer the storm!', 14, 0, 100, 0, 0, 20229, 'Siamat - Wailing Winds 2'),
(44819, 2, 1, 'Nothing more than dust in the wind.', 14, 0, 100, 0, 0, 20232, 'Siamat - Slay'),
(44819, 4, 0, 'The sky... Beckons...', 14, 0, 100, 0, 0, 20226, 'Siamat - Death');

DELETE FROM conditions WHERE SourceEntry IN (85017, 83151);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 85017, 0, 0, 31, 0, 3, 48097, 0, 0, 0, '', 'Slipstream - Target Wind Tunnel Landing Zone'),
(13, 7, 83151, 0, 0, 31, 0, 3, 44704, 0, 0, 0, '', 'Absorb Storm - Target Minion of Siamat');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(85016, 'spell_lct_slipstream'),
(83066, 'spell_lct_wailing_winds'),
(84521, 'spell_lct_thunder_crash');

REPLACE INTO `creature_onkill_reward` (`creature_id`, `RewOnKillRepFaction1`, `MaxStanding1`, `RewOnKillRepValue1`, `CurrencyId1`, `CurrencyCount1`) VALUES
(44819, 0, 0, 0, 395, 30), -- 5 Player Normal
(51088, 0, 0, 0, 395, 70); -- 5 Player Heroic
