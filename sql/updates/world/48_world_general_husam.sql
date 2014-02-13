
/*
12:42:45.604 -- aggro
-- traps
12:42:53.045 -- throw target trigger
12:42:53.045 -- 1

12:43:09.924 -- throw target trigger
12:43:09.519 -- 2

*/


UPDATE `instance_template` SET `script`= 'instance_lost_city_of_the_tolvir' WHERE `map`= 755;

-- General Husam Encounter

UPDATE `creature_template` SET `minlevel`= 86, `maxlevel`= 86, `scriptname`= 'boss_general_husam', `vehicleId`= 1036, `mindmg`= 399, `maxdmg`= 598, `attackpower`= 150, `dmg_multiplier`= 125, `movementId`= 154 WHERE `entry`= 44577;
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction_A`= 16, `faction_H`= 16, `exp`= 3, `vehicleId`= 1036, `mindmg`= 532, `maxdmg`= 798, `attackpower`= 199, `dmg_multiplier`= 125, `movementId`= 154 WHERE `entry`= 48932;
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction_A`= 16, `faction_H`= 16, `flags_extra`= 130, `scriptname`= 'npc_lct_shockwave_visual' WHERE `entry`= 44712;
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction_A`= 16, `faction_H`= 16, `flags_extra`= 130, `vehicleID`= 1050, `scriptname`= 'npc_lct_landmine_vehicle' WHERE `entry`= 44798;
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction_A`= 16, `faction_H`= 16, `flags_extra`= 130, `scriptname`= 'npc_lct_landmine_passenger' WHERE `entry`= 44796;
UPDATE `creature_template` SET `flags_extra`= 130 WHERE `entry`= 44840;
UPDATE `creature_template` SET `InhabitType`= 6 WHERE `entry`= 44711;
UPDATE `creature_template` SET `InhabitType`= 4, `flags_extra`= 130 WHERE `entry`= 44586;

DELETE FROM `creature_text` WHERE `entry` = 44577;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(44577, 0, 0, 'Invaders! You shall go no further!', '14', '0', '0', '0', '0', '21886', 'General Husam - Aggro'), 
(44577, 1, 0, 'Murkash!', '14', '0', '0', '0', '0', '21888', 'General Husam - Shockwave'),
(44577, 2, 0, '|TInterface\\Icons\\spell_nature_earthquake.blp:20|t%s begins to cast |cFFFF0000|Hspell:83445|h[Shockwave]|h|r!', 41, 0, 100, 0, 0, 0, 'General Husam- Shockwave'),
(44577, 3, 0, 'Tread lightly!', '1', '0', '0', '0', '0', '21887', 'General Husam - Mines Explosion'),
(44577, 4, 0, 'Siamat must not be freed! Turn back before it is too late!', '14', '0', '0', '0', '0', '21885', 'General Husam - Death'),
(44577, 5, 0, 'Insolent rats!', '14', '0', '0', '0', '0', '21889', 'General Husam - Kill Player');

DELETE FROM conditions WHERE SourceEntry IN (83445, 91257, 83466, 81350, 91263);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 91263, 0, 0, 31, 0, 3, 44796, 0, 0, 0, '', 'Detonate Traps - Target Trap Passenger'),
(13, 7, 81350, 0, 0, 31, 0, 3, 44586, 0, 0, 0, '', 'Pillar Shake - Target Pillar'),
(13, 7, 83466, 0, 0, 31, 0, 3, 44711, 0, 0, 0, '', 'Shockwave - Target Shockwave Dummy'),
(13, 7, 83445, 0, 0, 31, 0, 3, 44711, 0, 0, 0, '', 'Shockwave - Target Shockwave Dummy'),
(13, 7, 91257, 0, 0, 31, 0, 3, 44711, 0, 0, 0, '', 'Shockwave - Target Shockwave Dummy');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(83445, 'spell_lct_shockwave'),
(91257, 'spell_lct_shockwave'),
(83113, 'spell_lct_bad_ententions'),
(83129, 'spell_lct_shockwave_visual_summon'),
(91263, 'spell_lct_detonate_traps'),
(83654, 'spell_lct_hammer_fist'),
(91256, 'spell_lct_hammer_fist');

REPLACE INTO `creature_template_addon` (`entry`, `auras`) VALUES
(44712, '83127'),
(44711, '83129');

REPLACE INTO `creature_onkill_reward` (`creature_id`, `RewOnKillRepFaction1`, `MaxStanding1`, `RewOnKillRepValue1`, `CurrencyId1`, `CurrencyCount1`) VALUES
(44577, 0, 0, 0, 395, 30), -- 5 Player Normal
(48932, 0, 0, 0, 395, 70); -- 5 Player Heroic